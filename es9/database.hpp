#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__
#include <iomanip>
#include <iostream>
#include <variant>
#include <tuple>
#include <sqlite3.h>
#include "../functions.hpp"
using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int countcallback(void* data, int count, char** rows,char **azColName)
{
    if (count == 1 && rows) {
        *static_cast<int*>(data) = atoi(rows[0]);
        return 0;
    }
    return 1;
}


class Database {
    /* Database class (using C++17 sqlite3 -> https://www.sqlite.org/index.html)

    */
    private:
        // Variables
        string name;
        sqlite3* db; 
        char *zErrMsg = 0;

        bool connected;
        bool debug = false;

        // Hidden functions
        void __parse_name(string name){
            if (general::strings::endsWith(name,".db")){
                const std::string ext(".db");
                if ( name != ext &&
                    name.size() > ext.size() &&
                    name.substr(name.size() - ext.size()) == ".db" )
                {
                // if so then strip them off
                name = name.substr(0, name.size() - ext.size());
                }
            }
        };

        template<size_t I = 0, typename... Tp> void parse_keys(std::tuple<Tp...>& t) {
            //std::cout << std::get<I>(t) << " ";
            std::get<0>(t) = general::strings::upper(std::get<0>(t));
            if constexpr(I+1 != sizeof...(Tp))
                parse_keys<I+1>(t);
        }

    protected:
    public:
        // Constructors
        Database(){
            name = "mydatabase";
            connected = false;
        };
        Database(string _name){
            name = _name;
            connected = false;
        };
        Database(string _name, bool conn){
            name = _name;
            if (conn){
                connect();
                connected = true;
            }
        };
        Database(string _name, bool conn, bool _debug){
            name = _name;
            debug = _debug;
            if (conn){
                connect();
                connected = true;
            }
        };
        ~Database(){};


        // Methods
        int connect(){
            if (!connected){
                int rc;
                string tmp_name = name +".db";
                rc = sqlite3_open(tmp_name.c_str(), &db);
                if( rc ) {
                    fprintf(stderr, "[DB] Can't open database: %s\n", sqlite3_errmsg(db));
                    return -1;
                } else {
                    if (debug){
                        fprintf(stdout, "[DB] Opened database successfully\n");
                    }
                    connected = true;
                    return rc;
                }
            }else{
                return -1;
            }
            
        };

        int create_table(string table_name, vector<std::tuple<string,string,string>>& keys, bool ifnotexists = true){
            if (connected){
                int rc;
                string sql;
                if (ifnotexists){
                    sql = "CREATE TABLE IF NOT EXISTS "+table_name+"(";
                }else{
                    sql = "CREATE TABLE "+table_name+"(";
                }
                
                for (auto key : keys){
                    parse_keys(key);
                    sql += get<0>(key)+"  "+get<1>(key)+"  "+get<2>(key)+",";
                }
                sql = sql.substr(0, sql.size()-1);
                sql += ");";
                if (debug) cout << sql << endl;
                rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
                if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                } else {
                    //cout << "[DB] Table "<<table_name<<" created successfully"<<endl;
                    if (debug) fprintf(stdout,"Table %s created successfully\n",table_name.c_str());
                }
                return rc;
            }else{
                // throw
                return -1;
            }
        };

        int insert(string sql){
            if (connected){
                int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
                if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                    return -1;
                } else {
                    //cout << "[DB] Table "<<table_name<<" created successfully"<<endl;
                    //fprintf(stdout,"[DB] Data inserted correctly");
                    return rc;
                }
            }else{
                // throw
                return -1;
            }
        };
    

        int close(){
            if (connected){
                sqlite3_close(db);
                return 0;
            }else{
                cerr << "[DB] Database not connected. Cannot terminate."<<endl;
                return -1;
            }
        };


        // *********** GETS **************
        string GetName() const {
            return name;
        };

        bool IsConnected() const {
            return connected;
        };

        sqlite3* GetDatabase() const {
            return db;
        }



        // *********** SETS **************
        void SetName(string _name, bool force = false){
            if (name == "mydatabase"){
                name = _name;
            }else{
                if (!force){
                    cerr << "[DB] Cannot rename the database instance. Please set force to true."<<endl;
                    return;
                }else{
                    name = _name;
                }
            }
        };
}; 
#endif