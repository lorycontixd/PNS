#ifndef __MUTATIONS_HPP__
#define __MUTATIONS_HPP__
#include <algorithm>
#include "individual.hpp"
#include "random.hpp"
#include "settings.hpp"
using namespace std;


int Swap (Individual &i, Random *rnd){
	int a = int(rnd->Rannyu(0,i.GetGenesSize()));
	int b = int(rnd->Rannyu(0,i.GetGenesSize()));
	swap(i.GetGenes()[a],i.GetGenes()[b]);
	return 0;
}

int NeighbourSwap(Individual &i, Random *rnd){
	int index = int(rnd->Rannyu(0,i.GetGenesSize()-1));
	swap(i.GetGenes()[index],i.GetGenes()[index+1]);
	return 0;
}

int Shift (Individual &i, Random *rnd){
	int shift = int(rnd->Rannyu(1,i.GetGenesSize()));
	rotate(i.GetGenes().begin(),i.GetGenes().begin()+shift,i.GetGenes().end());
	return 0;
}

int MultipleSwap (Individual &i, Random *rnd){
	int inizio = int ( rnd->Rannyu(0,i.GetGenesSize()/2) );
	int length = int( rnd->Rannyu(1,i.GetGenesSize()/2-inizio) );
	int shift = int ( rnd->Rannyu(length,i.GetGenesSize()/2-1) );
	vector<unsigned> y(length);
	vector<unsigned> z(length);
    vector<unsigned> x = i.GetGenes();
	for(unsigned i=0;i<length;i++) z[i]=x[inizio+shift+i];
	for(unsigned i=0;i<length;i++) y[i]=x[inizio+i];
	for(unsigned i=0;i<length;i++) x[inizio+i]=z[i]; 
	for(unsigned i=0;i<length;i++) x[inizio+shift+i]=y[i]; 
	return 0;
}

int Reverse (Individual &i, Random *rnd){
	int inizio = int(rnd->Rannyu(0,i.GetGenesSize()));
	reverse(i.GetGenes().begin()+inizio,i.GetGenes().end());
	return 0;
}

#endif