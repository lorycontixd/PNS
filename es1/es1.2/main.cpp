#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <typeinfo> //check type of variable -> typeid(var).name()
#include <vector>
#include "random.h"
#include "../../ini_reader.h"
#include "../../functions.h"
using namespace std;

int main (int argc, char *argv[]){
   string filename = check_filename_input(argc,argv);
   INIReader reader(filename);
   if (reader.ParseError() != 0) {
      std::cout << "Can't load "<<filename<<"\n";
      return 1;
   }
   int M = stoi(reader.Get("simulation","throws","UNKNOWN"));
   string numbers = reader.Get("simulation","numbers","UNKNOWN");
   numbers.erase(std::remove(numbers.begin(), numbers.end(), '['), numbers.end());
   numbers.erase(std::remove(numbers.begin(), numbers.end(), ']'), numbers.end());
   string outputfiles = reader.Get("settings","input_files","UNKNOWN");
   bool logger_debug = to_bool(reader.Get("settings","logger_debug","UNKNOWN"));
   bool data_debug = to_bool(reader.Get("settings","data_debug","UNKNOWN"));
   string base_dir = reader.Get("settings","base_dir","UNKNOWN");
   vector<string> files = split_string(outputfiles);
   
   vector<int> _numbers = split_int(numbers,",");
   cout << "size; "<<_numbers.size()<<endl;
   vector<vector<double>> results(_numbers.size(),vector<double>(M));
   vector<vector<vector<double>>> container;
   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("../Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("../seed.in");
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
   double sum,avg,rand;
   for (int x = 0;x<files.size();x++){
      cout << "X: "<<x<<endl;
      for (int k=0;k<_numbers.size();k++){
         for (int i = 0; i<M;i++){
            sum = 0;
            for (int j = 0;j<_numbers[k];j++){
                  /*case 0: rand = rnd.Rannyu();
                  case 1: rand = rnd.Exp(1);
                  case 2: rand = rnd.Lorentz(0,1);
                  default: rand = rnd.Rannyu();*/
                  if (x==0){
                     rand = rnd.Rannyu();
                  }else if (x==1){
                     rand = rnd.Exp(1);
                  }else if (x==2){
                     rand = rnd.Lorentz(0,1);
                  }else{
                     cerr << "Error: x cannot be "<<x<<endl;
                  }
               if (data_debug){cout << "Extracted "<<rand<<endl;}
               sum += rand;
            }
            if (data_debug){cout << avg << endl;}
            avg = sum/numbers[k];
            results[k][i] = avg;
         }
      }
      container.push_back(results);
   }
   

   check_dir(base_dir,true);
   for (int k = 0;k<container.size();k++){
      ofstream out(base_dir+"/"+files[k]);
      for (int i = 0;i<container[k].size();i++) { 
         for (int j = 0;j<container[k][i].size();j++){
            //if (j==10){break;};
            out << container[k][i][j]<<"\t";
         }
         out << "\n";
      }
      if (logger_debug){cout<<"Data written to file: "<<files[k]<<endl;}
   }
   

   rnd.SaveSeed();
   return 0;
}