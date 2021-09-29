#include <iostream>
#include <cstdlib>
#include <cmath>
#include "settings.hpp"
#include "population.hpp"
#include "individual.hpp"
#include "genetic.hpp"
#include "exceptions.hpp"
#include "mutations.hpp"
#include "database.hpp"
using namespace std;



int main(int argc, char** argv){
    if (argc!=2){
        throw CommandlineArgumentError("main","Invalid parameter","config_file");
    }
    Random rnd;
    GeneticAlgorithm *model = new GeneticAlgorithm();
    model->Input(argv[1]);
    model->GetPopulation().CalculateFitnesses();
    //i<settings::max_populations
    for (unsigned i=0; i<settings::max_populations ;i++){
        Population newpop;
        model->GetPopulation().CalculateFitnesses();
        while (newpop.GetIndividualsSize() < settings::max_individuals){
            model->GetPopulation().SortIndividuals();
            model->Select();
            model->Mutation(0.1);
            vector<Individual> sons = model->Crossover(0.6);
            newpop.AddIndividual(sons[0]);
            newpop.AddIndividual(sons[1]);
        }
        newpop.CalculateFitnesses();
        newpop.SortIndividuals();
        vector<Individual> results = newpop.GetIndividuals();
        model->ReplacePopulation(newpop);
        model->SaveTempFittest();
    }
    model->SaveConfig();
    model->close();
    cout << "Best fitness: "<<model->GetPopulation().GetFittest().GetFitnessConst()<<endl;
    return 0;
}