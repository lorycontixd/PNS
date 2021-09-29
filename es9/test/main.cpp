#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
#include <stdio.h>  // for printf
#include <vector>
#include <tuple>
#include "../mutations.hpp"
#include "../metrics.hpp"
#include "../database.hpp"
#include "../random.hpp"
#include "../settings.hpp"
#include "../exceptions.hpp"
#include <armadillo>
//#include <mongocxx/client.hpp>
//#include <mongocxx/instance.hpp>
#include <sqlite3.h>
using namespace std; 


template <typename T> void show(vector<T>& v){
    for (auto i : v){
        cout << i << ", ";
    }
    cout << endl;
}

double random_float(double LO, double HI){
	double r = LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI-LO)));
	return r;
}

template <typename T> void Shuffle(vector<T>& v){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle( v.begin(),v.end(),default_random_engine(seed));
}

int main(int argc, char const *argv[])
{
	template<typename T> T Fixture::Unpack<T>::value{};
	return 0;
}


/*
int main(int argc, char* argv[]) {
	unsigned size = 10;
	Random *rnd = new Random();
	vector<unsigned> ints;
	for (unsigned i = 0; i<size; i++){
		ints.push_back(i);
	}
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//shuffle( ints.begin(),ints.end(),default_random_engine(seed));
	show(ints);
	Individual i;
	i.SetGenes(ints);
	Swap(i,rnd);
	Reverse(i,rnd);
	i.ShowGenes();
	return 0;
}*/

/*
int main(int argc, char const *argv[])
{
	double r0 = random_float(0,2*M_PI);
	double x0 = sin(r0);
	double y0 = cos(r0);

	double r1 = random_float(0,2*M_PI);
	double x1 = sin(r1);
	double y1 = cos(r1);

	double r2 = random_float(0,2*M_PI);
	double x2 = sin(r2);
	double y2 = cos(r2);

	LoadSettings(argv[1]);
	cout << settings::metric->norm(x0,x1,y0,y1);
	return 0;
}
*/


