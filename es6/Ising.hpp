#ifndef __ISING_1D_HPP__
#define __ISING_1D_HPP__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <cmath>
#include "database.hpp"
#include "../ini_reader.hpp"
#include "../functions.hpp"
#include "random.hpp"
using namespace std;
namespace fs = std::filesystem;

class Ising {
	private:
		Random *rnd;
		Database db;

		//parameters, observables
		const vector<string> observables = {"ene","heat","susc","magn"};
		const unsigned n_observable = observables.size();
		int iu, ih, im, ix;
		vector<double> walker;

		// averages
		vector <double> glob_av, glob_av2, blk_av;
		double blk_norm,	accepted,	attempted;
		double stima_u,	stima_h,	stima_m,	stima_x;
		double err_u,		err_h,	err_m,	err_x;

		//configuration
		unsigned int nspin;
		vector<double> s;

		// thermodynamical state
		double temp, j, h, beta;

		// simulation
		bool metro;
		unsigned nstep, nblk, nRestart;
		bool restart;
		string configfile;
		string sampling; // Metropolis or Gibbs
		string outputdir;

		// simulation states

		auto PrepareVectors(){
			walker.resize(n_observable);
			s.resize(nspin);
			glob_av.resize(n_observable);
			glob_av2.resize(n_observable);
			blk_av.resize(n_observable);
		};

		auto PrepareDirectories(){
			string basedir = "outputs/";
			fs::create_directory(basedir);
			string dbdir = basedir+"databases/";
			fs::create_directory(dbdir);
		}

		void LoadDatabaseSettings(){
			if (db.IsConnected()){
				char *zErrMsg;
				cout << "Loading database settings into database: "<<db.GetName()<<endl;
				tuple<string,string,string> key = make_tuple("ID","INT PRIMARY KEY","NOT NULL");
				tuple<string,string,string> tuple_temp = make_tuple("TEMP","REAL","NOT NULL");
				tuple<string,string,string> tuple_beta = make_tuple("BETA","REAL","NOT NULL");
				tuple<string,string,string> tuple_spins = make_tuple("NSPIN","INT","NOT NULL");
				tuple<string,string,string> tuple_j = make_tuple("J","REAL","NOT NULL");
				tuple<string,string,string> tuple_h = make_tuple("H","REAL","NOT NULL");
				tuple<string,string,string> tuple_sampling = make_tuple("SAMPLING","REAL","NOT NULL");
				tuple<string,string,string> tuple_nsteps = make_tuple("NSTEPS","INT","NOT NULL");
				tuple<string,string,string> tuple_nblocks = make_tuple("NBLOCKS","INT","NOT NULL");
				vector<tuple<string,string,string>> myvec = {key,tuple_temp,tuple_beta,tuple_spins,tuple_j,tuple_h,tuple_sampling,tuple_nsteps,tuple_nblocks};
				db.create_table("SETTINGS",myvec,true);
				int rc,count;
				rc = sqlite3_exec(db.GetDatabase(), "SELECT COUNT(*) FROM SETTINGS", countcallback, &count, &zErrMsg);
				if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
				string sql = "INSERT INTO SETTINGS (ID,TEMP,BETA,NSPIN,J,H,SAMPLING,NSTEPS,NBLOCKS) VALUES ( "+to_string(count)+","+to_string(temp)+","+to_string(beta)+","+to_string(nspin)+","+to_string(j)+","+to_string(h)+",'"+sampling+"',"+to_string(nstep)+","+to_string(nblk)+");";
				db.insert(sql);
			}
		}


	public:
		Ising(){
			configfile = "config.ini";
			restart = true;
			rnd = new Random();
		};
		Ising(string config, bool nrestart){
			configfile = config;
			nRestart = nrestart;
			if (nRestart == 0){
				restart = true;
			}else{
				restart = false;
			}
			rnd = new Random();
			PrepareDirectories();
			string dbdir = "outputs/databases/";
			unsigned i = general::filesystem::count_files(dbdir);
			string dbname = dbdir+"database"+to_string(i);
			db.SetName(dbname);
			db.connect();
			cout << "Connected database:  " << db.GetName() << endl;
		};
		Ising(string config, bool nrestart, string dbname){
			configfile = config;
			nRestart = nrestart;
			if (nRestart == 0){
				restart = true;
			}else{
				restart = false;
			}
			rnd = new Random();
			PrepareDirectories();
			string dbdir = "outputs/databases/";
			db.SetName(dbdir+dbname);
			db.connect();
			cout << "Connected database:  " << db.GetName() << endl;
		};
		~Ising(){

		};

		auto Input() {
			INIReader reader(configfile);
			temp = stod(reader.Get("simulation","temperature","20"));
			beta = 1.0/temp;
			nspin = stoi(reader.Get("simulation","n_spin","50"));
			j = stod(reader.Get("simulation","J","1.0"));
			h = stod(reader.Get("simulation","h","0.0"));
			metro = general::conversion::to_bool(reader.Get("simulation","metro","0"));
			if (metro){sampling="metropolis";}else{sampling="gibbs";}
			nblk = stoi(reader.Get("simulation","nblocks","100"));
			nstep = stoi(reader.Get("simulation","runs","10000"));
			
			PrepareVectors();
			LoadDatabaseSettings();

			/*ofstream settings(outputdir+"settings.txt");
			settings << "temp\tbeta\tnspin\tj\th\tsampling\tnruns\tnblocks"<<endl;
			settings << temp << "\t" << beta << "\t" << nspin << "\t" << j << "\t" << h << "\t" << sampling << "\t" << nstep << "\t"  << nblk << endl;
			settings.close();
			*/

			cout << "Classic 1D Ising model             " << endl;
			cout << "Monte Carlo simulation             " << endl << endl;
			cout << "Nearest neighbour interaction      " << endl << endl;
			cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
			cout << "The program uses k_B=1 and mu_B=1 units " << endl;
			cout << "Temperature = " << temp << endl;
			cout << "Number of spins = " << nspin << endl;
			cout << "Exchange interaction = " << j << endl;
			cout << "External field = " << h <<endl;

			if(metro==1) cout << "The program perform Metropolis moves" << endl;
			else cout << "The program perform Gibbs moves" << endl;
			
			cout << "Number of blocks = " << nblk << endl;
			cout << "Number of steps in one block = " << nstep << endl << endl;

		//Prepare arrays for measurements
			iu = 0; //Energy
			ih = 1; //Heat capacity
			im = 2; //Magnetization
			ix = 3; //Magnetic susceptibility
		

		//initial configuration
			ifstream ReadInput;
			if(restart){
				for (int i=0; i<nspin; ++i) {
					if(rnd->Rannyu() >= 0.5) s[i] = 1;
					else s[i] = -1;
				}
				cout << "[Input] Is Restart" << endl;
			} else {
				ReadInput.open("final_configs/config.final");
				for (int i=0; i<nspin; ++i) {ReadInput>>s[i];}
				ReadInput.close();
				cout << "[Input] Is NOT Restart" << endl;
			}
		
		//Evaluate energy etc. of the initial configuration
			Measure();

		//Print initial values for the potential energy and virial
			cout << "Initial energy = " << walker[iu]/(double)nspin << endl << endl;
		}; // End of input

		void Move() {
			int o;
			double p, energy_old, energy_new;

			for(int i=0; i<nspin; ++i) {
				o = (int)(rnd->Rannyu()*nspin);	//Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)

				if(sampling=="metropolis"){ //Metropolis
					energy_old = Boltzmann(s[o], o);
					s[o] = s[o]*-1.;
					energy_new = Boltzmann(s[o], o);
					p=exp(-(energy_new-energy_old) / temp);
					if( rnd->Rannyu()<=p ) { //accetiamo la mossa
						accepted++;
						attempted++;
					}else{
						s[o]=s[o]*-1.;	
						attempted++;
					}
				}else{ //Gibbs sampling
					p = exp(-Boltzmann(1., o )/temp) / (exp(-Boltzmann(1.,o)/temp)+ exp(-Boltzmann(-1.,o)/temp) );//probabilità che s[o] = +1
					if( rnd->Rannyu() <= p ) {
						s[o]=+1;
					}else{
						s[o]=-1;
					}
				}
			}
		};

		double Boltzmann(int sm, int ip) {
			double ene = -j * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
			return ene;
		};

		void Measure() {
			double u = 0.0, m=0.0;

			for (int i=0; i<nspin; ++i) {
				u += -j * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);
				m += s[i];
			}
			walker[iu] = u;
			walker[ih] = u*u;
			walker[im] = m;
			walker[ix] = m*m;
		};

		void Reset(int iblk) { //Reset block averages
			if(iblk == 1) {
				for(int i=0; i<n_observable; ++i) {
					glob_av[i] = 0;
					glob_av2[i] = 0;
				}
			}

			for(int i=0; i<n_observable; ++i) {
				blk_av[i] = 0;
			}
			blk_norm = 0;
			attempted = 0;
			accepted = 0;
		}


		void Accumulate(void) { //Update block averages

			for(int i=0; i<n_observable; ++i) {
				blk_av[i] = blk_av[i] + walker[i];
			}
			blk_norm = blk_norm + 1.0;
		};

		void Averages(int iblk){ //Print results for current block
			ofstream Ene, Heat, Mag, Chi;
			string sql;
			
			cout << "Block number " << iblk << endl;
			cout << "Acceptance rate " << accepted/attempted << endl << endl;

			//Energy
			stima_u = blk_av[iu]/blk_norm/double(nspin);
			glob_av[iu]  += stima_u;
			glob_av2[iu] += stima_u*stima_u;
			err_u=Error(glob_av[iu],glob_av2[iu],iblk);
			/* Ene.open("outputs/ave_ene.dat",ios::app);
			Ene << nRestart*nblk+iblk << "	" << glob_av[iu]/double(iblk) << "	" << err_u << endl;
			Ene.close();*/
			tuple<string,string,string> tuple_eneind = make_tuple("I","INT","NOT NULL");
			tuple<string,string,string> tuple_ene= make_tuple("VALUE","REAL","NOT NULL");
			tuple<string,string,string> tuple_eneerr = make_tuple("ERROR","REAL","NOT NULL");
			vector<tuple<string,string,string>> cols_ene = {tuple_eneind,tuple_ene,tuple_eneerr};
			db.create_table("ENERGY",cols_ene,true);
			sql = "INSERT INTO ENERGY (I,VALUE,ERROR) VALUES ("+to_string(nRestart*nblk+iblk)+","+to_string(glob_av[iu]/double(iblk))+","+to_string(err_u)+");";
			db.insert(sql);

			//Heat Capacity
			stima_h = 1./(temp*temp) * ( blk_av[ih]/blk_norm - (blk_av[iu]*blk_av[iu]) / (blk_norm*blk_norm) ) / double(nspin);
			glob_av[ih]  += stima_h;
			glob_av2[ih] += stima_h*stima_h;
			err_h=Error(glob_av[ih],glob_av2[ih],iblk);
			/*Heat.open("outputs/ave_heat.dat",ios::app);
			Heat << nRestart*nblk+iblk << "	" << glob_av[ih]/double(iblk) << "	" << err_h << endl;
			Heat.close();*/
			tuple<string,string,string> tuple_heatind = make_tuple("I","INT","NOT NULL");
			tuple<string,string,string> tuple_heat = make_tuple("VALUE","REAL","NOT NULL");
			tuple<string,string,string> tuple_heaterr = make_tuple("ERROR","REAL","NOT NULL");
			vector<tuple<string,string,string>> cols_heat = {tuple_heatind,tuple_heat,tuple_heaterr};
			db.create_table("HEAT",cols_ene,true);
			sql = "INSERT INTO HEAT (I,VALUE,ERROR) VALUES ("+to_string(nRestart*nblk+iblk)+","+to_string(glob_av[ih]/double(iblk))+","+to_string(err_h)+");";
			db.insert(sql);

			// Magnetic Susceptibility
			stima_x = 1./temp * blk_av[ix]/blk_norm / double(nspin); 
			glob_av[ix]  += stima_x;
			glob_av2[ix] += stima_x*stima_x;
			err_x = Error( glob_av[ix], glob_av2[ix], iblk);
			/*Chi.open("outputs/ave_susc.dat",ios::app);
			Chi << nRestart*nblk+iblk << "	" << glob_av[ix]/double(iblk) << "	" << err_x << endl;
			Chi.close();*/
			tuple<string,string,string> tuple_suscind = make_tuple("I","INT","NOT NULL");
			tuple<string,string,string> tuple_susc = make_tuple("VALUE","REAL","NOT NULL");
			tuple<string,string,string> tuple_suscerr = make_tuple("ERROR","REAL","NOT NULL");
			vector<tuple<string,string,string>> cols_susc = {tuple_suscind,tuple_susc,tuple_suscerr};
			db.create_table("SUSC",cols_susc,true);
			sql = "INSERT INTO SUSC (I,VALUE,ERROR) VALUES ("+to_string(nRestart*nblk+iblk)+","+to_string(glob_av[ix]/double(iblk))+","+to_string(err_x)+");";
			db.insert(sql);

			// Magnetization
			stima_m = blk_av[im]/blk_norm / double(nspin); 
			glob_av[im]  += stima_m;
			glob_av2[im] += stima_m*stima_m;
			err_m = Error( glob_av[im], glob_av2[im], iblk);
			/*Mag.open("outputs/ave_magn.dat",ios::app);
			Mag << nRestart*nblk+iblk << "	" << glob_av[im]/double(iblk) << "	" << err_m << endl;
			Mag.close();*/
			tuple<string,string,string> tuple_magnind = make_tuple("I","INT","NOT NULL");
			tuple<string,string,string> tuple_magn = make_tuple("VALUE","REAL","NOT NULL");
			tuple<string,string,string> tuple_magnerr = make_tuple("ERROR","REAL","NOT NULL");
			vector<tuple<string,string,string>> cols_magn = {tuple_magnind,tuple_magn,tuple_magnerr};
			db.create_table("MAGN",cols_magn,true);
			sql = "INSERT INTO MAGN (I,VALUE,ERROR) VALUES ("+to_string(nRestart*nblk+iblk)+","+to_string(glob_av[im]/double(iblk))+","+to_string(err_m)+");";
			db.insert(sql);

			cout << "----------------------------" << endl << endl;
		};

		void ConfFinal(void) {
			ofstream WriteConf;

			cout << "Print final configuration to file config.final " << endl << endl;
			WriteConf.open("final_configs/config.final");
			for (int i=0; i<nspin; ++i) {
				WriteConf << s[i] << endl;
			}
			WriteConf.close();
			rnd->SaveSeed();
		};

		int Pbc(int i) { //Algorithm for periodic boundary conditions
			if(i >= nspin) i = i - nspin;
			else if(i < 0) i = i + nspin;
			return i;
		};

		double Error(double sum, double sum2, int iblk) {
			return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)iblk);
		};

		void close(){
			db.close();
        };


		// *************  GETS  ***************
		auto GetBlocks() const {
			return nblk;
		}

		auto GetSteps() const {
			return nstep;
		}


};

#endif