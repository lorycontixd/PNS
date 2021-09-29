#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <ctime>   
#include <exception>
#include <sstream>
#include "../functions.hpp"

using namespace std;
#define quote(x) #x

#define Stringize( L )     #L 
#define MakeString( M, L ) M(L)
#define $Line MakeString( Stringize, __LINE__ )
#define Warning __FILE__ "(" $Line ") : Reminder: "
// Call with: #pragma message(Reminder "message as string") 

template<size_t N>string convert(char const(&data)[N])
{
   return std::string(data, std::find(data, data + N, '\0'));
}

class BaseError : public std::exception {
    private:
    protected:
        string name;
        string msg;
        string location;
        string error;
        string now;
	public:
        BaseError(){
            
            name = typeid(*this).name();
           
            msg = "["+location+"] "+name+": "+error;
        };
        BaseError(string _location, string _error){
            
            location = _location;
            error = _error;
            parse_name();
            msg = "["+now+"] ["+location+"] "+name+": "+error;
        }
        virtual string get_name(){ return name;}
        virtual const string get_location(){ return location;}
        virtual const char * what() const throw() = 0;

        void update(){
            location = general::strings::upper(location);
            auto start = std::chrono::system_clock::now();
            parse_name();
            auto current = std::chrono::system_clock::now();
            std::time_t current_time = std::chrono::system_clock::to_time_t(current);
            now = std::ctime(&current_time);
            now = now.substr(0,now.length()-1);
            msg = "["+now+"] ["+location+"] "+name+": "+error;
        }

        void parse_name(){
            name = typeid(*this).name();
            string newname = "";
            for (char i : name){
                if (!isdigit(i)){
                    newname +=i;
                }
            }
            name=newname;
        }
};

//*****************  INPUT ERROR  ************************

class InputError : public BaseError{
    private:
    protected:
        string variable;
    public:
        InputError(string _location, string _error, string _variable): BaseError(_location,_error){
            variable = _variable;
            update();
            msg += " <"+variable+">";

        };
    
    const char * what() const throw(){
        return msg.c_str();
    };
};

class CommandlineArgumentError : public InputError{
    private:
    protected:
    public:
        CommandlineArgumentError(string _location, string _error, string _variable) : InputError(_location, _error, _variable){
            update();
            msg += " <"+variable+">";
        };
        
        const char * what() const throw(){
            return msg.c_str();
        };
};

class ConfigFileError : public InputError {
    private:
    protected:
    public:
        ConfigFileError(string _location, string _error, string _variable) : InputError(_location, _error, _variable){
            update();
            msg += " <"+variable+">";
        };
        
        const char * what() const throw(){
            return msg.c_str();
        };
};

//*****************  RUNTIME ERROR  ************************

class RuntimeError : public BaseError{
    private:
    protected:
    public:
        RuntimeError (string _location, string _error) : BaseError(_location,_error){
            update();
        };

        const char * what() const throw(){
            return msg.c_str();
        };
};

class FitnessError : public RuntimeError {
    private:
    protected:
    public:
        FitnessError (string _location) : RuntimeError(_location,"Unable to calculate fitness"){
            update();
        };

        const char * what() const throw(){
            return msg.c_str();
        };

};

class OperationError : public RuntimeError {
    private:
    protected:
        string operation;
    public:
        OperationError(string _location, string _operation) : RuntimeError(_location,"Error while performing") {
            operation = _operation;
            update();
            msg += " "+operation;
        }

        const char * what() const throw(){
            return msg.c_str();
        };
};

class IndividualCheckFailure : public RuntimeError {
    private:
    protected:
        string requirement;
    public:
        IndividualCheckFailure(string _location, string _requirement) : RuntimeError(_location,"Requirement not met -> ") {
            requirement = _requirement;
            update();
            msg += requirement;
        }

        const char * what() const throw(){
            return msg.c_str();
        };
};

class GetEmptyError : public RuntimeError {
    private:
    protected:
        string variable;
    public:
        GetEmptyError(string _location, string _variable) : RuntimeError(_location,"Cannot get empty variable ") {
            variable = _variable;
            update();
            msg += variable;
        }

        const char * what() const throw(){
            return msg.c_str();
        };
};



/**********************************************************************
************************  WARNINGS  ***********************************
**********************************************************************/

/*
class BaseWarning {
    private:
    protected:
        string location, error;
        string msg;
        string name;
    public:
        BaseWarning(string _location, string _error){
            location = _location;
            error = _error;
        };

        void update(){
            parse_name();
            msg = name+": "+error;
        };

        void parse_name(){
            name = typeid(*this).name();
            string newname = "";
            for (char i : name){
                if (!isdigit(i)){
                    newname +=i;
                }
            }
            name=newname;
        };

        static string what()  {
            cerr << msg << endl;
        };
};
*/

#endif