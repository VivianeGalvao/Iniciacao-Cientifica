#include <iostream>
#include <fstream>
#include<climits>
#include "Avaliation_Function.h"
#include "PsPso.h"
#define DIMENSION 30
#define FLT_MAX 3.40282347E+38F
#define SEED 3
#define N 11

using namespace std;

int main()
{
    ofstream myfile;
    myfile.open("results.csv");

    myfile<<"Dimensão;"<<DIMENSION<<"\n";
    myfile<<"Delta Inicial;"<<"Infinito"<<"\n";
    myfile<<"\n";
//    myfile<<"Num Function; Seed; Valor da Função Objetivo\n";
    myfile<<"Num Function;"<<" Media"<<"\n";

    double *x = new double[DIMENSION];
    double DELTA = FLT_MAX;
    double media = 0;
    //double DELTA = 0.01;
    for(int i=1; i<N+1; i++){
        cout<<"NUMERO DA FUNCAO --------------- "<<i<<endl;
        myfile<<i<<";";
        for(int j=1; j<SEED+1; j++){
            //myfile<<j<<";";
            PSwarm(DIMENSION, j, DELTA,i, x);
            media += Compute_Function(x, DIMENSION, i);
            //cout<<"SEMENTE ------------- "<<j<<"    MINIMIZADOR: "<<endl;
            //for(int i=0; i<DIMENSION && x!=NULL; i++){ cout<<"x"<<i+1<<": "<<x[i]<<endl;}
        }
        media = media/SEED;
        myfile<<media<<"\n";
        cout<<endl;
    }

    myfile.close();
    delete []x;
    return 0;
}
