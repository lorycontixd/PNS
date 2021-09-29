#ifndef __DATABLOCKING_HPP__
#define __DATABLOCKING_HPP__

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;


double error(double SumAve, double SumAve2, int n){
	if(n==0) return 0;
	double diff = SumAve2 - pow(SumAve,2);
	double sqrtval = sqrt(abs(diff)/double(n));
	return sqrtval;
}

double DataBlocking ( string inputfile, unsigned nblocks, string outputfile){
	vector<double> dati;
	ifstream in(inputfile);
	double temp;
	while (!in.eof()){
		in>>temp;
		dati.push_back(temp);
	}
	unsigned totalsize = dati.size();
	unsigned blocklength = totalsize/nblocks;
	vector<double> blocks(nblocks);
	vector<double> AV(nblocks);
	vector<double> AV2(nblocks);
	vector<double> Err(nblocks);
	double ave2,sum, blocksum;

	unsigned index;
	for (unsigned i=0; i<nblocks; i++){
		blocksum = 0;
		for (unsigned j=0; j<blocklength; j++){
			index = (i+1)*j;
			blocksum += dati[index];
		}
		blocks[i] = blocksum/blocklength;
	}

	ofstream risul(outputfile);
	for (unsigned i=0; i<nblocks; i++){
		sum = ave2 = 0;
		for (unsigned j=0; j<i+1; j++){
			sum += blocks[i];
			ave2 += pow(blocks[i],2);
		}
		AV[i] = sum/double(i+1);
		AV2[i] = ave2/double(i+1);
		Err[i] = error(AV[i], AV2[i], i);

		risul << double(i+1) << "\t" << AV[i] << "\t" << Err[i]<<endl;
	}
	risul.close();

	return 0.;
}

#endif