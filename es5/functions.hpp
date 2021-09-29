#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__
#define __STDCPP_MATH_SPEC_FUNCS__
#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <cmath>
#include <iostream>
#include <assert.h>
using namespace std;

class Function
{
private:

public:
    Function(){

    };
    ~Function(){

    };
    virtual void print_settings() = 0;

    virtual double eval(double x, double y, double z) = 0;
    virtual double eval(vector<double>) = 0;
};

class Exponential : public Function{
    protected:
        double a,b,c;
    public:
        Exponential(){
            a = 1;
            b = 1;
            c = 0;
        };

        Exponential(double _a, double _b, double _c){
            a = _a;
            b = _b;
            c = _c;
        }

        double eval(double r, double theta, double phi){
            return 0;
        }
};

class TestWaveFunction : public Function{
    private:
        unsigned n,l,m;
        const double a0 = double(0.0529e-09);


    public:
        TestWaveFunction(unsigned _n,unsigned _l,unsigned _m){
            n = _n;
            l = _l;
            m = _m;
        }
        ~TestWaveFunction();

        void print_settings(){
            cout << "TestWavefunction"<<endl;
        }

        double GetBohrRadius(){
            return a0;
        }

        double to_bohr_units(double r){
            double y = double(r)*GetBohrRadius();
            //cout << "ToBohrUnits of "<<r<<"=\t"<<y<<endl;
            return y;
        }

        double eval(double x, double y, double z){
            double r = sqrt(x*x+y*y+z*z);
            if (n==1 && l==0 && m==0){
                return M_PI*exp(-2*r);
            }else if(n==2 && l == 1 && m==0){
                double CosTheta=z/r;
                return 1./(32.*M_PI)*exp(-r)*pow(r*CosTheta,2);
            }else{
                throw "Error :(";
            }
        }

        double eval(vector<double> vec){
            double x = vec[0];
            double y = vec[1];
            double z = vec[2];

            double r = sqrt(x*x+y*y+z*z);
            double theta;
            if (z!=0){
                theta = atan(sqrt(x*x+y*y)/z);
            }else{
                theta = M_PI_2;
            }
            if (n==1 && l==0 && m==0){
                return M_PI*exp(-2*r);
            }else if(n==2 && l == 1 && m==0){
                double CosTheta=z/r;
                return 1./(32.*M_PI)*exp(-r)*pow(r*CosTheta,2);
            }else{
                throw "Error :(";
            }
        }
};

class WaveFunction : public Function{
    protected:
        unsigned n,l,m;
        const double a0 = double(0.0529e-09);

        bool debug = false;
    
    public:
        WaveFunction(){
            n = 1;
            l = 0;
            m = 0;
        };

        WaveFunction(unsigned _n, unsigned _l, unsigned _m){
            assert (_n>=1);
            n = _n;
            l = _l;
            m = _m;
        }

        ~WaveFunction(){};

        void print_settings(){
            cout << "***************  Hydrogren Wavefunction  ***************"<<endl;
            cout << "## Quantum numbers: ("<<n<<","<<l<<","<<m<<")"<<endl;
            cout << "## Debug mode: "<<boolalpha<<debug<<endl;
            cout << "********************************************************"<<endl;
            cout << " "<<endl;
        }

        double __rad_to_deg(double rad){
            return rad*180.0/M_PI;
        }

        double __deg_to_rad(double deg){
            return deg*M_PI/180;
        }

        double GetBohrRadius(){
            return a0;
        }

        double to_bohr_units(double r){
            double y = double(r)*GetBohrRadius();
            //cout << "ToBohrUnits of "<<r<<"=\t"<<y<<endl;
            return y;
        }

        double exp_term(double r){
            double y = exp(-to_bohr_units(r)/(n*GetBohrRadius()));
            if (debug){cout << "ExpTerm of "<<r<<"= "<<y<<"\tn*a0= "<<n*GetBohrRadius()<<endl;}
            return y;
        }

        double r_term(double r){
            double x = (2*to_bohr_units(r))/(n*GetBohrRadius());
            double y = pow(x,l);
            if (debug){cout << "R-term of for r="<<r<<"=\t"<<y<<endl;}
            return y;
        }

        double laguerre_term(double r){
            double y;
            double degree = n-l-1;
            if (degree==0){
                y = 1.;
            }else if(degree==1){
                y = -r+1;
            }else if(degree==2){
                y = 0.5*(r*r-4*r+2);
            }else if(degree==3){
                y = (1/6)*(-pow(r,3)-9*r*r-18*r+6);
            }else{
                throw "laguerre term only takes n lower than 4.";
            }
            if (debug) {cout << "Laguerre term with n="<<n<<" and l="<<l<<":\t"<<y<<endl;}
            return y;
            //return laguerre(n-l-1,(2*to_bohr_units(r))/(n*GetBohrRadius()));
        }

        double spherical_harmonics(double theta, double phi){
            double y;
            // Only 0,0 and 1,0 cases for this exercise
            if (l==0 && m==0){
                y = 0.5*sqrt(1/M_PI);
            }else if(l==1 && m==0){
                y = 0.5*sqrt(3/M_PI)*cos(theta);
            }else{
                throw "spherical_harmonics: only 0,0 or 1,0 valid";
            }
            if (debug) {cout<<"Spherical harmonics with l= "<<l<<" & m="<< m <<":\t"<<y<<endl;}
            return y;
        }
        
        double norm(){
            double term1 = sqrt(  pow((2/(n*GetBohrRadius())),3)  );
            double term2 = sqrt(  (tgammaf(n-l))/(2*n*tgammaf(n+l+1))  );
            double y = term1*term2;
            if (debug){ cout << "Norm=\t"<<y<<"\t\t term1: " <<term1<<" , term2: "<<term2<<endl;}
            return y;
        }

        double eval(double x, double y, double z){
            double r =  sqrt(x*x+y*y+z*z);
            double theta,phi;
            if (z!=0){
                theta = atan(sqrt(x*x+y*y)/z);
            }else{
                theta = M_PI_2;
            }
            if (x!=0){
                phi = atan(y/x);
            }else{
                if (y>0){
                    phi = M_PI_2;
                }else{
                    phi = -M_PI_2;
                }
            }

            return norm()*exp_term(r)*r_term(r)*laguerre_term(r)*spherical_harmonics(theta,phi);
        }


        double eval(vector<double> coordinates) {
            double x = coordinates[0];
            double y = coordinates[1];
            double z = coordinates[2];

            double r =  sqrt(x*x+y*y+z*z);
            double theta,phi;
            if (z!=0){
                theta = atan(sqrt(x*x+y*y)/z);
            }else{
                theta = M_PI_2;
            }
            if (x!=0){
                phi = atan(y/x);
            }else{
                if (y>0){
                    phi = M_PI_2;
                }else{
                    phi = -M_PI_2;
                }
            }

            return norm()*exp_term(r)*r_term(r)*laguerre_term(r)*spherical_harmonics(theta,phi);
        }
};

#endif