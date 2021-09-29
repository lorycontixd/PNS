#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__
#include <random> 
#include <map>
#include <utility>
#include <cassert>
#include "individual.hpp"
#include "settings.hpp"

bool comparator( Individual& lhs,  Individual& rhs) {
   return lhs.GetFitnessConst() < rhs.GetFitnessConst();
}


class Population{
    /* Class Population
    Represents a population (set) of Individuals (solutions to the GA problem)

    The key attribute of this class is the `individuals` member, which is a container of Individuals.
    The class also has two Individual variables where the objects with best fitness scores are saved.

    Constructors:
        --> Default: Sets individuals to size 0.
        --> Size(int): Initializes individuals vector with size

    Methods:
        --> CalculateFitness(bool)
            Iterates through individuals and calculates fitness of their genes

            Parameters:
                - sort (bool : false): sort the returned fitnesses
            Returns:
                - fitnesses: vector of fitness values


        --> SetInitial(bool)
            Sets the population as the initial one of the genetic algorithm

            Parameters:
                - do_shuffle(bool : true): shuffles the genes of each individual of the starting population
            Returns:

        --> SortIndividuals(bool,bool)
            Sort the individuals of the population based on the fitness levels

            Parameters:
                - set_fittests(bool : true): saves the best individuals after sorting
                - get_copy(bool : false): sort a copy instead to preserve original individuals vector
            Returns:
                - sorted copy of individuals
    */
    private:
        vector<Individual> individuals;
        
        Individual fittest;
        Individual secondfittest;
        bool is_sorted;
    protected:
    public:
        
        Population(){
            individuals.resize(0);
        };
        Population(unsigned size){
            individuals.resize(size);
        }
        ~Population(){};

        void operator=(Population &p){
            this->fittest = p.GetFittest();
            this->secondfittest = p.GetSecondFittest();
            this->individuals = p.GetIndividuals();
        };

        auto CalculateFitnesses(bool _sort = false){
            vector<double> fitnesses;
            for (unsigned i = 0; i<individuals.size(); i++){
                fitnesses.push_back(individuals[i].GetFitness());
            }
            if (_sort){
                sort(fitnesses.begin(),fitnesses.end());
            }
            SortIndividuals();
            return fitnesses;
        };

        vector<Individual>& SortIndividuals(bool set_fittests = true, bool get_copy = false){
            if (get_copy){
                vector<Individual> veccopy(individuals);
                sort(veccopy.begin(),veccopy.end(),&comparator);
                if (set_fittests){
                    fittest = individuals[0];
                    secondfittest = individuals[1];
                }
                return veccopy;
            }else{
                sort(individuals.begin(), individuals.end(), &comparator);
                is_sorted = true;
                if (set_fittests){
                    fittest = individuals[0];
                    secondfittest = individuals[1];
                }
                return individuals;
            }
            
        };

        void ShowFitnesses(bool ordered = true) const {
            if (!ordered){
                for (unsigned i=0; i<individuals.size(); i++){
                    cout << individuals[i].GetFitnessConst()<<", ";
                }
                cout << endl << endl;
            }else{
                vector<double> fitnesses;
                for (unsigned i=0;i<individuals.size();i++){
                    fitnesses.push_back(individuals[i].GetFitnessConst());
                }
                sort(fitnesses.begin(),fitnesses.end());
                for (double d : fitnesses){
                    cout <<d <<", ";
                }
            }
        };

        void PrintPath(bool ordered = true){
            cout << "Printing individuals path "<<endl;
            cout << "Is sorted by fitness: "<<boolalpha << is_sorted << endl;
            for (unsigned i=0; i<individuals.size(); i++){
                cout << "Iteration "<<i<<"/"<<individuals.size()<<endl;
                individuals[i].ShowGenes();
                individuals[i].ShowFitness();
                cout << endl;
            }
        };

        // ***********  GETS  ************
        vector<Individual> GetIndividuals() {
            return individuals;
        };

        vector<double> GetFitnesses() {
            vector<double> f;
            
            cout << "Fitnesses: "<<f.size()<<endl;
            return f;
        };

        unsigned GetIndividualsSize() const {
            return individuals.size();
        };

        Individual& GetFittest() {
            return fittest;
        };

        Individual& GetSecondFittest() {
            return secondfittest;
        };

        // ***********  SETS  ************
        void AddIndividual(Individual &i){
            individuals.push_back(i);
        };

        void SetIndividual(unsigned index, Individual &i){
            individuals[index] = i;
        };
};

#endif