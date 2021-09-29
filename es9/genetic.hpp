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
using namespace std;
using namespace settings;


class GeneticAlgorithm{
    /* Class for the Genetic Algorithm

    */
    private:
        Population population;
        
        unsigned generation_count;
        vector<Individual> parents;
        vector<double> fitness_per_iteration;

        Random *rnd;
        Database d;
        string configfile;
        bool initialized;
    protected:
    public:
        GeneticAlgorithm(){
            initialized = false;
        };
        ~GeneticAlgorithm(){};


        void Input(string configfile){
            if (!initialized){ 
                rnd = new Random();
                LoadSettings(configfile);
                if (settings::database_removeprevious){
                    string cmd = "rm -f "+settings::database_dir+"*.db";
                    system(cmd.c_str());
                    if (settings::logger_debug) cout << "[GA] Removed previous database"<<endl;
                }
                if (settings::database_active){
                    d.SetName(settings::database_name,true);
                    d.connect();
                }
                cout << "DB NAME:  " << d.GetName() << endl;
                LoadDatabaseSettings(d);
                GenerateCities(settings::layout); // Returns X,Y vectors
                CityX = GetCityX();
                CityY = GetCityY();
                CityIndex = GetCityIndexes();

                population.SetInitial();
                vector<Individual> inds = population.GetIndividuals();
                fitness_per_iteration.resize(0);
                parents.resize(2); // Set parents dimension to 2
                initialized = true;
            }else{
                cerr << "[GA] Warning: Simulation already initialized. Ignoring call. "<<endl;
                //#pragma message(Warning "[GA] Simulation already initialized.")
            }
        };


        auto Select(double expo=2.){
            unsigned a = int( settings::max_individuals*pow(rnd->Rannyu(),expo) );
            unsigned b = int( settings::max_individuals*pow(rnd->Rannyu(),expo) );
            //cout << "[Select] Indices: "<<a<< " , "<<b<<endl;
            parents[0] = population.GetIndividuals()[a];
            parents[1] = population.GetIndividuals()[b];
            return parents;
        };


        vector<Individual> Crossover(double probability){
            double r = rnd->Rannyu();
            if (r<probability){
                unsigned cut = int(rnd->Rannyu(0,settings::ncities));
                vector<unsigned> path0 = parents[0].GetGenes();
                vector<unsigned> path1 = parents[0].GetGenes();
                path0.resize(settings::ncities-cut);
                path1.resize(settings::ncities-cut);
                while (path0.size()<parents[0].GetGenesSize()){
                    for (unsigned i = 0; i<parents[1].GetGenesSize(); i++){
                        if(std::find(path0.begin(), path0.end(), parents[1].GetGenes()[i]) == path0.end()) {
                            path0.push_back(parents[1].GetGenes()[i]);
                        }
                    }
                }
                while (path1.size()<parents[1].GetGenesSize()){
                    for (unsigned i = 0; i<parents[0].GetGenesSize(); i++){
                        if(std::find(path1.begin(), path1.end(), parents[0].GetGenes()[i]) == path1.end()) {
                            path1.push_back(parents[0].GetGenes()[i]);
                        }
                    }
                }
                Individual son1(path0);
                Individual son2(path1);
                vector<Individual> sons = {path0, path1};
                return sons;
            }
        };


        void Mutation(double probability){
            for (auto& i : parents){
                if (rnd->Rannyu()<probability){Swap(i,rnd);}
                if (rnd->Rannyu()<probability){NeighbourSwap(i,rnd);}
                if (rnd->Rannyu()<probability){Shift(i,rnd);}
                if (rnd->Rannyu()<probability){MultipleSwap(i,rnd);}
                if (rnd->Rannyu()<probability){Reverse(i,rnd);}
            }
        }


        void SaveConfig(){
            if (settings::database_active){
                vector<tuple<string,string,string>> cols;
                for (size_t t = 0; t<settings::ncities; t++){
                    string colname = "INDEX"+to_string(t);
                    tuple <string,string,string> temp = make_tuple(colname,"INTEGER","");
                    cols.push_back(temp);
                }
                d.create_table("BEST",cols,true);

                // Register Final Fitness
                tuple<string,string,string> ftns = make_tuple("FITNESS","REAL","NOT NULL");
                vector<tuple<string,string,string>> fit_vec = {ftns};
                d.create_table("FITNESS",fit_vec,true);

                // Register Fitness Per Population
                vector<tuple<string,string,string>> fpi_cols;
                cout << "MAX POPULATIONS: "<<settings::max_populations<<endl;
                for (size_t t = 0; t<settings::max_populations; t++){
                    string colname = "ITER"+to_string(t);
                    tuple<string,string,string> tmp = make_tuple(colname,"INTEGER","");
                    fpi_cols.push_back(tmp);
                }
                d.create_table("FPI",fpi_cols,true);

                Individual best = population.GetFittest();
                vector<unsigned> best_genes = best.GetGenes();
                // Insert best & fitness
                string _columns = "";
                string _values = "";
                
                for (size_t t=0;t<cols.size(); t++){
                    _columns += get<0>(cols[t])+", ";
                    _values += to_string(best_genes[t])+", ";
                }
                _columns = _columns.substr(0,_columns.size()-2);
                _values = _values.substr(0,_values.size()-2);
                string sql = "INSERT INTO BEST("+_columns+") VALUES ("+_values+");";
                string sql2 = "INSERT INTO FITNESS(FITNESS) VALUES ("+to_string(best.GetFitnessConst())+")";
                cout << "fitness sql: "<<sql2<<endl;
                d.insert(sql); //best individual
                d.insert(sql2); //fitness
            
                
                // Insert fitness_per_iter
                _columns = "";
                _values = "";
                for (size_t t=0;t<fitness_per_iteration.size(); t++){
                    _columns += get<0>(fpi_cols[t])+", ";
                    _values += to_string(fitness_per_iteration[t])+", ";
                }
                _columns = _columns.substr(0,_columns.size()-2);
                _values = _values.substr(0,_values.size()-2);
                sql = "INSERT INTO FPI("+_columns+") VALUES ("+_values+");";
                cout << "fpi sql: "<<sql<<endl;
                d.insert(sql);
            }
        };


        void SaveTempFittest(){
            if (settings::fitness_per_iter){
                double fitness = population.GetFittest().GetFitness();
                fitness_per_iteration.push_back(fitness);
                
            }
        };

        void close(){
            if (settings::database_active){
                d.close();
            }
        };

        // ***********  GETS  ************
        Population& GetPopulation() {
            return population;
        };

        vector<Individual>& GetParents() {
            return parents;
        };

        Database& GetDatabase() {
            return d;
        }
        // ***********  SETS  ************
        void ReplacePopulation(Population &newpop){
            parents.clear();
            parents.resize(2);
            population = newpop;
        };
};

#endif