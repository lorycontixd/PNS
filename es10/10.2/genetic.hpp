#ifndef __GENETIC_HPP__
#define __GENETIC_HPP__
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <filesystem>
#include <tuple>
#include "settings.hpp"
#include "population.hpp"
#include "exceptions.hpp"
#include "random.hpp"
#include "citygen.hpp"
#include "mutations.hpp"
#include "../../logger.hpp"
using namespace std;
using namespace settings;
namespace fs = std::filesystem;


class GeneticAlgorithm{
    /*Class for the Genetic Algorithm

    This class differs from the Genetic Algorithm class from Ex9 because only few methods are needed in Ex10.
    */
    private:
        Population population;
        double beta;

        int mpisize, mpirank;
        bool ismaster;

        Random *rnd;
        string configfile;
        bool initialized;
        Log::Logger logger;
    protected:
    public:
        GeneticAlgorithm(int mysize, int myrank){
            mpisize = mysize;
            mpirank = myrank;
            if (mpirank==0){
                ismaster = true;
            }else{
                ismaster = false;
            }
            initialized = false;
        };
        ~GeneticAlgorithm(){};


        void Input(string configfile){
            /* 
                Initializes simulation settings & system variables, logger and database
            */
            if (!initialized){ 
                beta = 1.0;
                rnd = new Random();
                LoadSettings(configfile); // Loads simulation + system settings
                fs::create_directory("outputs/");
                fs::create_directory(settings::output_dir);
                logger.set_name("GA_Logger");   // Initializes logger class
                logger.set_level(Log::LEVEL_DEBUG);
                GenerateCities(settings::layout); // Generates city positions -> Returns X,Y vectors
                CityX = GetCityX();
                CityY = GetCityY();
                CityIndex = GetCityIndexes();
                initialized = true;
            }else{
                cerr << "[GA] Warning: Simulation already initialized. Ignoring call. "<<endl;
                //#pragma message(Warning "[GA] Simulation already initialized.")
            }
        };

        auto SaveConfig(){
            vector<Individual> inds = population.GetIndividuals();
            string newdir = "files/";
            fs::create_directory(settings::output_dir+newdir);
            ofstream out;
            out.open(settings::output_dir+newdir+"genes.dat"); // Save genes of best individual
            if (out.fail()){
                logger.fatal("Could not open file: "+settings::output_dir+"genes.dat");
            }else{
                vector<unsigned> genes = inds.back().GetGenes();
                for (size_t t=0; t<genes.size(); t++){
                    out << genes[t] << endl;
                }
                out.close();
            }
            out.open(settings::output_dir+newdir+"fitnesses.dat"); // Save fitnesses of all individuals
            if (out.fail()){
                logger.fatal("Could not open file: "+settings::output_dir+"fitnesses.dat");
            }else{
                for (size_t t=0; t<inds.size(); t++){
                    out << t << "\t" << inds[t].GetBeta() << "\t" << inds[t].GetFitnessConst()<<endl;
                }
                out.close();
            }
        }

        void close(){

        };

        // ***********  GETS  ************
        double GetBeta() const {
            return beta;
        }

        Population& GetPopulation() {
            return population;
        };

        int GetMPISize() const {
            return mpisize;
        }

        int GetMPIRank() const {
            return mpirank;
        }

        bool IsMaster() const {
            return ismaster;
        }
        // ***********  SETS  ************
        void SetBeta(double _beta){
            beta = _beta;
        }
};

#endif