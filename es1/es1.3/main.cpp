#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "random.hpp"
#include "../../datablocking.hpp"
#include  "../../functions.hpp"
#include "../../ini_reader.hpp"
using namespace std;

int main (int argc, char **argv){
	if (argc!=2){
		cerr << "[MAIN] Error: Program requires <config_file> parameter. Exiting..."<<endl;
		exit(EXIT_FAILURE);
	}
	string filename = argv[1];
	INIReader reader(filename);
	if (reader.ParseError() < 0) {
        cerr << "[MAIN] Error: Can't load "<<filename<<endl;
        exit(EXIT_FAILURE);
    }
	bool logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","true"));
	bool data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
    if (logger_debug)cout << "----> Initializing random number generator"<<endl<<endl;
    Random rnd=initialization();
	unsigned N = stoi(reader.Get("simulation","throws","10000")); // Number of throws inside each block
	unsigned L = stoi(reader.Get("simulation","blocks","100")); // Number of blocks
	unsigned M = int(N*L); // Total throws over all blocks (unused)
	double spacing = stod(reader.Get("simulation","blocks","10.0"));
	double PI[L];
	unsigned Nhit=0;
	unsigned Ntot=0;
	double x_1, x_2, theta;
	double l=0.8;
	double t=1.;
	if (logger_debug){
		cout << "----> Starting simulation"<<endl;
		cout << "--> L (number of blocks): "<<L<<endl;
		cout << "--> N (throws in a block): "<<N<<endl<<endl;
	}

	for (unsigned j=0; j<L; j++){
		Nhit=Ntot=0;

		ofstream positions("outputs/positions.dat");
		for(unsigned i=0; i<N; i++){
			theta=rnd.Direction2D();
			x_1=rnd.Rannyu()*10.;
			x_2=x_1+l*sin(theta);
			// i , x1 , y1 , x2 , y2
			
			if (int(x_1)!=int(x_2) || x_1<0 || x_2<0) {
				positions << i << "\t" << x_1 << "\t" << 0 << "\t" << x_2 << "\t" << x_1+l*cos(theta)<<"\t"<<1<<endl;
				Ntot++;Nhit++;
			}else {
				positions << i << "\t" << x_1 << "\t" << 0 << "\t" << x_2 << "\t" << x_1+l*cos(theta)<<"\t"<<0<<endl;
				Ntot++;
			}
		}
		positions.close();
		PI[j]=2.*l*Ntot/(Nhit*t);
		if (data_debug){
			cout << "- Iteration: "<<j<<"/"<<L<<endl;
			cout << "- Partial acceptance: "<<Nhit/Ntot<<endl;
			cout << "- Partial PI estimate: "<<PI[j]<<endl<<endl;
		}
	}

    if (logger_debug)cout << "\nPrinting data to results file"<<endl;
	string outputfile="outputs/results.dat";
	Ex1::DataBlocking(PI, L, outputfile);	

	return 0;
}   