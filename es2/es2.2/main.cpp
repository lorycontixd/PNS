#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include "../../functions.hpp"
#include "../../ini_reader.hpp"
#include "../../datablocking.hpp"
#include "random.hpp"
#if !defined(DISCRETE)
    #define DISCRETE 0
#endif
#if !defined(CONTINUOUS)
    #define CONTINUOUS 1
#endif
using namespace std;

Random rnd = Init();

void TakeStep(unsigned i, double a, vector<double>& positions){
    if (i==0){
        // DISCRETE STEP
        double dir = rnd.Rannyu(0,3);
        double verse = rnd.Rannyu(0,2);
        int sign;
        if (verse<=1){
            sign = -1;
        }else{
            sign = 1;
        }
        if (dir<=1){
            positions[0] += sign*a;
        }else if(1<dir && dir<=2){
            positions[1] += sign*a;
        }else{
            positions[2] += sign*a;
        }
    }else if(i==1){
        // CONTINUOUS STEP
        double theta = rnd.Rannyu(0,M_PI);
        double phi = rnd.Rannyu(0,2*M_PI);

        positions[0] += a*cos(phi)*sin(theta);
        positions[1] += a*sin(phi)*sin(theta);
        positions[2] += a*cos(theta);

    }else{
        throw "Invalid index [i] for random walk, must be 0 or 1.";
    }
}



int main(int argc, char** argv){
    if (argc!=2){cerr << "One parameter must be passed: <config_file>."<<endl;}
    string filename = argv[1];
    INIReader reader(filename);

    unsigned int runs = stoi(reader.Get("simulation","iterations","10000"));
    unsigned int steps = stoi(reader.Get("simulation","steps","100"));
    double a = stod(reader.Get("simulation","lattice_constant","1"));
    bool logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","false"));
    bool data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
    string base_dir = reader.Get("settings","base_dir","results/");

    map<unsigned, string> keys = {
        {DISCRETE,"discrete"},
        {CONTINUOUS,"continuous"}
    };
    vector<double> AV_dist(steps,0.0); // hold distance of each step
    vector<double> AV_dist2(steps,0.0); // hold distance^2 of each step
    vector<double> err(steps,0.0); // hold error of each step
    vector<double> av_random_walks(runs);

    for (unsigned k=0; k<keys.size(); k++){
        // 0 --> discrete
        // 1 --> continuous

        // Initialize variables for each simulation (disc,cont)
        vector<double> positions(3,0.0);
        double dist = 0;
        ofstream pos_out(base_dir+keys[k]+"_pos.dat"); // save position after each RW run
        ofstream results_out(base_dir+keys[k]+"_results.dat");

        // Print config
        if (logger_debug){
            console::ConsoleHeader("Random walk: "+keys[k],"*",70);
            cout << "-- Lattice constant: "<<a<<endl;
            cout << "-- Initial position: ("<<positions[0]<<","<<positions[1]<<","<<positions[2]<<")"<<endl;
        }

        for (unsigned j=0; j<runs; j++){
            // Reset positions & distances for each RW run
            fill(positions.begin(), positions.end(), 0.0);
            for (unsigned i=0; i<steps; i++){
                TakeStep(k,a,positions);
                dist = pow(positions[0],2)+pow(positions[1],2)+pow(positions[2],2);
                AV_dist[i] += dist;
                AV_dist2[i] += pow(dist,2);
                if (j==0){
                    pos_out << positions[0]<<"\t"<<positions[1]<<"\t"<<positions[2]<<"\t"<<dist<<endl;
                }
            }
        }

        for(int i=0;i<steps;i++){
            //cout << AV_dist[i]<<endl;
			AV_dist[i] = AV_dist[i]/double(runs);   // transform sums in averages
			AV_dist2[i] = AV_dist2[i]/double(runs);  // transform sums in averages
			err[i] = sqrt( (AV_dist2[i] - pow(AV_dist[i],2))/double(runs) );
			results_out << i+1 << "	" << sqrt(AV_dist[i]) << "	" << err[i] / (2.*sqrt(AV_dist[i])) << endl;
		}
        pos_out.close();
        results_out.close();
        console::newlines(2);
    }
    return 0;
}