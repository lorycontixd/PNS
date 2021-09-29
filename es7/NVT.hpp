/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __NVT_HPP__
#define __NVT_HPP__

//Random numbers
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "random.hpp"
#include "../ini_reader.hpp"
#include "../datablocking.hpp"
#include "../functions.hpp"
using namespace std;

class NVT{
    private:
        //parameters, observables
        const int m_props=1000;
        int n_props, iv, iw, igofr;
        double vtail,ptail,bin_size,nbins,sd;
        vector<double> walker;
    
        // averages
        vector<double> blk_av, glob_av, glob_av2;
        double blk_norm,accepted,attempted;
        double stima_pot,stima_pres,stima_gofr,err_pot,err_press,err_gdir,err_gofr;

        //configuration
        string matter_state;
        vector<vector<double>> pos;

        // thermodynamical state
        int npart;
        double beta,temp,vol,rho,box,rcut;

        // simulation
        int nstep, nblk;
        double delta;

        //pigreco
        const double pi=3.1415927;
        Random *rnd;

        //settings
        bool logger_debug, data_debug;
        bool xyz;
        string outputdir;

        //simulation state
        bool initialized;
        bool equilibrated;

        double acceptance;
        unsigned nacc, ntot;

        void PrepareVectors(){
            walker.resize(m_props);
            blk_av.resize(m_props);
            glob_av.resize(m_props);
            glob_av2.resize(m_props);
            if (npart>0){
                pos.resize(3, vector<double>(npart));
            }else{
                cerr << "[NVT] Error: Loading vector with no particles" << endl;
                exit(EXIT_FAILURE);
            }
        };

        void PrepareVariables(){
            nacc = ntot = 0;
        }


    public:
        NVT(){
            initialized = false;
            rnd = new Random();
        }

        void Input(string configfile){
            ifstream ReadConf;
            INIReader reader(configfile);
            
            //default values set to solid
            matter_state = reader.Get("simulation","name","solid");
            temp = stod(reader.Get("simulation","temp","1.1"));
            npart = stoi(reader.Get("simulation","npart","108"));
            rho = stod(reader.Get("simulation","rho","1.1"));
            rcut = stod(reader.Get("simulation","rcut","2.2"));
            delta = stod(reader.Get("simulation","delta","0.12"));
            nblk = stoi(reader.Get("simulation","nblk","10"));
            nstep = stoi(reader.Get("simulation","nstep","1000"));
            logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","true"));
            xyz = general::conversion::to_bool(reader.Get("settings","xyz","false"));
            experimental::filesystem::create_directory("outputs/");
            outputdir = "outputs/"+matter_state+"/";
            experimental::filesystem::create_directory(outputdir);

            cout << "Classic Lennard-Jones fluid        " << endl;
            cout << "Monte Carlo simulation             " << endl << endl;
            cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
            cout << "Boltzmann weight exp(- beta * sum_{i<j} v(r_ij) ), beta = 1/T " << endl << endl;
            cout << "The program uses Lennard-Jones units " << endl;
            beta = 1.0/temp;
            cout << "Temperature = " << temp << endl;
            cout << "Number of particles = " << npart << endl;
            cout << "Density of particles = " << rho << endl;
            vol = (double)npart/rho;
            box = pow(vol,1.0/3.0);
            cout << "Volume of the simulation box = " << vol << endl;
            cout << "Edge of the simulation box = " << box << endl;
            cout << "Cutoff of the interatomic potential = " << rcut << endl << endl;
                
            //Tail corrections for potential energy and pressure
            vtail = (8.0*pi*rho)/(9.0*pow(rcut,9)) - (8.0*pi*rho)/(3.0*pow(rcut,3));
            ptail = (32.0*pi*rho)/(9.0*pow(rcut,9)) - (16.0*pi*rho)/(3.0*pow(rcut,3));
            cout << "Tail correction for the potential energy = " << vtail << endl;
            cout << "Tail correction for the virial           = " << ptail << endl; 
            cout << "The program perform Metropolis moves with uniform translations" << endl;
            cout << "Moves parameter = " << delta << endl;
            cout << "Number of blocks = " << nblk << endl;
            cout << "Number of steps in one block = " << nstep << endl << endl;

            PrepareVectors();
            PrepareVariables();

            //PrepareFiles(); 
            //Prepare arrays for measurements
            iv = 0; //Potential energy
            iw = 1; //Virial
            
            n_props = 2; //Number of observables

            //measurement of g(r)
            igofr = 2;
            nbins = 100;
            n_props = n_props + nbins;
            bin_size = (box/2.0)/(double)nbins;
            //Read initia   l configuration
            cout << "Test random number: "<<rnd->Rannyu()<<endl;
            cout << "Read initial configuration from file config.0 " << endl << endl;
            ReadConf.open("configfiles/config.0");
            double tempx, tempy, tempz;
            for (int i=0; i<npart; ++i)
            {
                ReadConf >> tempx >> tempy >> tempz;
                tempx = Pbc( tempx * box );
                tempx = Pbc( tempx * box );
                tempx = Pbc( tempx * box );
            }
            ReadConf.close();
            initialized = true;
        };

        auto calculate_acceptance(){
            acceptance = double(nacc)/double(ntot);
        };

        double interaction_energy

        auto make_pass(double delta){
            unsigned index = rnd->Rannyu(0,pos.size());
            vector<double> selected = pos[index];
            vector<double> newpos;
            double A = 0;
            for (unsigned i=0; selected.size(); i++){
                newpos.push_back(rnd->Rannyu(selected[i]-delta/2.,selected[i]+delta/2.));
            }
            A = interaction_energy(selected, newpos);
            double r = rnd->Rannyu();
            bool accepted;
            if (r<=A){
                for(int i=0;i<3;i++){
                    pos[index][i]=newpos[i];
                }
		        nacc++; 
                accepted = true;
            }else{
                accepted = false;    
            }
            ntot++;
            calculate_acceptance();
            return accepted;
        };

        auto equilibrate(unsigned equilibration_steps){

        };

        double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
            double y = r - box * rint(r/box);
            return y;
        };

        double Error(double sum, double sum2, int iblk){
            if( iblk == 1 ) return 0.0;
            else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
        };
        
};



#endif

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/