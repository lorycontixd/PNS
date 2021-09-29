#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <sstream>
#include "random.hpp"
#include "../../../ini_reader.hpp"
#include "../../../functions.hpp"
using namespace std;

double error(vector<double>& AV,vector<double>& AV2,int n){
   if (n==0){
      return 0;
   }else{
      return sqrt( (AV2[n] - pow(AV[n],2) )/n);
   }
}

int main (int argc, char *argv[]){
   if (argc!=2){
      cerr << "Program requires parameter <config_file>." <<endl;
      exit(EXIT_FAILURE);
   }
   string filename = argv[1];
   INIReader reader(filename);
   if (reader.ParseError() != 0) {
      cout << "Can't load "<<filename<<"\n";
      exit(EXIT_FAILURE);
   }
   int M = stoi(reader.Get("simulation","runs","10000"));
   int N = stoi(reader.Get("simulation","blocks","100"));
   string outputfile = reader.Get("settings","input_file","UNKNOWN");
   bool logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","UNKNOWN"));
   bool data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","UNKNOWN"));

   if (logger_debug){
      printSettings(reader);
   }

   if (M%N!=0){
      cerr << "Please select a number of throws multiple for number of blocks."<<endl;
      exit(EXIT_FAILURE);
   }
   int L = M/N;
   vector<double> r(M);
   vector<double> _ave(N);
   vector<double> _ave2(N);
   vector<double> _ave_prog(N);
   vector<double> _ave2_prog(N);
   vector<double> _error(N);
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
   //In questo for, carico M numeri casuali
   for (int i=0;i<M;i++){
      r[i] = rnd.Rannyu();
   }

   ofstream stream("outputs/temp.dat");
   //in questo for, calcolo le medie degli N blocchi.
   for(int i=0; i<N; i++){
      float sum=0;
      int k=0;
      for(int j=0;j<L;j++){
         k = j+i*L; //MI SERVE PER CAMBIARE I NUMERI CASUALI in ogni blocco
         sum+=r[k];
      }
      _ave[i] = double(sum/L);
      if (data_debug){cout << "Ave["<<i<<"] = "<<_ave[i]<<endl;}
      stream << _ave[i]<<endl;
      _ave2[i] = pow(_ave[i],2);
   }
   stream.close();

   for (int i = 0;i<N;i++){
      for (int j = 0;j<i+1; j++){
         _ave_prog.at(i)+=_ave[j];
         _ave2_prog.at(i)+= _ave2[j];
      }
      _ave_prog[i] = double(_ave_prog[i] / (i+1));
      _ave2_prog[i] = double(_ave2_prog[i] / (i+1));
      _error[i] = error(_ave_prog,_ave2_prog,i);

      if (data_debug){
         cout << "Sum: "<<_ave_prog[i]<<endl;
         cout << "Sum^2: "<<_ave2_prog[i]<<endl;
         cout << "Error: "<<_error[i]<<endl<<endl;
      }
   }

   if (_ave_prog.size()!=_ave2_prog.size()){
      cerr << "RuntimeError: arrays _sum and _sum2 must have the same size."<<endl;
      exit(EXIT_FAILURE);
   }
   
   ofstream output(outputfile);
   for (int i = 0; i<_ave_prog.size();i++){
      output << i <<"\t"<< _ave_prog[i] << "\t" << _error[i] << endl;
   }
   if (logger_debug){
      cout << "Written to file: "<<outputfile<<"!"<<endl;
   }
   
   rnd.SaveSeed();
   return 0;
}
