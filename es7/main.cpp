#include <iostream>
#include "NVT.hpp"
using namespace std;

int main(int argc, char** argv){
    if (argc!=2){
        cerr << "[MAIN] Program runs with parameter <config_file>"<<endl;
        exit(EXIT_FAILURE);
    }
    string configfile = argv[1];
    NVT *model = new NVT();
    model->Input(configfile); //Inizialization
    int nconf = 1;
    for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
    {
        model->Reset(iblk);   //Reset block averages
        for(int istep=1; istep <= nstep; ++istep)
        {
        model->Move();
        model->Measure();
        model->Accumulate(); //Update block averages
        if(istep%10 == 0){
            model->ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
            nconf += 1;
        }
        }
        model->Averages(iblk);   //Print results for current block
    }
    model->ConfFinal(); //Write final configuration
    return 0;
}
