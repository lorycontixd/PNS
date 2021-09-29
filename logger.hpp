#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <map>
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace Log{
    unsigned LEVEL_DEBUG = 0;
    unsigned LEVEL_INFO = 1;
    unsigned LEVEL_WARNING = 2;
    unsigned LEVEL_ERROR = 3;
    unsigned LEVEL_FATAL = 4;

    class Logger {
        private:
            string name;
            unsigned level;
            bool include_date;
            bool include_level;
            map<unsigned,string> keys = { {0,"DEBUG"} , {1,"INFO"} , {2,"WARNING"}, {3,"ERROR"} , {4,"FATAL"}};
        protected:
        public:
            Logger (){
                name = "MyLogger";
                level = LEVEL_INFO;
                include_date = true;
                include_level = true;
            }
            Logger(unsigned _level){
                name = "MyLogger";
                level = _level;
                include_date = true;
                include_level = true;
            };
            Logger(string _name, unsigned _level){
                name = _name;
                level = _level;
                include_date = true;
                include_level = true;
            };
            Logger(string _name, unsigned _level, bool idate, bool ilevel){
                name = _name;
                level = _level;
                include_date = idate;
                include_level = ilevel;
            };
            ~Logger(){};


            auto get_date(){
                auto current = std::chrono::system_clock::now();
                std::time_t current_time = std::chrono::system_clock::to_time_t(current);
                string now = std::ctime(&current_time);
                now = now.substr(0,now.length()-1);
                return now;
            };

            auto get_msg(string message, unsigned currentlevel, string color){
                string date = get_date();
                string msg = "";
                if (include_date){
                    msg += "["+date+"] ";
                }
                if (include_level){
                    msg += "["+keys[currentlevel]+"] ";
                }
                msg += color + message + RESET;
                return msg;
            };

            auto get_level(){
                return keys[level];
            };

            void set_level(unsigned index){
                if (index < 0 || index > 4){
                    cerr << "Logger level not accepted"<<endl;
                    exit(EXIT_FAILURE);
                }
                level = index;
            };

            void set_name(string _name){
                name = _name;
            };

            auto debug(string message, bool _return = false){
                if (level<=LEVEL_DEBUG){
                    string msg = get_msg(message,LEVEL_DEBUG,WHITE);
                    cout << msg << endl;
                }
            };

            auto info(string message, bool _return = false){
                if (level<=LEVEL_INFO){
                    string msg = get_msg(message,LEVEL_INFO,BOLDMAGENTA);
                    cout << msg << endl;
                }
            };

            auto warning(string message, bool _return = false){
                if (level<=LEVEL_WARNING){
                    string msg = get_msg(message,LEVEL_WARNING,BOLDYELLOW);
                    cout << msg << endl;
                }
            };

            auto error(string message, bool _return = false){
                if (level<=LEVEL_ERROR){
                    string msg = get_msg(message,LEVEL_ERROR,BOLDRED);
                    cout << msg << endl;
                }
            };

            auto fatal(string message){
                if (level<=LEVEL_FATAL){
                    string msg = get_msg(message,LEVEL_FATAL,BOLDRED);
                    cout << msg << endl;
                    cout << "Fatal error detected. Exiting.."<<endl;
                    exit(EXIT_FAILURE);
                }
            };
    };
};

#endif