#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "random.hpp"
#include "metropolis.hpp"
#include "datablocking.hpp"
#include "../functions.hpp"

using namespace std;

double Psi(double, double, double);
double Psi_Second(double, double, double);
double Potential(double);

int main (int argc, char *argv[]){
	if(argc != 4){
		cerr << " Error: Program needs parameters -> ./main <mu> <sigma> <automation>";
		exit(EXIT_FAILURE);
	}

	double ene,sum, mu, sigma;
	mu = atof(argv[1]);
	sigma = atof(argv[2]);
	bool automation = general::conversion::to_bool(argv[3]);

	Metropolis Met(mu,sigma, automation);
	Met.Input("config.ini");
	Met.Equilibration(0.50);
	Met.Run();
	Met.Save();
	
	
	return 0;
}
