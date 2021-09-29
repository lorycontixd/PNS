#ifndef __DATABLOCKING_HPP__
#define __DATABLOCKING_HPP__
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

double error(double SumAve, double SumAve2, int n){
	return sqrt( ( SumAve2-(SumAve*SumAve) )/double(n) );
}

double Data_Blocking ( vector<double>& Average, int Block_Number, string output_file){
	ofstream risul(output_file);
	double finalAV[Block_Number];
	double finalAV2[Block_Number];
	double err[Block_Number];
	double ave2,sum;

	for (int j=0; j<Block_Number; j++){
		sum=ave2=0;
		for (int i=0; i<j+1; i++){
			sum+=Average[i];
			ave2+=Average[i]*Average[i];
		}
		finalAV[j]=sum/double(j+1);
		finalAV2[j]=ave2/double(j+1);
		if(j!=0){err[j]=error(finalAV[j],finalAV2[j],j);}
		else{err[j]=0;}
		risul<<double(j+1)<<"\t"<<finalAV[j]<<"\t"<<err[j]<<endl;
	}
	risul.close();
	return 0.;
}

#endif