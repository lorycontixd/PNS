#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "settings.hpp"
#include "population.hpp"
#include "individual.hpp"
#include "genetic.hpp"
#include "exceptions.hpp"
#include "random.hpp"
#include "mutations.hpp"
#include "../../logger.hpp"
using namespace std;
using namespace std::chrono;

const char separator   = ' ';
const int nameWidth    = 6;
const int numWidth     = 8;


auto get_cpp_version(){
    if (__cplusplus == 201703L) return "C++17";
    else if (__cplusplus == 201402L) return "C++14";
    else if (__cplusplus == 201103L) return "C++11\n";
    else if (__cplusplus == 199711L) return "C++98\n";
    else std::cout << "pre-standard C++";
}


int main(int argc, char** argv){
    try{
        if (argc!=2){
            throw CommandlineArgumentError("main","Invalid parameter","config_file");
        }

        // MPI variables
        const int root = 0;
        int mpisize, myrank;
        int buf;
        int ierr; //Get the error of MPI commands
        double *irecv, *irecv_time;
        double isend, isend_time;
        MPI_Group world_group;

        MPI_Init(&argc,&argv);
        if (ierr != 0){
            cerr << "TSP - Simulated Annhealing Error"<<endl;
            cerr << "MPI_Init returned code "<<ierr<<endl;
            exit(EXIT_FAILURE);
        }

        // Get the number of processes
        ierr = MPI_Comm_size( MPI_COMM_WORLD, &mpisize);
        // Get the rank of this process
        ierr = MPI_Comm_rank( MPI_COMM_WORLD, &myrank);
        
        irecv = new double[mpisize];
        irecv_time = new double[mpisize];
        if (myrank==0){
            cout << "\nTSP Simulated Annhealing - MASTER PROCESS" << endl;
            cout << "C++ version: "<<get_cpp_version()<<endl;
            cout << "Compiled on: "<<__DATE__ << " at " << __TIME__ << "."<<endl<<endl;
            cout << "===> MPI STATS: "<<endl;
            cout << "Using "<<mpisize<< " processes."<<endl;
        }
        ierr = MPI_Comm_group(MPI_COMM_WORLD, &world_group);
        MPI_Barrier(MPI_COMM_WORLD);
        Random *rnd = new Random();
        GeneticAlgorithm *model = new GeneticAlgorithm(mpisize, myrank);
        model->Input(argv[1]);

        string databasedir = "outputs/databases/";
        fs::create_directory(databasedir);
        unsigned i = general::filesystem::count_files(databasedir);
        string databasename = databasedir + "db_" + to_string(i);

        Individual old_path(true);
        Population population;
        // Time execution
        auto start = high_resolution_clock::now();
        for (size_t i=0; i<settings::ntemp ;i++){
            model->SetBeta(model->GetBeta()*settings::step);
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
        MPI_Barrier(MPI_COMM_WORLD); // Wait for all processes to catch up

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        double ms = duration.count();
        isend_time = ms;

        Individual best = model->GetPopulation().GetIndividuals().back();
        double bestfit = best.GetFitnessConst();
        isend = bestfit; // Prepare fitness value to be sent
        MPI_Gather(&isend,1,MPI_DOUBLE,irecv,1,MPI_DOUBLE,root,MPI_COMM_WORLD);
        MPI_Gather(&isend_time,1,MPI_DOUBLE,irecv_time,1,MPI_DOUBLE,root,MPI_COMM_WORLD);
        if (myrank==root){
            Database d(databasename);
            d.connect();
            LoadDatabaseSettings(d, mpisize);
            for (int i=0; i<mpisize; i++){
                cout << i << " - "<<irecv[i]<<endl;;
            }
            cout << endl;

            auto res = *min_element(irecv,irecv+mpisize);
            unsigned iter = 0;
            for (int i=0; i<mpisize; i++){
                if (irecv[i] == res){
                    iter = i;
                }
            }
            buf = iter;
            cout << "Minimum value for process "<<iter<<" of value "<<res<<endl;
 
            // results
            tuple<string,string,string> tuple_proc = make_tuple("PROCESS","INTEGER","NOT NULL");
            tuple<string,string,string> tuple_fitness = make_tuple("FITNESS","REAL","NOT NULL");
            tuple<string,string,string> tuple_time = make_tuple("TIME","REAL","NOT NULL");
            vector<tuple<string,string,string>> cols_results = {tuple_proc, tuple_fitness, tuple_time};
            d.create_table("RESULTS",cols_results,true);
            string sql = "INSERT INTO RESULTS (PROCESS,FITNESS,TIME) VALUES ";
            string temp;
            for (int i=0; i<mpisize; i++){
                temp += "("+to_string(i) + "," + to_string(irecv[i]) + "," + to_string(irecv_time[i])+"),";
            }
            temp = temp.substr(0,temp.size()-1);
            temp += ";";
            sql += temp;
            d.insert(sql);
            d.close();
        }

        // Telling everyone who the best process is
        
        ierr = MPI_Bcast(&buf, 1, MPI_INT, root, MPI_COMM_WORLD);
        //cout << "I am process "<<myrank<<". My fitness value is "<<bestfit<<". Best process is "<<buf<<endl;        
        if (myrank==buf){
            Database d(databasename);
            d.connect();

            tuple<string,string,string> tuple_gene = make_tuple("GENE","INTEGER PRIMARY KEY","NOT NULL");
            tuple<string,string,string> tuple_cityx = make_tuple("CITYX","REAL","NOT NULL");
            tuple<string,string,string> tuple_cityy = make_tuple("CITYY","REAL","NOT NULL");
            vector<tuple<string,string,string>> cols_genes = {tuple_gene,tuple_cityx,tuple_cityy};
            d.create_table("BEST",cols_genes,true);
            string sql = "INSERT INTO BEST (GENE,CITYX,CITYY) VALUES ";
            vector<unsigned> genes = best.GetGenes();
            string temp;
            for (int i=0; i<genes.size(); i++){
                temp += "("+to_string(genes[i])+","+to_string(settings::CityX[genes[i]])+","+to_string(settings::CityY[genes[i]])+"),";
            }
            temp = temp.substr(0,temp.size()-1);
            temp += ";";
            sql += temp;
            d.insert(sql);
            d.close();
        } 

        MPI_Finalize();
        exit(EXIT_SUCCESS);
        
    }catch (const std::exception& e){ cerr << e.what() << endl ;}
    return 0;
}
    
