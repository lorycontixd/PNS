#ifndef __DATABLOCKING_HPP__
#define __DATABLOCKING_HPP__

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;


/*
Datablocking:
The datablocking method is used to calculate the statistical uncertainty of a MonteCarlo simulation
The uncertainty can be calculated using:  𝜎2𝐴:=⟨(𝐴−⟨𝐴⟩)2⟩=⟨𝐴2⟩−⟨𝐴⟩2

The datablocking method divides M MonteCarlo steps in N blocks (M>N), and used the M/N steps inside a block to calculate A_i
Then: <A^2> is the average of squared values (A_i)^2, while <A>^2 is the squared of the average of averaged values A_i
*/



double error(double SumAve, double SumAve2, int n){
    if (n==0){return 0.;}else{
        return sqrt( ( SumAve2-(SumAve*SumAve) )/double(n) );
    }
}


namespace Ex1{
    double DataBlocking ( double * Dati, int Dati_Number, string outputfile){
        double AV[Dati_Number];
        double AV2[Dati_Number];
        double Err[Dati_Number];
        double ave2,sum;

        ofstream risul(outputfile);
        for (int j=0; j<Dati_Number; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=Dati[i];
                ave2+=Dati[i]*Dati[i];
            }
            AV[j]=sum/double(j+1);
            AV2[j]=ave2/double(j+1);
            Err[j]=error(AV[j],AV2[j],j);

            if(j==0) { Err[j]=0; }

            risul<<double(j)<<"	"<<AV[j]<<"	"<<Err[j]<<endl;
        }
        risul.close();
        return 0.;
    }
}

namespace Ex2{
    double DataBlocking ( vector<double> dati, string outputfile){
        vector<double> AV,AV2,err;
        double ave2,sum;
        unsigned N = dati.size();

        ofstream risul(outputfile);
        for (int j=0; j<N; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=dati[i];
                ave2+=pow(dati[i],2);
            }
            AV.push_back(sum/double(j+1));
            AV[j]=sum/double(j+1);
            AV2.push_back(ave2/double(j+1));
            if (j!=0){
                err.push_back(error(AV[j],AV2[j],j));
            }else{
                err.push_back(0);
            }

            risul<<double(j)<<"\t"<<AV[j]<<"\t"<<err[j]<<endl;
        }
        risul.close();
        return 0.;
    }
}

namespace Ex3{
    double DataBlocking ( vector<double> &Dati, unsigned size,const string outputfile){
        double ave2,sum;
        vector<double> AV;
        vector<double> AV2;
        vector<double> Err;
        ofstream risul(outputfile);
        for (int j=0; j<size; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=Dati[i];
                ave2+=Dati[i]*Dati[i];
            }
            AV.push_back(sum/double(j+1));
            AV2.push_back(ave2/double(j+1));
            Err.push_back(error(AV[j],AV2[j],j));
            if(j==0) { Err.push_back(0.0);}
            risul<<double(j)<<"\t"<<AV[j]<<"\t"<<Err[j]<<endl;
        }
        risul.close();
        return 0.;
    }
}


namespace Ex4{
    double DataBlocking4_1( string File_Input, int size, unsigned restart, string File_Output){
        cout << "Datablocking ex4 being called"<<endl;
        vector<double> Dati;
        vector<double> AV(size,0.0);
        vector<double> AV2(size,0.0);
        vector<double> Err(size,0.0);
        double ave2,sum;

        int k=0;double x;
        ifstream dati(File_Input);
        while(dati>>x){
            k++;
        }
        dati.close();
        dati.open(File_Input);
        for(int i=0;i<k;i++){
            dati>>x;
            if(i>=k-size){
                Dati.push_back(x);
                //cout << Dati[i-k+size]<<endl;
            }
        }
        dati.close();
        ofstream risul(File_Output);
        for (int j=0; j<size; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=Dati[i];
                ave2+=Dati[i]*Dati[i];
            }
            AV[j]=sum/double(j+1);  
            AV2[j]=ave2/double(j+1);
            Err[j]=error(AV[j],AV2[j],j);
            risul<<(restart+1)*double(j+1)<<"\t"<<AV[j]<<"\t"<<Err[j]<<endl;
            
        }
        risul.close();
        return 0.;
    }

    double DataBlocking4_2 ( string input_file, int size, int block_length, string output_file){
    //essendo i file in append devo caricar e solo i dati dell'ultima simulazione cioè quelli che si trovano nelle ultime Dati_Numeber righe
        vector<double> dati(size,0.0);
        int k=0;
        double x;
        ifstream dati_in(input_file);
        while(dati_in>>x) {
            k++;
        }
        dati_in.close();
        dati_in.open(input_file);
        for(int i=0;i<k;i++){
            dati_in>>x;
            if(i>=k-size){
                dati[i-k+size]=x;
            }
        }
        dati_in.close();

    //raggruppo i dati in blocchi calcolando la media per ciascun blocco
        int block_number = int(size/block_length);
        vector<double> block(block_number,0.0);
        for(int i=0;i<size;i++){
            block[i/block_length] += dati[i]/(double)block_length;
        }

        //faccio il datablocking di block[]
        ofstream risul(output_file);
        double AV[size];
        double AV2[size];
        double Err[size];
        double ave2,sum;

        cout << "--" << block[0] << endl;
        for (int j=0; j<block_number; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=block[i];
                ave2+=block[i]*block[i];
            }
            AV[j]=sum/double(j+1);
            AV2[j]=ave2/double(j+1);
            Err[j]=error(AV[j],AV2[j],j);

            if(j==0) { Err[j]=0; }

            risul << double(j+1) << "\t" << setprecision(8) << AV[j]<< "\t" << Err[j] << endl;
        }
        risul.close();
        return 0.;
    }

    double error(double SumAve, double SumAve2, int n){
        if (n==0){return 0.0;}else{
            return sqrt( ( SumAve2-(SumAve*SumAve) )/double(n) );
        }
    }
}

namespace Ex5{
    double DataBlocking ( vector<double>& Dati, int Dati_Number, const string outputfile){
        double AV[Dati_Number];
        double AV2[Dati_Number];
        double Err[Dati_Number];
        double ave2,sum;

        ofstream risul(outputfile,ios::app);
        for (int j=0; j<Dati_Number; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=Dati[i];
                ave2+=Dati[i]*Dati[i];
            }
            AV[j]=sum/double(j+1);
            AV2[j]=ave2/double(j+1);
            Err[j]=error(AV[j],AV2[j],j);

            if(j==0) { Err[j]=0; }

            risul<<double(j)<<"	"<<AV[j]<<"	"<<Err[j]<<endl;
        }
        risul.close();
        return 0.;
    }
}

//***********************************  EX 7  ***********************************

namespace Ex7{
    void DataBlocking ( vector<double> Dati, int dim,string File_Output){
        vector<double> AV;
        vector<double> AV2;
        vector<double> Err;
        double ave2,sum;

        ofstream risul(File_Output);
        for (int j=0; j<dim; j++){
            sum=0;
            ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=Dati[i];
                ave2+=Dati[i]*Dati[i];
            }
            AV.push_back(sum/double(j+1));
            AV2.push_back(ave2/double(j+1));
            Err.push_back(error(AV[j],AV2[j],j));

            if(j==0) { Err[j]=0; }

            risul<<double(j)<<"\t"<<AV[j]<<"\t"<<Err[j]<<endl;
        }
        risul.close();
    }
}

//***********************************  EX 8  ***********************************


namespace Ex8{
    double DataBlocking( vector<double> dati, int blk, string output_file="risultati.dat" ){
        ofstream risul(output_file);
        vector<double> finalAV(blk);
        vector<double> finalAV2(blk);
        vector<double> err(blk);
        double ave2=0;
        double sum=0;

        for (int j=0; j<blk; j++){
            sum=ave2=0;
            for (int i=0; i<j+1; i++){
                sum+=dati[i]/2.5;
                //cout << ". "<< i << "\t" << dati[i]<<endl;
                ave2+=pow(dati[i],2);
            }
            //cout << "av: "<<j<<"\tsum: "<<sum<<"\t"<<sum/double(j+1)<<endl;
            finalAV[j] = sum/double(j+1);
            finalAV2[j] = ave2/double(j+1);
            err[j] = error(finalAV[j],finalAV2[j],j);
            risul<<double(j+1)<<"\t"<<finalAV[j]<<"\t"<<err[j]<<endl;
        }
        risul.close();
        return 0.;
    }
}

#endif  