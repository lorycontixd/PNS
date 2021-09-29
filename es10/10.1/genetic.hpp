#ifndef __GENETIC_HPP__
#define __GENETIC_HPP__
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <tuple>
#include "settings.hpp"
#include "population.hpp"
#include "exceptions.hpp"
#include "random.hpp"
#include "citygen.hpp"
#include "database.hpp"
#include "mutations.hpp"
#include "../../logger.hpp"
using namespace std;
using namespace settings;


class GeneticAlgorithm{
    /*Class for the Genetic Algorithm

    This class differs from the Genetic Algorithm class from Ex9 because only few methods are needed in Ex10.
    */
    private:
        Population population;
        double beta;

        Random *rnd;
        Database d;
        string configfile;
        bool initialized;
        Log::Logger logger;
    protected:
    public:
        GeneticAlgorithm(){
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
                logger.set_name("GA_Logger");   // Initializes logger class
                logger.set_level(Log::LEVEL_DEBUG);
                logger.info("Initializing simulation...");
                PrintSettings(); // Shows the settings
                if (settings::database_active){
                    cout << "Database active!!"<<endl;
                    if (settings::database_removeprevious){
                        // Removes previously-created databases
                        string cmd = "rm -f "+settings::output_dir+"*.db";
                        system(cmd.c_str());
                        if (settings::logger_debug) cout << "[GA] Removed previous database"<<endl;
                    }
                    d.SetName(settings::output_dir+settings::database_name,true);
                    cout << "Name: "<<d.GetName() << endl;
                    d.connect();
                    cout << "Connected database:  " << d.GetName() << endl;
                }
                LoadDatabaseSettings(d); // Load database settings
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
            if (settings::database_active){
                logger.info("Saving config in database");
                tuple<string,string,string> tuple_cities = make_tuple("ID","INTEGER","");
                tuple<string,string,string> tuple_citiesX = make_tuple("X","REAL","NOT NULL");
                tuple<string,string,string> tuple_citiesY = make_tuple("Y","REAL","NOT NULL");
                vector<tuple<string,string,string>> cols_cities = {tuple_cities,tuple_citiesX,tuple_citiesY};
                d.create_table("CITIES",cols_cities,true);

                tuple<string,string,string> tuple_id = make_tuple("ID","INTEGER","");
                tuple<string,string,string> tuple_beta = make_tuple("BETA","REAL","NOT NULL");
                tuple<string,string,string> tuple_fitness = make_tuple("FITNESS","REAL","NOT NULL"); 
                vector<tuple<string,string,string>> cols_fitness = {tuple_id,tuple_beta,tuple_fitness};
                d.create_table("FITNESSES",cols_fitness,true);

                tuple<string,string,string> tuple_best = make_tuple("GENES","INTEGER","NOT NULL");
                vector<tuple<string,string,string>> cols_best = {tuple_best};
                d.create_table("BEST",cols_best,true);

                string sql_fitness = "INSERT INTO FITNESSES (ID,BETA,FITNESS) VALUES ";
                string sql_cities = "INSERT INTO CITIES (ID,X,Y) VALUES ";
                string sql_best = "INSERT INTO BEST (GENES) VALUES ";

                vector<Individual> inds = population.GetIndividuals();
                for (size_t t=0; t<inds.size(); t++){
                    sql_fitness += "("+to_string(t)+","+to_string(inds[t].GetBeta())+","+to_string(inds[t].GetFitnessConst())+"),";
                }
                sql_fitness = sql_fitness.substr(0,sql_fitness.size()-1);
                sql_fitness += ";";

                vector<unsigned> genes = inds.back().GetGenes();           
                for (size_t t=0; t<genes.size(); t++){
                    sql_best += "("+to_string(genes[t])+"),";
                }
                sql_best = sql_best.substr(0,sql_best.size()-1);
                sql_best += ";";

                for (size_t t=0; t<settings::ncities; t++){
                    sql_cities += "("+to_string(t)+","+to_string(CityX[t])+","+to_string(CityY[t])+")";
                }
                sql_cities = sql_cities.substr(0,sql_cities.size()-1);
                sql_cities += ";";

                d.insert(sql_fitness);
                d.insert(sql_best);
                d.insert(sql_cities);
            }
            
        }

        void close(){
            if (settings::database_active){
                d.close();
            }
        };

        // ***********  GETS  ************
        double GetBeta() const {
            return beta;
        }

        Population& GetPopulation() {
            return population;
        };

        Database& GetDatabase() {
            return d;
        };
        // ***********  SETS  ************
        void SetBeta(double _beta){
            beta = _beta;
        }
};

#endif