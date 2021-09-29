#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__
#include <iostream>
#include <cstdlib>
#include <tuple>
#include "database.hpp"
#include "metrics.hpp"
#include "../../ini_reader.hpp"
#include "../../functions.hpp"
using namespace std;

unsigned read_update(string layout){
    unsigned count;
    string countfile = "./outputs/"+layout+"/simulationcount.dat";
    ifstream readcount(countfile);
    readcount >> count;
    readcount.close();
    return count;
}

unsigned write_update(string layout, unsigned count){
    ofstream write("./outputs/"+layout+"/simulationcount.dat");
    write << count;
    write.close();
}

namespace settings{
    static unsigned ncities;
    static std::string layout;
    static bool circle;
    static double box;
    static std::string metric_type;
    static Metric *metric;
    static vector<unsigned> CityIndex;
    static vector<double> CityX; // Holds x coordinates of cities
    static vector<double> CityY; // Holds y coordinates of cities

    static unsigned ntemp;
    static double step;
    static unsigned iterations;
    
    static bool logger_debug;
    static bool data_debug;
    static bool fitness_per_iter;
    static std::string besttrip_filename;

    static std::string output_dir;

    // states
    static bool cities_generated;

};


void LoadSettings(string configfile){
    #if defined(SETTINGS_LOADED)
        #pragma warning(default:0)
    #else 
        INIReader reader(configfile);
        if (reader.ParseError() != 0) {
            cout << "Can't load "<<configfile<<"\n";
            exit(EXIT_FAILURE);
        }

        settings::ncities = std::stoi(reader.Get("simulation","ncities","32"));
        settings::layout = reader.Get("simulation","layout","circle");
        settings::box = std::stod(reader.Get("simulation","box","1"));
        settings::metric_type = reader.Get("simulation","metric","L2");
        if (settings::layout == "circle" ){
            settings::circle = true;
        }else if(settings::layout == "square"){
            settings::circle = false;
        }else{
            cerr << "[LoadSettings] Error: Invalid layout "<<settings::layout<<endl;
        }

        if (settings::metric_type=="L1"){
            settings::metric = new L1();
        }else if (settings::metric_type=="L2"){
            settings::metric = new L2();
        }else{
            cerr << "[LoadSettings] Error: Invalid metric "<<settings::metric_type<<endl;
            exit(EXIT_FAILURE);
        }

        settings::ntemp = std::stoi(reader.Get("simulation.temperature","N","2000"));
        settings::step = std::stod(reader.Get("simulation.temperature","step","1.003"));
        settings::iterations = std::stoi(reader.Get("simulation","iterations","1000"));

        settings::logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","true"));
        settings::data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
        settings::fitness_per_iter = general::conversion::to_bool(reader.Get("settings","fitness_per_iteration","true"));
        settings::besttrip_filename = reader.Get("outputs","besttrip_filename","");

        settings::output_dir = reader.Get("settings","base_dir","./outputs/"+settings::layout+"/");
        settings::cities_generated = false;

        #define SETTINGS_LOADED true
    #endif
}

auto PrintSettings(){
    cout << "Layout: "<<settings::layout<<endl;
    cout << "Ncities: "<<settings::ncities<<endl;
    cout << "Box: "<<settings::box<<endl;
    cout << "Metric: "<<settings::metric_type<<endl;
    cout << "Ntemp: "<<settings::ntemp<<endl;
    cout << "Beta step: "<<settings::step<<endl;
    cout << "Iterations: "<<settings::iterations<<endl<<endl;
}

void LoadDatabaseSettings(Database &db, unsigned nprocesses){
    if (db.IsConnected()){
        char *zErrMsg;
        
        tuple<string,string,string> key = make_tuple("ID","INT PRIMARY KEY","NOT NULL");
        tuple<string,string,string> _nproc = make_tuple("PROCESSES","INT","NOT NULL");
        tuple<string,string,string> _ncities = make_tuple("NCITIES","INTEGER","NOT NULL");
        tuple<string,string,string> _layout = make_tuple("LAYOUT","TEXT","NOT NULL");
        tuple<string,string,string> _box = make_tuple("BOX","REAL","NOT NULL");
        tuple<string,string,string> _metric_type = make_tuple("METRIC","TEXT","NOT NULL");
        tuple<string,string,string> _ntemp = make_tuple("NTEMP","INTEGER","NOT NULL");
        tuple<string,string,string> _beta_step = make_tuple("BETA_STEP","REAL","NOT NULL");
        tuple<string,string,string> _iters = make_tuple("ITERATIONS","INTEGER","NOT NULL");
        vector<tuple<string,string,string>> myvec = {key,_nproc,_ncities,_layout,_box,_metric_type,_ntemp,_beta_step,_iters};
        db.create_table("SETTINGS",myvec,true);
        int rc,count;
        rc = sqlite3_exec(db.GetDatabase(), "SELECT COUNT(*) FROM SETTINGS", countcallback, &count, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        string sql = "INSERT INTO SETTINGS (ID,PROCESSES,NCITIES,LAYOUT,BOX,METRIC,NTEMP,BETA_STEP,ITERATIONS) VALUES ("+to_string(count)+","+to_string(nprocesses)+","+to_string(settings::ncities)+",'"+settings::layout+"',"+to_string(settings::box)+",'"+settings::metric_type+"',"+to_string(settings::ntemp)+","+to_string(settings::step)+","+to_string(settings::iterations)+");";
        db.insert(sql);
        if (settings::logger_debug) cout << "Database settings loaded"<<endl;
    }
}

#endif