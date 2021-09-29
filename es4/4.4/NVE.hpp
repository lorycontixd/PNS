#include <iostream>   
#include <cstdlib>    
#include <fstream>    
#include <cmath> 
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>
#include "../inc/random.hpp"
#include "../../functions.hpp"
#include "datablocking.hpp"
#include "../../ini_reader.hpp"

using namespace std;
namespace fs = std::filesystem;


class NVE{
	private:
		Random *rnd;

		const int m_props=4;
		int n_props;
		int iv,ik,it,ie;
		double stima_epot, stima_ekin, stima_etot, stima_temp, stima_pres;

		// averages
		double acc,att;

		//configuration
		const int m_part=108;
		vector<double> x,y,z,xold,yold,zold,vx,vy,vz;
		unsigned nrestart;
		bool restart;

		// thermodynamical state
		unsigned npart;
		double energy, temp, vol, rho, box, rcut;
		string stateofmatter;

		// simulation
		unsigned nstep, nblocks;
		double delta;
		string configfile;
		bool equilibrationrun;
		bool xyz;

		auto PrepareVectors(){
			x.resize(m_part);
			y.resize(m_part);
			z.resize(m_part);
			xold.resize(m_part);
			yold.resize(m_part);
			zold.resize(m_part);

			vx.resize(m_part);
			vy.resize(m_part);
			vz.resize(m_part);
		};

		auto ParseConfiguration(string configfile){
			INIReader reader(configfile);
			stateofmatter = reader.Get("simulation","name","solid");
			npart = stoi(reader.Get("simulation","n_part","108"));
			nstep = stoi(reader.Get("simulation","nstep","10000"));
			temp = stod(reader.Get("simulation","temp","1.9"));
			rho = stod(reader.Get("simulation","rho","0.8"));
			rcut = stod(reader.Get("simulation","rcut","2.5"));
			delta = stod(reader.Get("simulation","delta","0.0005"));
			nblocks = stoi(reader.Get("simulation","nblocks","100"));
			xyz = general::conversion::to_bool(reader.Get("settings","xyz","false"));
		};

		auto PrepareDirectories(){
			string basedir = "outputs/";
			fs::create_directory(basedir);
			string statedir = basedir+stateofmatter+"/";
			fs::create_directory(statedir);
			fs::create_directory("frames/");
			fs::create_directory(statedir+"equilibration/");
			fs::create_directory(statedir+"measurements/");
		}

	public:
		NVE(string cfile, unsigned _nrestart, bool equilibration){
			configfile = cfile;
			nrestart = _nrestart;
			equilibrationrun = equilibration;
			cout << "[NVE] Eqrun: "<<boolalpha<<equilibrationrun<<endl;
			if (nrestart==0){
				restart = true;
			}else{
				restart = false;
			}
			rnd = new Random();
		};

		void Input(){ //Prepare all stuff for the simulation
			ifstream ReadConf;

			cout << "Classic Lennard-Jones fluid" << endl;
			cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
			cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
			cout << "The program uses Lennard-Jones units " << endl;

			ParseConfiguration(configfile);
			PrepareVectors();
			PrepareDirectories();
			
			cout << "Number of particles = " << npart << endl;
			cout << "Density of particles = " << rho << endl;
			vol = (double)npart/rho;
			cout << "Volume of the simulation box = " << vol << endl;
			box = pow(vol,1.0/3.0);
			cout << "Edge of the simulation box = " << box << endl;	
			cout << "The program integrates Newton equations with the Verlet method " << endl;
			cout << "Time step = " << delta << endl;
			cout << "Number of steps = " << nstep << endl << endl;

			if(restart){ 
				//Read initial configuration
				cout << "Read initial configuration from file config.0 " << endl << endl;
				ReadConf.open("configs/config.0");
				for (int i=0; i<npart; ++i){
					ReadConf >> x[i] >> y[i] >> z[i];
					x[i] = x[i] * box;
					y[i] = y[i] * box;
					z[i] = z[i] * box;
				}
				ReadConf.close();
				
				//Prepare initial velocities
				cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
				double sumv[3] = {0.0, 0.0, 0.0};
				for (int i=0; i<npart; ++i){
					vx[i] = rnd->Rannyu() - 0.5;
					vy[i] = rnd->Rannyu() - 0.5;
					vz[i] = rnd->Rannyu() - 0.5;

					sumv[0] += vx[i];
					sumv[1] += vy[i];
					sumv[2] += vz[i];
				}
				for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
				double sumv2 = 0.0, fs;
				for (int i=0; i<npart; ++i){
					vx[i] = vx[i] - sumv[0];
					vy[i] = vy[i] - sumv[1];
					vz[i] = vz[i] - sumv[2];

					sumv2 += vx[i]*	vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
				}

				sumv2 /= (double)npart;
				fs =sqrt(3 * temp / sumv2);   // fs = velocity scale factor 
				if (equilibrationrun){
					/* I only want to rescale the velocities if I'm performing equilibration, not in teh measurements */
					for (int i=0; i<npart; ++i){
						vx[i] *= fs;
						vy[i] *= fs;
						vz[i] *= fs;
					}
					cout << "scale factor: "<<fs<<endl;
					cout << vx[0] << "," << vy[0] << "," << vz[0] << endl;
				}

				for (int i=0; i<npart; ++i){
					xold[i] = Pbc(x[i] - vx[i] * delta);
					yold[i] = Pbc(y[i] - vy[i] * delta);
					zold[i] = Pbc(z[i] - vz[i] * delta);
				}
				
			}else{
			//Read final configuration and restart from there
				ifstream ReadFinalConf,ReadOldFinalConf;
				cout << "Restart form final configuration from file config.final " << endl << endl;
				ReadFinalConf.open("configs/config.final");
				ReadOldFinalConf.open("configs/config.old_final");
				double startx[npart], starty[npart], startz[npart];
				for (int i=0; i<npart; ++i){
					ReadFinalConf >> x[i] >> y[i] >> z[i];
					ReadOldFinalConf >> xold[i] >> yold[i] >> zold[i];
					x[i] = x[i] * box;
					y[i] = y[i] * box;
					z[i] = z[i] * box;
					xold[i] = xold[i] * box;
					yold[i] = yold[i] * box;
					zold[i] = zold[i] * box;
					startx[i] = x[i];
					starty[i] = y[i];
					startz[i] = z[i];
				}
				ReadFinalConf.close();
				ReadOldFinalConf.close();
				
			//Prepare initial velocities
				double xnew, ynew, znew;
				vector<double> fx(m_part);
				vector<double> fy(m_part);
				vector<double> fz(m_part);
				double fs, sumv2=0;

				for(int i=0; i<npart; ++i){ //Force acting on particle i
					fx[i] = Force(i,0);
					fy[i] = Force(i,1);
					fz[i] = Force(i,2);
				}

				for(int i=0; i<npart; ++i){ //calcolo v(t+dt/2)

					xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
					ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
					znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

					vx[i] = Pbc(xnew - x[i])/ delta;
					vy[i] = Pbc(ynew - y[i])/ delta;
					vz[i] = Pbc(znew - z[i])/ delta;

					sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];	

					x[i] = xnew;
					y[i] = ynew;
					z[i] = znew;
				}
				sumv2 /= (double)npart;
				fs = sqrt(3.*temp/sumv2);   // fs = velocity scale factor 
				
				cout << "Before rescaling v: " << vx[0] << "," << vy[0] << "," << vz[0] << endl;
				if (equilibrationrun){
					for (int i=0; i<npart; ++i){
						vx[i] *= fs;
						vy[i] *= fs;
						vz[i] *= fs;
					}
					cout << "scale factor: "<<fs<<endl;
					
				}
				cout << "After rescaling v: " << vx[0] << "," << vy[0] << "," << vz[0] << endl;

				for (unsigned i=0; i<npart; ++i){
					xold[i] = Pbc(startx[i] - vx[i] * delta);
					yold[i] = Pbc(starty[i] - vy[i] * delta);
					zold[i] = Pbc(startz[i] - vz[i] * delta);

					x[i] = startx[i];
					y[i] = starty[i];
					z[i] = startz[i];
				}
				
			}
			return;
		};

		void Move(void){ //Move particles with Verlet algorithm
			double xnew, ynew, znew;
			vector<double> fx(m_part);
			vector<double> fy(m_part);
			vector<double> fz(m_part);

			for(int i=0; i<npart; ++i){ //Force acting on particle i
				fx[i] = Force(i,0);
				fy[i] = Force(i,1);
				fz[i] = Force(i,2);
			}

			for(int i=0; i<npart; ++i){ //Verlet integration scheme

				xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
				ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
				znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

				vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
				vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
				vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

				xold[i] = x[i];
				yold[i] = y[i];
				zold[i] = z[i];

				x[i] = xnew;
				y[i] = ynew;
				z[i] = znew;
			}
			return;
		}

		double Force(int ip, int idir){ //Compute forces as -Grad_ip V(r)
			double f=0.0;
			double dvec[3], dr;

			for (int i=0; i<npart; ++i){
				if(i != ip){
					dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
					dvec[1] = Pbc( y[ip] - y[i] );
					dvec[2] = Pbc( z[ip] - z[i] );

					dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
					dr = sqrt(dr);

					if(dr < rcut){
						f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
					}
				}
			}

			return f;
		}

		void Measure(){ //Properties measurement
			double v, t, p, vij, pij;
			double dx, dy, dz, dr;
			ofstream Epot, Ekin, Etot, Temp, Pres;

			v = 0.0; //reset observables
			t = 0.0;
			p = 0.0;

			//cycle over pairs of particles
			for (int i=0; i<npart-1; ++i){
				for (int j=i+1; j<npart; ++j){
			
					dx = Pbc( x[i] - x[j] );
					dy = Pbc( y[i] - y[j] );
					dz = Pbc( z[i] - z[j] );

					dr = dx*dx + dy*dy + dz*dz;
					dr = sqrt(dr);
					pij= 1./pow(dr,12)-0.5/pow(dr,6);
					p += pij;

					if(dr < rcut){
						vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);
						//Potential energy
						v += vij;
					}
				}          
			}

			for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]); //Kinetic energy
			string instantdir;
			if (equilibrationrun){
				instantdir = "./outputs/"+stateofmatter+"/equilibration/";
			}else{
				instantdir = "./outputs/"+stateofmatter+"/measurements/";
			}
			Epot.open(instantdir+"instant_epot.dat",ios::app);
			Ekin.open(instantdir+"instant_ekin.dat",ios::app);
			Temp.open(instantdir+"instant_temp.dat",ios::app);
			Etot.open(instantdir+"instant_etot.dat",ios::app);
			Pres.open(instantdir+"instant_pres.dat",ios::app);

			stima_epot = v/(double)npart; //Potential energy
			stima_ekin = t/(double)npart; //Kinetic energy
			stima_temp = (2.0 / 3.0) * t/(double)npart; //Temperature
			stima_etot = (t+v)/(double)npart; //Total enery
			stima_pres = rho * stima_temp + 48.* p / (3.*vol); //Pressure

			Epot << stima_epot << endl;
			Ekin << stima_ekin << endl;
			Temp << stima_temp << endl;
			Etot << stima_etot << endl;
			Pres << stima_pres << endl;

			Epot.close();
			Ekin.close();
			Temp.close();
			Etot.close();
			Pres.close();

			return;
		}

		void ConfFinal(void){ //Write final configuration
			ofstream WriteFinalConf;
			ofstream WriteOldFinalConf;
			cout << "Print final configuration to file config.final and scond to last configuration to file config.old_final " << endl << endl;
			WriteFinalConf.open("configs/config.final");
			WriteOldFinalConf.open("configs/config.old_final");

			for (int i=0; i<npart; ++i){
				WriteFinalConf << x[i]/box << "	" << y[i]/box << "	" << z[i]/box /*<< setw(wd) << vx[i] << setw(wd) <<  vy[i] << setw(wd) << vz[i]*/ << endl;
				WriteOldFinalConf << xold[i]/box << "	" <<  yold[i]/box << "	" << zold[i]/box << endl;
			}
			WriteFinalConf.close();
			WriteOldFinalConf.close();

			return;
		}

		void ConfXYZ(int nconf){ //Write configuration in .xyz format
			ofstream WriteXYZ;

			WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
			WriteXYZ << npart << endl;
			WriteXYZ << "This is only a comment!" << endl;
			for (int i=0; i<npart; ++i){
				WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
			}
			WriteXYZ.close();
		}

		double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
			return r - box * rint(r/box);
		}

		// ******************  GETS  ******************

		unsigned GetSteps() const {
			return nstep;
		}

		unsigned GetBlocks() const {
			return nblocks;
		}

		bool GetEquilibrationRun() const {
			return equilibrationrun;
		}

		string GetState() const {
			return stateofmatter;
		}

		bool GetXYZ() const {
			return xyz;
		}

};









