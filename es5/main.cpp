#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>
#include <fstream>
#include "metropolis.hpp"
#include "functions.hpp"
#include "../ini_reader.hpp"
using namespace std;

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

auto get_files(string path, string simname){
    //THE SUBSTRING TO BE FOUND.
    auto pattern{ simname };
    int k=0;
    //std::regex_constants::icase - TO IGNORE CASE.
    auto rx = std::regex{ pattern,std::regex_constants::icase };
    for (const auto & entry : filesystem::directory_iterator(path)){
        string p = entry.path();
        if (std::regex_search(p, rx)){
            k++;
        }
    }
    return k;
}


int main(int argc, char const *argv[])
{
    if (argc != 2){
        cerr << "Simulation requires arg: <config_file>"<<endl;
        exit(EXIT_FAILURE);
    }
    string configfile = argv[1];
    unsigned simulations = 2;

    INIReader reader(configfile);
    if (reader.ParseError() != 0) {
        cout << "Can't load "<<configfile<<endl;
        return -1;
    }

    unsigned runs = stoi(reader.Get("simulation","runs","100000"));
    int blocks = stoi(reader.Get("simulation","blocks","1000"));
    double x0 = stof(reader.Get("simulation","x0","1.0"));
    double y0 = stof(reader.Get("simulation","y0","1.0"));
    double z0 = stof(reader.Get("simulation","z0","1.0"));
    double delta = stof(reader.Get("simulation","delta","1.0"));
    string sampling = reader.Get("simulation","sampling","normal");
    bool test_run = to_bool(reader.Get("settings","test","false"));
    bool ts = to_bool(reader.Get("settings","timeseries","false"));

    vector<double> avg;
    string data_output_file,ts_output_file,sim_name;
    for (int i=0;i<simulations;i++){
        Function *f;
        avg.clear();
        unsigned n,l,m;
        if (i==0){
            sim_name = "1s";
            n = 1; l = m = 0;
        }else if(i==1){
            sim_name = "2p";
            n = 2; l = 1; m = 0;
        }else{
            throw "Main: undefined wavefunction for i not 0,1";
        }
        if (test_run){
            f = new TestWaveFunction(n,l,m);
        }else{
            f = new WaveFunction(n,l,m);
        }
        
        Metropolis *met = new Metropolis(sim_name,runs,blocks,sampling,delta,x0,y0,z0,f);
        met->print_settings();

        avg = met->run();
        string outputdir = "results/"+met->GetSampling();
        data_output_file = outputdir+"/data_"+sim_name+"_"+to_string(get_files(outputdir,sim_name))+".dat";
        ofstream out;
        out.open(data_output_file);
        out << x0 << "\t" << y0 << "\t" << z0 << endl;
        out.close();
        if (ts){
            ts_output_file = "results/"+met->GetSampling()+"/timeseries_"+sim_name+".dat";
        }else{
            ts_output_file = "";
        }

        met -> write_results(data_output_file,ts_output_file,true);
        met->end(true);
        cout << " "<<endl<<endl;
    }
    return 0;
}