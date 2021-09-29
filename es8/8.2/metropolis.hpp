#ifndef __METROPOLIS_HPP__
#define __METROPOLIS_HPP__

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.hpp"
#include "wavefunctions.hpp"
#include "datablocking.hpp"
#include "../functions.hpp"
#include "../ini_reader.hpp"
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;

auto limit(double x){
	string s = to_string(x).substr(0,4);
	return s;
};

class Metropolis {
	private:
		double starting_position;
		double Pos;
		double Delta;
		double Acceptance;
		unsigned Ntot; 
		unsigned Nacc;

		unsigned nblocks, blocklength;
		unsigned eqsteps;
	

		MyWaveFunction *f;
		Random *rnd;
		
		bool automation; // controlled by python script or not
		string outputdir;
		string outputfile;
		string pos_filename;

		void PrepareDirectories(){
			fs::create_directory(outputdir);
			if (automation){
				fs::create_directory(outputdir+"automation/");
				fs::create_directory(outputdir+"automation/energies/");
				fs::create_directory(outputdir+"automation/positions/");
			}else{
				fs::create_directory(outputdir+"single/");
			}
		};

	public:
		Metropolis(double mu, double sigma, bool autom){
			rnd = new Random();
			f = new MyWaveFunction(mu, sigma);
			

			Acceptance=0.;
			Ntot=0;
			Nacc=0;
			automation = autom;
			outputdir = "outputs/";
			PrepareDirectories();
			
		};
		~Metropolis(){};

		auto Input(string configfile){
			
			nblocks = 100;
			blocklength = 1000;
			starting_position = 10.0;
			Pos = starting_position;
			eqsteps = 1000;
			Delta = 1.0;

			if (automation){
				outputfile = outputdir+"automation/energies/results_"+limit(GetMu())+"_"+limit(GetSigma())+".dat";
				pos_filename = outputdir+"automation/positions/pos_"+limit(GetMu())+"_"+limit(GetSigma())+".dat";
			}else{
				int i = general::filesystem::count_files("outputs/single");
				outputdir = "outputs/single/"+to_string(i)+"/";
				fs::create_directory(outputdir);
				outputfile = outputdir+"energy.dat";
				pos_filename = outputdir+"pos.dat";

				string settings_fname = outputdir+"settings.txt";
				ofstream settings(settings_fname);
				settings << "nblocks\tblocklength\tstart_pos\teqsteps\tmu\tsigma\tstart_delta" << endl;
				settings << nblocks << "\t" << blocklength << "\t" << starting_position << "\t" << eqsteps << "\t" << GetMu() << "\t" << GetSigma() << "\t" << Delta << endl;
				settings.close();
			}
		};

		bool MakePass(){
			double New_Pos=rnd->Rannyu(Pos-Delta/2.,Pos+Delta/2.);
			double A=min(1., f->squared(New_Pos)/f->squared(Pos) );
			double r=rnd->Rannyu();
			if(r<=A) {
				Pos=New_Pos;
				Ntot++;
				Nacc++;
				Acceptance=double(Nacc)/double(Ntot);
				return true;
			}else{
				Ntot++;
				Acceptance=double(Nacc)/double(Ntot);
				return false;
			}
		};

		double Equilibration(double Desire_Acceptance){
			int i;
			for(i=0;i<eqsteps;i++){
				if(Acceptance==Desire_Acceptance){break;}
				Ntot=Nacc=0;
				for(int j=0;j<100;j++){
					MakePass();
				}
				if(Acceptance<Desire_Acceptance){Delta=Delta-1./(i+1.);}
				if(Acceptance>Desire_Acceptance){Delta=Delta+1./(i+1.);}
				if(i==999){cout<<"Dopo "<<i<<" tentativi non ho raggiunto il valore di accettazione desiderato \n Acceptance = "<<Acceptance<<endl;}
			}
			cout<<"N di tentativi: "<<i<<"\naccettazione raggiunta: "<<Acceptance<<"\tDelta: "<<Delta<<endl;
			return Acceptance;
		}

		double Run(){
			double sum, ene;
			vector<double> AV(nblocks);
			ofstream pos(pos_filename);
			for (int l=0;l<nblocks;l++){
				sum=0;
				for (int i=0;i<blocklength; i++){
					MakePass();
					ene = -0.5*f->second_derivative(GetPosition())/f->eval(GetPosition())+Potential(GetPosition());
					sum += ene;
					pos << GetPosition() << endl;
				}
				AV[l]=sum/double(blocklength);
			}
			pos.close();
			Data_Blocking(AV, nblocks, outputfile);
		};
		
		auto Save(){
			if (automation){
				//string filename = "outputs/results"+
				ifstream risul(outputfile);
				string enfile = outputdir + "automation/energies.dat";
				ofstream energie(enfile,ios::app);
				int k;
				double x, error;
				while(! risul.eof()){
					risul >> k >> x >> error;
				}
				energie<< limit(GetMu()) <<"\t"<< limit(GetSigma()) <<"\t"<< x <<endl;
				energie.close();
				risul.close();
			}
		}

		double Potential(double x){
			return pow(x,4.)-5./2.*pow(x,2.);
		}

		// ************** Gets
		double GetPosition() const {
			return Pos;
		}

		double GetAcceptance() const {
			return Acceptance;
		}

		double GetMu() {
			return f->GetMu();
		}

		double GetSigma() {
			return f->GetSigma();
		}
};


#endif
