#ifndef __METRICS_HPP__
#define __METRICS_HPP__
#include <iostream>
#include <cmath>
using namespace std;

class Metric{
    private:
    protected:
        string name;
    public:
        Metric(){};
        ~Metric(){}

        virtual double norm(double x1, double x2, double y1, double y2) = 0;
};

class L1 : public Metric{
    private:
    protected:
    public:
        L1(){
            name = "L1";
        };

        double norm(double x1, double x2, double y1, double y2){
            return abs(x2 - x1) + abs(y2 - y1);
        };
};

class L2 : public Metric{
    private:
    protected:
    public:
        L2(){
            name = "L2";
        };

        double norm(double x1, double x2, double y1, double y2){
            return pow(x2 - x1,2) + pow(abs(y2 - y1),2);
        };
};

#endif