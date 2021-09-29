#ifndef __DISTRIBUTIONS__H__
#define __DISTRIBUTIONS__H__

#include <vector>
#include <random>
#include <assert.h>
using namespace std;

class Distribution
{
private:

public:
    Distribution(){};
    ~Distribution(){};
    virtual vector<double> sample() = 0;
};


class Uniform : public Distribution {
    private:
        double x0,y0,z0;
        double delta;
        unsigned dims;
    public:
        Uniform(){x0 = 0; delta=1;dims=1;srand (time(NULL));};
        Uniform(double _x0,double _delta){x0 = _x0; delta = _delta; dims = 1; srand (time(NULL));}
        Uniform(double _x0, double _delta,unsigned d){x0 = _x0; delta = _delta; dims = d; srand (time(NULL));assert (0<dims<4);};
        ~Uniform(){};

        double GetX0(){
            return x0;
        }
        void SetX0(double x){
            x0 = x;
        }
        double GetY0(){
            return y0;
        }
        void SetY0(double y){
            y0 = y;
        }
        double GetZ0(){
            return z0;
        }
        void SetZ0(double z){
            z0 = z;
        }

        double GetDelta(){
            return delta;
        }
        void SetDelta(double d){
            delta = d;
        }

        unsigned GetDimentions(){
            return dims;
        }
        void SetDimentions(unsigned _dims){
            dims = _dims;
        }

        vector<double> sample(){
            
            vector <double> coordinates;
            for (int i = 0;i<dims;i++){
                float temp = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
                coordinates.push_back(temp);
            }
            return coordinates;
        };
};


#endif