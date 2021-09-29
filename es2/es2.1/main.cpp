#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include "random.hpp"
#include "../../datablocking.hpp"
#include "../../functions.hpp"
#include "../../ini_reader.hpp"
#if !defined(RESULTS_DIR)
    #define RESULTS_DIR "outputs/"
#endif
using namespace std;
using namespace std::chrono;

int main(int argc,char** argv){
    if (argc!=2){cerr << "One parameter must be passed: <config_file>."<<endl;exit(EXIT_FAILURE);}
    string filename = argv[1];
    INIReader reader(filename);

    unsigned int N = stoi(reader.Get("simulation","iterations","10000"));
    unsigned int blocks = stoi(reader.Get("simulation","blocks","100"));
    if (N%blocks!=0){
        cerr << "Please select a number of blocks as a factor of N."<<endl;
        exit(EXIT_FAILURE);
    }
    unsigned L = int(N/blocks);
    bool logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","false"));
    bool data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
    unsigned checkpoint = stoi(reader.Get("settings","checkpoint","100"));
    string uniform_file = reader.Get("settings","uniform_file","NONE");
    string optimized_file = reader.Get("settings","optimized_file","NONE");
    bool is_uniform_file = (uniform_file!="NONE");
    bool is_optimized_file = (optimized_file!="NONE");
    if (!is_uniform_file){
        cerr << "Must specify a parameter <uniform_file> in config file"<<endl;
        exit(EXIT_FAILURE);
    }
    if (!is_optimized_file){
        cerr << "Must specify a parameter <optmizied_file> in config file"<<endl;
        exit(EXIT_FAILURE);
    }
    
    Random rnd;
    vector<double> AV(blocks,0.0);
    double sum;
    if (logger_debug){cout << "Starting simulation with uniform sampling"<<endl;}
    auto start = high_resolution_clock::now();
    for (int j=0; j<blocks; j++){
		sum=0;
		for(int i=0; i<L; i++){
			sum += M_PI/2.*cos( M_PI/2.* rnd.Rannyu() );
		}
		AV[j] = sum/double(L);
        if (data_debug){
            cout << "Block "<<j<<" --->  estimate: "<<AV[j]<<endl;
        }
	}
	Ex2::DataBlocking(AV, uniform_file);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Uniform sampling execution time: "<<to_string(duration.count())<< " microseconds" << endl<< endl;


	double x,f_x;
    if (logger_debug){cout << "Starting simulation with importance sampling"<<endl;}
    auto start2 = high_resolution_clock::now();
	for (int j=0; j<blocks; j++){
        AV[j]=0;
		sum=0;
		for(int i=0; i<L; i++){
			x = 1.-sqrt (1.-rnd.Rannyu());							//genero un x con distribuzione p(x)=2-2x
			sum += M_PI/2.*cos( M_PI/2.*x)/(2*(1-x));
		}
		AV[j] = sum/double(L);
        if (data_debug){
            cout << "Block "<<j<<" --->  estimate: "<<AV[j]<<endl;
        }
	}
	Ex2::DataBlocking(AV, optimized_file);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Importance sampling execution time: "<<to_string(duration2.count())<< " microseconds" << endl<< endl;

    return 0;
}