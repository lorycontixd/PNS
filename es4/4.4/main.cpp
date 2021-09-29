#include <iostream>
#include <cstdlib>
#include "NVE.hpp"
#include "datablocking.hpp"
#include "../../functions.hpp"

int main(int argc, char* argv[]){
	
	if(argc !=4){
		cerr << argv[0] << " requires parameters <configfile> <nrestart> <equilibrationrun>."<<endl;
        exit(EXIT_FAILURE);
	}

    string configfile = argv[1];
    unsigned nrestart = stoi(argv[2]);
    bool equilibrationrun = general::conversion::to_bool(argv[3]);
    NVE *model = new NVE(configfile, nrestart, equilibrationrun);

	model->Input(); //Inizialization
	int nconf = 1;

    unsigned nstep = model->GetSteps();
    unsigned nblocks = model->GetBlocks();
    unsigned blocklength = int(nstep/nblocks);
    bool xyz = model->GetXYZ();

	for(int istep=1; istep <= nstep; ++istep){
		model->Move(); //Move particles with Verlet algorithm
		model->Measure(); //Properties measurement
		if(istep%blocklength == 0){
			cout << "Number of time-steps: " << istep << endl;
			cout << "Number of block: " << istep/blocklength << endl << endl;
		}
        if (xyz){
            if(istep%100 == 0){
                model->ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
                nconf += 1;
            }
        }
	}
	model->ConfFinal();         //Write final configuration to restart
    string state = model->GetState();
    if (!equilibrationrun){
        vector<string> vars = {"epot","etot","ekin","temp","pres"};
        for (size_t t=0; t<vars.size(); t++){
            string inputfile = "./outputs/"+state+"/measurements/instant_"+vars[t]+".dat";
            string outputfile = "./outputs/"+state+"/measurements/ave_"+vars[t]+".dat";
            DataBlocking(inputfile, nblocks, outputfile);
        }
    }
	return 0;
}