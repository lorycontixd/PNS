#ifndef __WAVEFUNCTIONS_HPP__
#define __WAVEFUNCTIONS_HPP__

#include <cmath>
using namespace std;

class WaveFunction{
    private:
    protected:
        double mu, sigma;

    public:
        WaveFunction(){
            mu = 1;
            sigma = 1;
        };
        WaveFunction(double m, double s){
            mu = m;
            sigma = s;
        };
        ~WaveFunction(){};

        virtual double eval(double x) = 0;
        virtual double squared(double x)=0;
        virtual double second_derivative(double x)=0;

        void SetMu(double m){
            mu = m;
        };

        double GetMu(){
            return mu;
        };

        void SetSigma(double s){
            sigma = s;
        }

        double GetSigma(){
            return sigma;
        }
};


class MyWaveFunction : public WaveFunction{
    private:
    protected:
    public:
        MyWaveFunction(double m, double s) : WaveFunction(m,s){};

    virtual double eval(double x){
        return (exp( -(x-mu)*(x-mu)/(2.*sigma*sigma) ) + exp( -(x+mu)*(x+mu)/(2.*sigma*sigma) ) );
    };

    virtual double squared(double x){
        double a=exp(-pow((x-mu)/sigma,2.)*0.5);
        double b=exp(-pow((x+mu)/sigma,2.)*0.5);
        return (a*a+b*b+2.*a*b);
    };

    virtual double second_derivative(double x){
        return (exp( -(x-mu)*(x-mu)/(2.*sigma*sigma) )*( pow((x-mu)/(sigma*sigma),2.) - 1./pow(sigma,2.) ) + exp( -(x+mu)*(x+mu)/(2.*sigma*sigma) ) * ( pow((x+mu)/(sigma*sigma),2.) - 1./pow(sigma,2.) ) );
    }
};




#endif