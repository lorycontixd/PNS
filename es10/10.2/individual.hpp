#ifndef __INDIVIDUAL_HPP__
#define __INDIVIDUAL_HPP__
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "settings.hpp"
#include "exceptions.hpp"
using namespace std;

class Individual{
    /*
        Individual class -> Represents a solution to the problem solved by the Genetic Algorithm.

        genes: list of city indices.
    */
    private:
        vector<unsigned> genes;
        double beta;
        double fitness;
    protected:
    public:
        
        Individual(){
            beta = 0;
            fitness = 0;
            genes.resize(0);
            for (unsigned i = 1; i<settings::ncities; i++){
                genes.push_back(i);
            }
        };

        Individual(bool do_shuffle){
            beta = 0;
            genes.resize(0);
            for (unsigned j=0; j<settings::ncities; j++){
                genes.push_back(j);
            }
            if (do_shuffle){
                Shuffle(1,0);
            }
            Check();
        };

        Individual(double _beta, bool do_shuffle = true){
            beta = _beta;
            for (unsigned j=0; j<settings::ncities; j++){
                AddGene(j);
            }
            if (do_shuffle){
                Shuffle(1,0);
            }
            Check();
        };

        Individual(vector<unsigned> &newgenes){
            genes = newgenes;
            Check();
            CalculateFitness();
        };

        ~Individual(){};

        unsigned operator[] (unsigned index) {
            return this->genes.at(index);
        };

        bool operator>( Individual &other){
            this->CalculateFitness();
            return this->GetFitnessConst() > other.GetFitnessConst() ;
        };

        bool operator<( Individual &other){
            this->CalculateFitness();
            return this->GetFitnessConst()  < other.GetFitnessConst() ;
        };

        bool operator==( Individual &other){
            this->CalculateFitness();
            return (this->GetFitnessConst()  == other.GetFitnessConst()  && this->GetGenes() == other.GetGenes());
        };

        void operator=(const Individual &other){
            this->SetBeta(other.GetBeta());
            this->genes = other.genes;
            this->CalculateFitness();
        }

        double CalculateFitness(){
            double dist = 0;
            for (unsigned i=0;i<genes.size()-1;i++){
                //auto it = find(settings::CityIndex.begin(), settings::CityIndex.end(), genes[i]);
                //unsigned index = it - settings::CityIndex.begin();
                dist += settings::metric->norm(settings::CityX[genes[i]],settings::CityX[genes[i+1]],settings::CityY[genes[i]],settings::CityY[genes[i+1]]);
            }
            dist += settings::metric->norm(settings::CityX[genes.back()],settings::CityX[genes.back()],settings::CityY[genes[0]],settings::CityY[genes[0]]);
            fitness = dist;
            if (fitness == 0){
                throw FitnessError("individual");
            }
            return dist;
        };

        void Shuffle(unsigned first_index, unsigned from_last_index){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle( genes.begin()+first_index,genes.end()-from_last_index,default_random_engine(seed));
        };

        void Sort(){
            sort(genes.begin(),genes.end());
        };

        void Check(){ 
            /* Check for duplicate values in genes vector */
            if (genes.size()>0){
                vector<unsigned> copy(genes.size());
                partial_sort_copy(begin(genes), end(genes), begin(copy), end(copy));
                auto it = std::unique( copy.begin(), copy.end() );
                bool isunique = (it == copy.end() );
                if (!isunique){
                    ShowGenes();
                    throw IndividualCheckFailure("individual","Repetition");
                }
                if (genes[0]!=0){
                    // If the first element is not 0, swap it with the position of 0
                    auto it = std::find (genes.begin(), genes.end(), 0);
                    swap(genes[0], genes[std::distance(genes.begin(), it)]);   
                }
            }
            /* Check for city return */
        };

        // **********  GETS  **********
        double GetBeta() const {return beta;}
        void ShowFitness(){cout<<fitness<<endl;}
        double GetFitness() { if (fitness == 0){CalculateFitness();}return fitness; }
        double GetFitnessConst() const {return fitness;}
        vector<unsigned>& GetGenes() { return genes; }
        unsigned GetGene(unsigned index) const {return genes[index];}
        unsigned GetGenesSize() const {if (genes.size()!=0){return genes.size();}else{ throw GetEmptyError("individual","genes"); } }
        void ShowGenes() const {for (unsigned i = 0; i<genes.size(); i++){cout << genes[i]<<", ";}cout << 0 << endl;}

        // **********  SETS  **********
        void SetBeta( double _beta){ beta = _beta;}
        void SetFitness(double f){ fitness=f; }
        void SetGenes(const vector<unsigned>& g){
            genes.clear();
            for (unsigned i = 0; i<g.size(); i++){
                genes.push_back(g[i]);
            }
            //CalculateFitness();
        }
        void SetGene(unsigned index, unsigned value){genes[index]=value;}
        void AddGene(unsigned value) {genes.push_back(value);}
}; 

#endif