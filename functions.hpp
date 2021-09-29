#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <filesystem>
#include <numeric>
#include <cmath>
#include <vector>
#include <sys/stat.h>
#include "ini_reader.hpp"
#if __cplusplus >= 201703L // C++17 and later 
   #include <string_view>
#endif
using namespace std;
namespace fs = std::filesystem;

//******************************************************************************************
//*************************************  GENERAL  ******************************************
//******************************************************************************************
namespace general{
   namespace filesystem{
      auto count_files(string path){
         auto dirIter = fs::directory_iterator(path);
         int fileCount = 0;

         for (auto& entry : dirIter)
         {
            ++fileCount;
         }
         return fileCount;
      }
   }

   namespace conversion{
      /* Group of functions needed for type conversion
      -> to_bool: accepts a string and converts it into a boolean value
      -> bool_to_string: returns a boolean from a string. if string_repr is true, it returns the boolean value as a word
      */

      bool to_bool(std::string str) {
         std::transform(str.begin(), str.end(), str.begin(), ::tolower);
         std::istringstream is(str);
         bool b;
         is >> std::boolalpha >> b;
         return b;
      }

      string bool_to_string(bool b,bool string_repr = true){
         if (!string_repr){
            return to_string(b);
         }else{
            return b ? "true" : "false";
         }
      }
   }

   namespace input{
      /* Set of functions to validate some general input
      -> check_config_input: requests that the main program is given a config file as input
      */

      string check_config_input(int argc,char** argv){
         if (argc!=2){
            cerr << "Program requires parameter <config_file>." <<endl;
            exit(EXIT_FAILURE);
         }
         string filename = argv[1];
         return filename;
      }
   }

   namespace stream{
      /* Utility functions for writing and reading files
      -> ReadFile: returns a vector of strings which contains each line of the file
      -> UpdateRestartFile: reads file named restart.dat and increments it by 1. (used in programs with restart parameter)
      */

      static vector<string> ReadFile(string filename){
         ifstream read(filename);
         string msg = "Error reading "+filename;
         if (!read.is_open() || read.fail()){
               cerr << msg << endl;
               exit(EXIT_FAILURE);
         }
         vector<string> lines;
         string line;
         while (getline(read, line))
         {
               lines.push_back(line);
         }
         return lines;
      }

      static void UpdateRestartFile(){
         ifstream FileStream("restart.dat");
         int value;
         FileStream >> value;
         FileStream.close();
         ofstream ofs;
         ofs.open("restart.dat");
         ofs << value+1;
         ofs.close();
      }
   }

   namespace strings{
      /* Set of functions that work with strings
      -> split_string: returns a list of substrings from a string separated by a given delimiter
      -> replace_substring: replaces a piece of string with another one
      -> split_int: returns a list of integers encoded in a string and separated by a given delimiter (e.g. "1,2,3,4")
      */

      vector<string> split_string(string s, string delimiter=","){
         vector<string> chars = {"{","}","[","]","(",")"};
         vector<string> result;
         size_t pos = 0;
         string token;
         while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            for (unsigned i = 0;i<chars.size();i++){
               token.erase(std::remove(token.begin(), token.end(), chars[i].c_str()[0]), token.end());
            }
            result.push_back(token);
            s.erase(0, pos + delimiter.length());
         }
         return result;
      }

      // replace a substring of a string with another substring
      bool replace_substring(std::string& str, const std::string& from, const std::string& to) {
         size_t start_pos = str.find(from);
         if(start_pos == std::string::npos)
            return false;
         str.replace(start_pos, from.length(), to);
         return true;
      }

      //
      vector<int> split_int(string s,string delimiter=","){
         vector<int> result;
         size_t pos = 0;
         string token;
         while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            result.push_back(stoi(token));
            s.erase(0, pos + delimiter.length());
         }
         return result;
      }

      string upper(string& str){
         int len = str.size(); 
         char b;

         for (int i = 0; i < len; i++){
            b = str[i]; 
            b = toupper(b); 
            // b = to lower(b); //alternately 
            str[i] = b;    
         } 
         return str;
      }

      static bool endsWith(std::string_view str, std::string_view suffix)
      {
         return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
      }
   } // end general->string
} // end general
   

   
namespace console{
   /* Functions that write outputs to the console
   -> newlines: print a given amount of new lines in the console
   -> ConsoleHeader: print a nicely formatted header message in the console
      - title(str): string representing the header text
      - character(char): character used to format the header message
      - length(int,30): total length of the message (includes text and char formatter)
      - beforelines(int,0): print a number of empty lines before the header
      - afterlines(int,1): print a number of empty lines after the header
      
   -> ConsoleTitle: print a nicely formatted title message in the console.
   Titles are a considered a subheader, which means are lower in rank than a header
   The parameters of ConsoleTitle are the same as the ones for the ConsoleHeader function.
   */

   void newlines(unsigned lines=1){
      for (unsigned i = 0; i<lines; i++){
         cout << "" << endl;
      }
   }

   void ConsoleHeader(string title,const char* character, int length = 30, int beforelines=0, int afterlines=1){
      int _size = title.length();
      int _size2 = length - _size - 4;
      if (_size2%2==1){
            length++;
      }
      if (_size2<=0){
            cerr << "Not enough space to write title. Increase length or shorten title. "<<endl;
            exit(EXIT_FAILURE);
      }
      int i;
      string templine = "";
      string textline = "";
      
      for (i=0;i<length;i++) templine += character;
      for (i=0;i<_size2/2;i++) textline += character;
      textline = textline +"  "+title+"  ";
      for (i=0;i<_size2/2;i++) textline += character;
      string final;
      for (i=0;i<beforelines;i++) final+="\n";
      final = templine+"\n"+textline+"\n"+templine;
      for (i=0;i<afterlines;i++) final+="\n";
      
      cout << final << flush;
   }

   static void ConsoleTitle(string title, const char* character, int length=30,int beforelines = 0,int afterlines=2){
      int _size = title.length();
      int _size2 = length - _size - 4;
      if (_size2%2==1){
            length++;
      }
      if (_size2<=0){
            cerr << "Not enough space to write title. Increase length or shorten title. "<<endl;
            exit(EXIT_FAILURE);
      }
      int i;
      string textline = "";
      
      for (i=0;i<beforelines;i++) textline+="\n";
      for (i=0;i<_size2/2;i++) textline += character;
      textline = textline +"  "+title+"  ";
      for (i=0;i<_size2/2;i++) textline += character;
      for (i=0;i<afterlines;i++) textline+="\n";
      
      cout<<textline<<flush;
   }
}
   




//******************************************************************************************
//***************************************  MATHS  ******************************************
//******************************************************************************************

namespace maths{
   /* Utility maths functions.
   */
  
   double mean(vector<double>& v){
      auto n = v.size(); 
      float average = 0.0f;
      if ( n != 0) {
         average = accumulate( v.begin(), v.end(), 0.0) / n; 
      }
      return average;
   }

   //vettore di chi quadri
   vector<double> chi_squared(vector<double>& v, double expected_value){
      vector<double> chis;
      for (vector<double>::const_iterator i = v.begin(); i != v.end(); ++i){
         chis.push_back(pow((*i - expected_value),2)/expected_value);
      }
      return chis;
   }

   //media di un vettore di chi quadri
   double mean_chi_squared(vector<double>& v, double expected_value){
      vector<double> chi = chi_squared(v,expected_value);
      return mean(chi);
   }
}



/*
double progressive_mean(vector<double>& v, unsigned i){
   vector<double> temp(i,0.0);
   for ()
}*/

//******************************************************************************************
//************************************  INI READER  ****************************************
//******************************************************************************************


string sections(INIReader &reader)
{
   stringstream ss;
   set<std::string> sections = reader.Sections();
   for (set<string>::iterator it = sections.begin(); it != sections.end(); ++it)
      ss << *it << ",";
   return ss.str();
}


void printSettings(INIReader reader){
   cout << "Config loaded from file.."<<endl;
   cout << "Sections: "<<sections(reader)<<endl;
   cout << "- Runs: "<<reader.Get("simulation","runs","UNKNOWN")<<endl;
   cout << "- Blocks: "<<reader.Get("simulation","blocks","UNKNOWN")<<endl;
   cout << "- Debug mode (Logger): "<<reader.Get("settings","logger_debug","UNKNOWN")<<endl;
   cout << "- Debug mode (Data): "<<reader.Get("settings","logger_debug","UNKNOWN")<<endl;
   cout << "- Data File: "<<reader.Get("settings","input_file","UNKNOWN")<<endl;
   cout << " "<<endl;
}

#endif