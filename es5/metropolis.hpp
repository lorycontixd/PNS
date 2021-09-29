#ifndef __METROPOLIS_HPP__
#define __METROPOLIS_HPP__
#define overwrite "\r"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>
#include "../datablocking.hpp"
#include "../logger.hpp"
#include "functions.hpp"
#include "random.hpp"
using namespace std;
using namespace filesystem; 
struct stat sb;

class Metropolis
{
    protected:
    // Class Parameters
        string name;
        unsigned iterations;
        unsigned nblocks;
        double delta;
        Random *dist = new Random();
        Log::Logger met_logger;
        Function *func;
        string sampling;
        
    // Class Local Variables
        vector<double> pos;
        vector<vector<vector<double>>> timeseries;
            // timeseries ==  array length L (iters) -> each with array length N (blocks) -> each array length 3 (x,y,z)
        unsigned nacc;
        unsigned ntot;
        double acceptance;
        vector<double> av;
        vector<double> acceptances;
        bool equilibrated = false;

    public:
        string check_sampling(string s){
            if (s!="normal" && s!="gauss"){
                throw "Metropolis: sampling must be normal or gauss, not "+s;
            }else{
                return s;
            }
        }

        // Constructors
        Metropolis(){
            name = "MyMetropolisAlgorithm";
            pos = {0.,0.,0.};
            delta = 1.;
            iterations = int(pow(10,5));
            nblocks = int(pow(10,2));
            func = new WaveFunction();
            sampling = "normal";
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
            //timeseries = new vector<vector<double>>();
        };

        Metropolis(string n, int iters, int blocks, string s){
            name = n;
            pos = {0.,0.,0.};
            delta = 1;
            iterations = iters;
            nblocks = blocks;
            func = new WaveFunction();
            sampling = check_sampling(s);
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
        };

        Metropolis(string n, unsigned iters, unsigned blocks, string s, double _delta, double x, double y, double z){
            name = n;
            pos = {0.,0.,0.};
            delta = _delta;
            iterations = iters;
            nblocks = blocks;
            func = new WaveFunction();
            sampling = check_sampling(s);
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
        };

        Metropolis(string n, unsigned iters, unsigned blocks, string s, double _delta, Function* f){
            name = n;
            pos = {0.,0.,0.};
            delta = _delta;
            iterations = iters;
            nblocks = blocks;
            func = f;
            sampling = check_sampling(s);
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
        };

        Metropolis(string n, string s, double x, double y, double z, double _delta,Function* f){
            name = n;
            pos = {x,y,z};
            delta = _delta;
            iterations = int(pow(10,5));
            nblocks = int(pow(10,2));
            func = f;
            sampling = check_sampling(s);
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
        };

        Metropolis(string n, unsigned iters, unsigned blocks, string s, double _delta, double x, double y, double z, Function* f){
            name = n;
            pos = {x,y,z};
            delta = _delta;
            iterations = iters;
            nblocks = blocks;
            func = f;
            sampling = check_sampling(s);
            met_logger.set_name("Metropolis Logger");
            met_logger.set_level(Log::LEVEL_DEBUG);

            acceptance = 0;
            nacc=0;
            ntot=0;
        };

        ~Metropolis(){};

        auto Input(){
            create_directory("results/");
            string samplingdir = "results/"+GetSampling()+"/";
            create_directory(samplingdir);

        }

        void print_settings(){
            met_logger.info("Launching Metropolis Algorithm");
            cout << "Name: "<<name<<endl;
            cout << "Iterations: "<<iterations<<endl;
            cout << "N° blocks: "<<nblocks<<endl;
            cout << "Starting position: ("<<pos[0]<<","<<pos[1]<<","<<pos[2]<<")"<<endl;
            cout << "Delta: "<<delta<<endl;
            cout << ""<<endl;
            func->print_settings();
        }

        // Setters & Getters
        void SetIterations(unsigned iters){
            iterations = iters;
        }

        void SetBlocks(unsigned blocks){
            nblocks = blocks;
        };

        void SetDelta(double d){
            delta = d;
        };

        // Computational Methods
        double calculate_ratio(double fold, double fnew){
            double ratio = fnew / fold;
            double alpha = min(1.,ratio);
            return alpha;
        };

        void calculate_acceptance(){
            acceptance = double(nacc)/double(ntot);
        };

        bool make_pass(int i){
            vector<double> newpos;
            double A = 0;
            for (int i=0;i<3;i++){
                if (sampling=="normal"){
                    newpos.push_back(dist->Rannyu(pos[i]-delta/2.,pos[i]+delta/2.));
                }else if(sampling == "gauss"){
                    newpos.push_back(dist->Gauss(pos[i],delta));
                }else{
                    // throw if put catch in main
                    cerr << "[METRO] Invalid sampling type: "<<sampling<<endl;
                    exit(EXIT_FAILURE);
                }

            }

            A = calculate_ratio(func->eval(pos),func->eval(newpos));
            double r=dist->Rannyu();
            bool accepted;
            if (r<=A){
                for(int i=0;i<3;i++){pos[i]=newpos[i];}
                ntot++;
		        nacc++; 
                accepted = true;
            }else{
                ntot++;
                accepted = false;    
            }
            calculate_acceptance();
            return accepted;
        };

        // Run the algorithm
        double equilibrate(double desired_acceptance, int max_iters, bool debug){
            met_logger.info("Equilibrating system...");
            //vector <double> pos = {x0,y0,z0};
            //timeseries.push_back(oldcoords);
            cout << "-- Starting Delta: "<<delta<<endl;
            int k=1;

            for (int i = 0;i<max_iters;++i){
                if (debug){
                    if (i%1000==0 && i!=0){
                        cout << "Checkpoint "<<k<<" reached   ("<<i<<"/"<<iterations<<")"<<"\t\r"<<flush;
                        k++;
                    }
                }
                if (acceptance == desired_acceptance){
                    cout << "Desired acceptance reached, stopping equilibration at step "<<i<<" of "<<max_iters << endl;
                    break;
                }
                nacc=ntot=0;

                // Cycle block
                for (int j=0;j<100;++j){
                    make_pass(i);
                }
                if(acceptance<desired_acceptance){
                    delta=delta-1./(i+1.);
                }
		        if(acceptance>desired_acceptance){
                    delta=delta+1./(i+1.);
                }
            }
            cout << "-- Final delta:  "<<delta<<endl;
            equilibrated = true;
            return acceptance;
        }

        vector<double> run(bool debug = false){
            met_logger.info("Running simulation...");
            double acc = equilibrate(0.5,10000,debug);
            if (!equilibrated){
                cout << "[WARNING] System has not been equilibrated" <<endl;
            }
            for (int i=0;i<int(iterations)/nblocks;i++){
                double sum=0;
                vector<vector<double>> temp_block;
                for (int j=0;j<nblocks;j++){
                    vector<double> temp_xyz = {pos[0],pos[1],pos[2]};
                    make_pass(i);
                    acceptances.push_back(acceptance);
                    sum+=sqrt(pos[0]*pos[0]+pos[1]*pos[1]+pos[2]*pos[2]);
                    temp_block.push_back(temp_xyz);
                }
                //cout << "[RUN] Average of block "<<i<<": "<<double(sum)/nblocks<<endl;
                av.push_back(double(sum)/nblocks);
                timeseries.push_back(temp_block);
            }
            cout <<""<<endl;
            return av;    
        }

        void write_results(string data_filename, string timeseries_filename,bool clear){
            met_logger.info("Saving results to file...");
            if (av.size()<=0){
                throw "Metropolis: cannot save results with no averages saved. Should call run function.";
            }
            Ex5::DataBlocking(av,int(iterations)/nblocks,data_filename);
            met_logger.debug("Datablocking completed..");
            string acc_filename = "results/"+GetSampling()+"/acceptance_"+name+".dat";
            ofstream AccStream(acc_filename);
            for (unsigned i=0; i<acceptances.size(); i++){
                AccStream << acceptances[i] << endl;
            }
            AccStream.close();
            if (timeseries_filename.size() > 0){
                if (timeseries.size()>0){
                    cout << "--- Saving timeseries to file: "<< timeseries_filename <<endl;
                    ofstream TimeseriesStream(timeseries_filename);
                    for (unsigned i=0;i<timeseries.size();i++){
                        for (unsigned j=0;j<timeseries[i].size();j++){
                            TimeseriesStream  <<timeseries[i][j][0] <<"\t"<< timeseries[i][j][1]<<"\t"<< timeseries[i][j][2]<<endl;
                        }
                        if (i%20==0){
                            cout << "- Writing timeseries "<<i<<"\t\r";
                        }
                        TimeseriesStream << endl;
                    }
                }
                met_logger.debug("Timeseries saved to file");
            }
            cout <<""<<endl;
            end(clear);
        } 

        void end(bool clear){
            met_logger.info("Terminating simulation...");
            if (clear){
                cout << "#### Clearing data from Metropolis..."<<endl;
                timeseries.clear();
                av.clear();
                acceptances.clear();
            }
            cout << "#### Clearing variable values..."<<endl;
            equilibrated = false;
            acceptance = 0;
            cout <<""<<endl;
        }

        void view_timeseries(){
            if (timeseries.size()<=0){
                throw "Metropolis: cannot view empty timeseries";
            }else{
                cout << "#### Viewing timeseries of Metropolis algorithm"<<endl;
                for (unsigned i=0;i<timeseries.size();i++){
                    cout << "----> Block "<<i<<endl;
                    for (unsigned j=0;j<timeseries[i].size();j++){
                        cout <<"-->" << timeseries[i][j][0] <<","<< timeseries[i][j][1]<<","<< timeseries[i][j][2]<<")"<<endl;
                    }
                    cout << endl;
                }
            }
            cout << "Partial N_acc/N_tot:\t"<<nacc<<" / "<<ntot<<"\t\t"<<double(nacc)/ntot<<endl;
        }


        // ##############  GET  ##########
        string GetSampling(){
            return sampling;
        }

        unsigned GetIterations(){
            return iterations;
        }

        vector<double> GetPosition(){
            return pos;
        }

        double GetDelta(){
            return delta;
        }

        unsigned GetBlocks(){
            return iterations;
        }
};

#endif