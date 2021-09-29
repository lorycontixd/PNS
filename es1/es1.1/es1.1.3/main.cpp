#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "random.h"
#include <cmath>
#include "../../../ini_reader.h"
#include "../../../functions.h"
using namespace std;
 
int main (int argc, char *argv[]){
   
   string filename = check_filename_input(argc,argv);
   INIReader reader(filename);
   if (reader.ParseError() != 0) {
      std::cout << "Can't load "<<filename<<"\n";
      return 1;
   }
   
   int N = stoi(reader.Get("simulation","numbers","10000"));
   int M = stoi(reader.Get("simulation","blocks","100"));
   string outputfile = reader.Get("settings","input_file","data.dat");
   bool logger_debug = to_bool(reader.Get("settings","logger_debug","true"));
   bool data_debug = to_bool(reader.Get("settings","data_debug","false"));
   cout << "Total extractions: "<<N<<endl;
   cout << "Intervals: "<<M<<endl;
   int L = int(N/M);
   if (logger_debug){ cout << "L= "<<L<<endl;}

   vector<double> randoms(N,0.0);
   vector<double> chi2(M,0.0);
   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("../../Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("../../seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   //Save 10^6 random numbers between 0 and 1
   for (int i = 0;i<N;i++){
      randoms[i] = rnd.Rannyu();
   }

   ofstream out(outputfile);
   for (int i = 0; i < M; i++){
      for (int j = 0;j<L;j++){
         int k = j + i*M;
         double rand = randoms[k];
         chi2[i] = (chi2[i] + pow((rand-N/M),2))/(N/M);
      }
      if (data_debug) {cout << chi2[i] <<endl;}
      out << i <<"\t"<<chi2[i]<<endl;
   }
   out.close();

   if (logger_debug){cout<<"Data written to file: "<<outputfile<<endl;}
   rnd.SaveSeed();
   return 0;
}