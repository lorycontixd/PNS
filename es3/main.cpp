#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdlib>

#include "random.hpp"
#include "../functions.hpp"
#include "../ini_reader.hpp"
#include "../datablocking.hpp"

using namespace std;


Random *rnd = new Random();

double GBM_Direct ( double, double, double, double);
double GBM_Step ( double, double, double, double, double);
double Max ( double, double, double, double, double, double);

int main (int argc, char **argv){
	if (argc!=2){
		cerr << "[MAIN] Error: Program requires parameter <config_file>"<<endl;
		exit(EXIT_FAILURE);
	}
	system("rm -f outputs/*.dat");
	INIReader reader(argv[1]);
	double T = stod(reader.Get("simulation","T","1"));
	double mu = stod(reader.Get("simulation","mu","0.1"));
	double sigma = stod(reader.Get("simulation","sigma","0.25"));
	double K = stod(reader.Get("simulation","K","100"));
	bool logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","true"));
	bool data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
	unsigned M=10000;
	unsigned N=100;
	unsigned L=M/N;
	vector<double> AV(L);
	double sum;
	string outputfile;
	double S_t, FinalPrice;

	if (logger_debug){console::ConsoleHeader("Exercise 3","*",100);}

	for(int Graph=0;Graph<4;Graph++){		//cicla sui 4 grafici richiesti (put-discretized, call-discretized, put-direct, call-direct)
		AV.clear();
		for (int j=0; j<L; j++){				//cicla sul n di blocchi
			sum = 0;
			for(int i=0; i<N; i++){				//cicla sulle stime del prezzo che in ogni blocco vengono fatte

				if(Graph<2){
					S_t = K;
					for(double h=0; h<1; h = h+0.01)  S_t = GBM_Step(h, h+0.01, mu, sigma, S_t);
				}

				FinalPrice = exp(-mu*T) * Max(Graph, S_t, T, mu, sigma, K);

				sum+=FinalPrice;
			}
			if (data_debug){
				cout << "[MAIN] Iter "<<j<<"/"<<L<<endl;
				cout << "[MAIN] Sum= "<<sum<<endl;
				cout << "[MAIN] N= "<<N<<endl;
				cout << "[MAIN] AV= "<<sum/double(N)<<endl<<endl;
			}
			AV.push_back(sum/double(N));
		}
		outputfile = "outputs/results"+to_string(Graph+1)+".dat";
		Ex3::DataBlocking( AV, L, outputfile);
	}
	return 0;
}

double GBM_Direct (double T, double mu, double sigma, double K){
	return K* exp( (mu-1./2.*sigma*sigma)*T + sigma*rnd->Gauss(0.,T) );
}

double GBM_Step (double T_0, double T_1, double mu, double sigma, double S_Prima){
	return S_Prima* exp( (mu-1./2.*sigma*sigma)*(T_1-T_0) + sigma*rnd->Gauss(0.,1.)*sqrt(T_1-T_0) );
}
double Max (double i, double S_t, double T, double mu, double sigma, double K){
	if(i==0) return max(0. , K-S_t);
	if(i==1) return max(0. , S_t-K);
	if(i==2) return max(0. , K-GBM_Direct(T,mu,sigma,K));
	if(i==3) return max(0. , GBM_Direct(T,mu,sigma,K)-K);
	else return 0;
};