#ifndef __CITYGEN_HPP__
#define __CITYGEN_HPP__
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "settings.hpp"
#include "random.hpp"
#include "../../logger.hpp"
using namespace std;

vector<vector<double>> GenerateCities(string layout){
    bool circle;
    if (layout == "circle" || layout == "Circle"){
        circle = true;
    }else if(layout == "square" || layout == "Square"){
        circle = false;
    }else{
        //throw
        cerr << "[Invalid layout] "<<endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<double>> results;
    vector<double> cityx, cityy;
    Random rnd;
    ofstream Position;
    Log::Logger city_logger("CityLogger",Log::LEVEL_INFO);
    city_logger.info("Initializing cities...");
    if(settings::circle){
        Position.open("./outputs/circle/cityposition.dat");
        double x;
        for(unsigned i=0; i<settings::ncities; i++){
            x=rnd.Rannyu(0,2.*M_PI);
            Position<<i<<"\t";
            Position<<sin(x) <<"\t";
            Position<<cos(x) <<"\n";
            cityx.push_back(sin(x));
            cityy.push_back(cos(x));
        }
    }else{
        Position.open("./outputs/square/cityposition.dat");
        double tempx, tempy;
        for(unsigned i=0; i<settings::ncities; i++){
            tempx = rnd.Rannyu();
            tempy = rnd.Rannyu();
            Position<<i<<"\t";
            Position<<tempx<<"\t";
            Position<<tempy<<"\n";
            cityx.push_back(tempx);
            cityy.push_back(tempy);
        }
    }
    Position.close();
    results.push_back(cityx);
    results.push_back(cityy);
    settings::cities_generated = true;
    return results;
}

vector<unsigned> GetCityIndexes(){
    if (settings::cities_generated){
        ifstream positions;
        vector<unsigned> result;
        if (settings::circle){
            positions.open("outputs/circle/cityposition.dat");
        }else{
            positions.open("outputs/square/cityposition.dat");
        }
        int i;
        double x,y;
        while (positions >> i >> x >> y)
        {
            result.push_back(i);
        }
        positions.close();
        return result;
    }else{
        cerr << "[GetCityIndex] Error: Cannot request index without initializing cities. Exiting.."<<endl;
        exit(EXIT_FAILURE);
    }
}

vector<double> GetCityX(){
    if (settings::cities_generated){
        ifstream positions;
        vector<double> result;
        if (settings::circle){
            positions.open("outputs/circle/cityposition.dat");
        }else{
            positions.open("outputs/square/cityposition.dat");
        }
        int i;
        double x,y;
        while (positions >> i >> x >> y)
        {
            result.push_back(x);
        }
        positions.close();
        return result;
    }else{
        cerr << "[GetCityIndex] Error: Cannot request index without initializing cities. Exiting.."<<endl;
        exit(EXIT_FAILURE);
    }
}

vector<double> GetCityY(){
    if (settings::cities_generated){
        ifstream positions;
        vector<double> result;
        if (settings::circle){
            positions.open("outputs/circle/cityposition.dat");
        }else{
            positions.open("outputs/square/cityposition.dat");
        }
        int i;
        double x,y;
        while (positions >> i >> x >> y)
        {
            result.push_back(y);
        }
        positions.close();
        return result;
    }else{
        cerr << "[GetCityIndex] Error: Cannot request index without initializing cities. Exiting.."<<endl;
        exit(EXIT_FAILURE);
    }
}

#endif