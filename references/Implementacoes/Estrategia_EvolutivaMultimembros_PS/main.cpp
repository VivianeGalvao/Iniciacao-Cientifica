#include <iostream>
#include <fstream>
#include "Avaliation_Function.h"
#include "ESPS.h"
#define DIM 30
#define N 11

using namespace std;

int main()
{
    ofstream myfile;
    myfile.open("results_Multimembers.csv");
    myfile<<"Dimensão;"<<DIM<<"\n";
    myfile<<"Media esperada;"<<0.7<<"\n";
    myfile<<"Delta Inicial;"<<0.7<<"\n";
    myfile<<"\n";
    myfile<<"Num Function; Seed; Valor da Função Objetivo\n";
    double *x = new double[DIM];
    for(int i=1; i<N+1; i++){
        cout<<"NUMERO DA FUNÇAO -------------------- "<<i<<endl;
        for(int j=1; j<4; j++){
            myfile<<i<<";";
            myfile<<j<<";";
            Evolutionary_Strategy(j, 0.7, DIM, i, 0.7, x);
           // for(int i=0; i<DIM; i++){ cout<<"x["<<i+1<<"]"<<x[i]<<endl; }
           myfile<<Compute_Function(x, DIM, i)<<"\n";
           VerificadorSolucao(x, DIM, i);
           cout<<endl;
        }
    }

    myfile.close();
    delete []x;
    return 0;
}
