#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__
#include <iostream>
#include <cstdlib>
#include <tuple>
#include "metrics.hpp"
#include "database.hpp"
#include "../ini_reader.hpp"
#include "../functions.hpp"
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

    static unsigned max_populations;
    static unsigned max_individuals;
    
    static bool logger_debug;
    static bool data_debug;
    static bool fitness_per_iter;
    static std::string besttrip_filename;

    static bool database_active;
    static std::string database_name;
    static std::string database_dir;
    static bool database_removeprevious;

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

        settings::max_populations = std::stoi(reader.Get("simulation.population","N","100"));
        settings::max_individuals = std::stoi(reader.Get("simulation.individuals","N","200"));

        settings::logger_debug = general::conversion::to_bool(reader.Get("settings","logger_debug","true"));
        settings::data_debug = general::conversion::to_bool(reader.Get("settings","data_debug","false"));
        settings::fitness_per_iter = general::conversion::to_bool(reader.Get("settings","fitness_per_iteration","true"));
        settings::besttrip_filename = reader.Get("outputs","besttrip_filename","");

        settings::database_active = general::conversion::to_bool(reader.Get("settings.database","active","true"));
        settings::database_dir = reader.Get("settings.database","base_dir","./outputs/"+settings::layout+"/");
        settings::database_name = reader.Get("settings.database","name",settings::database_dir+"results");
        settings::database_removeprevious = general::conversion::to_bool(reader.Get("settings.database","remove_previous","true"));
        settings::cities_generated = false;

        #define SETTINGS_LOADED true
    #endif
}


void LoadDatabaseSettings(Database &db){
    if (settings::database_active){
        if (db.IsConnected()){
            char *zErrMsg;
            int rc,count;
            rc = sqlite3_exec(db.GetDatabase(), "SELECT COUNT(*) FROM SETTINGS", countcallback, &count, &zErrMsg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            tuple<string,string,string> key = make_tuple("ID","INT PRIMARY KEY","NOT NULL");
            tuple<string,string,string> _ncities = make_tuple("NCITIES","INTEGER","NOT NULL");
            tuple<string,string,string> _layout = make_tuple("LAYOUT","TEXT","NOT NULL");
            tuple<string,string,string> _box = make_tuple("BOX","REAL","NOT NULL");
            tuple<string,string,string> _metric_type = make_tuple("METRIC","TEXT","NOT NULL");
            tuple<string,string,string> _max_ind = make_tuple("MAX_IND","INTEGER","NOT NULL");
            tuple<string,string,string> _max_pop = make_tuple("MAX_POP","INTEGER","NOT NULL");
            vector<tuple<string,string,string>> myvec = {key,_ncities,_layout,_box,_metric_type,_max_ind,_max_pop};
            db.create_table("SETTINGS",myvec,true);
            string sql = "INSERT INTO SETTINGS (ID, NCITIES,LAYOUT,BOX,METRIC,MAX_IND,MAX_POP) VALUES ("+to_string(count)+","+to_string(settings::ncities)+",'"+settings::layout+"',"+to_string(settings::box)+",'"+settings::metric_type+"',"+to_string(settings::max_individuals)+","+to_string(settings::max_populations)+");";
            cout << "Inserting settings:\n";
            db.insert(sql);
            if (settings::logger_debug) cout << "Settings loaded to database"<<endl;
        }
    }
}

#endif