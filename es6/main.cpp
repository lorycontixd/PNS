#include <iostream>
#include <cstdlib>
#include <vector>
#include "../functions.hpp"
#include "Ising.hpp"
using namespace std;

int main(int argc, char** argv) {
	if(argc!=3 && argc!=4){
        cerr << "[MAIN] " << argv[0] << " requires minimal parameters <config_file> <restart> <dbname (optional)>." << endl;
        exit(EXIT_FAILURE);
    }

    string configfile = argv[1];
    unsigned nrestart = stoi(argv[2]);
    cout << "[MAIN] nrestart= "<<nrestart<<endl;
    string dbname = argv[3];

    Ising *model = new Ising(configfile, nrestart, dbname);

	model->Input(); //Inizialization

	for(int iblk=1; iblk <= model->GetBlocks(); ++iblk) { //Simulation
		model->Reset(iblk);   //Reset block averages
		for(int istep=1; istep <= model->GetSteps(); ++istep) {
			model->Move();
			model->Measure();
			model->Accumulate(); //Update block averages
		}
		model->Averages(iblk);   //Print results for current block
	}
	model->ConfFinal(); //Write final configuration

return 0;
}