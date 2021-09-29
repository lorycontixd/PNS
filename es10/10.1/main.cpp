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
#include "../../logger.hpp"
using namespace std;



int main(int argc, char** argv){
    try{
        if (argc!=2){
            throw CommandlineArgumentError("main","Invalid parameter","config_file");
        }
        Random *rnd = new Random();
        GeneticAlgorithm *model = new GeneticAlgorithm();
        model->Input(argv[1]);
        Individual old_path(true);
        Population population;
        Log::Logger main_logger("MainLogger",Log::LEVEL_DEBUG);
        main_logger.info("Starting simulation...");
        for (size_t i=0; i<settings::ntemp ;i++){
            model->SetBeta(model->GetBeta()*settings::step);
            if (i%100==0){
                string msg = "i= "+to_string(i)+"\tbeta= "+to_string(model->GetBeta());
                main_logger.debug(msg);
                //cout << "i= "<<i<<"\tbeta= "<<model->GetBeta()<<endl;
            }
            for (size_t j=0; j<settings::iterations; j++){
                Individual new_path = old_path;
                CompleteMutation(new_path,rnd);
                new_path.Check();
                double oldfitness = old_path.CalculateFitness();
                double newfitness = new_path.CalculateFitness();
                double prob = exp( - model->GetBeta() * (newfitness - oldfitness));
                if ( prob >= rnd->Rannyu()){
                    old_path = new_path;
                    old_path.Check();
                }
            }
            old_path.SetBeta(model->GetBeta());
            old_path.CalculateFitness();
            model->GetPopulation().AddIndividual(old_path);
        }
        cout << "Saved " << model->GetPopulation().GetIndividualsSize() << " paths"<< endl;
        model->SaveConfig();
    }catch (const std::exception& e){ cerr << e.what() << endl ;}
    return 0;
}
    
