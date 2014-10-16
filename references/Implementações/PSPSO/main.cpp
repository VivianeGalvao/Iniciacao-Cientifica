#include <iostream>
#include "Avaliation_Function.h"
#include "PsPso.h"
#define DIMENSION 2
#define DELTA 10
#define SEED 20

using namespace std;

int main()
{
    double **pattern = new double*[DIMENSION*2];
    for(int i=0; i<DIMENSION*2; i++){ pattern[i] = new double[DIMENSION];}
    /** Gerando a matriz de direções padrão*/ /**MAXIMAL POSITIVE BASE*/
    for(int j=0; j<DIMENSION*2; j++){
        for(int i=0; i<DIMENSION; i++){
           if(j < DIMENSION){
            if( i == j){ pattern[j][i] = 1.0;}
            else { pattern[j][i] = 0.0; }
           }
           else{
                if(j - i == DIMENSION){ pattern[j][i] = -1.0;}
                else { pattern[j][i] = 0.0; }
           }
        }
      }
    cout<<"---------------------------------------------"<<endl;
    cout<<"MATRIX OF PATTERNS"<<endl;
    for(int i=0; i<DIMENSION*2; i++){
        cout<<i<<"| ";
        for(int j=0; j<DIMENSION; j++){
            cout<<pattern[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"---------------------------------------------"<<endl;
    double *x = PSwarm(DIMENSION, SEED, DELTA, pattern );

    cout<<"MINIMIZADOR: "<<endl;
    for(int i=0; i<DIMENSION && x!=NULL; i++){ cout<<"x"<<i+1<<": "<<x[i]<<endl;}


    for(int i=0; i<DIMENSION*2; i++){ delete []pattern[i]; }
    delete []pattern;
    return 0;
}
