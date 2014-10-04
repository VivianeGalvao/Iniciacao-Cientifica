#include <iostream>
#include "GeneralPatternSearch.h"
#include "Avaliation_Function.h"
#define SIZEPROBLEM 2
#define SIZEBASIS 2*SIZEPROBLEM
#define DELTA 1.0
using namespace std;


int main()
{
    double *x = new double[SIZEPROBLEM], **pattern = new double*[SIZEBASIS], f_best;

    for(int i=0; i<SIZEBASIS; i++){ pattern[i] = new double[SIZEPROBLEM];}
    for(int i=0; i<SIZEPROBLEM; i++){ x[i] = 10.0; }

    cout<<endl<<"PATTERN SEARCH"<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"Dados do problema"<<endl;
    cout<<"Dimensão do Problema: "<<SIZEPROBLEM<<"; Delta: "<<DELTA<<endl;
    cout<<"Guess Initial: "<<endl;
    for(int i=0; i<SIZEPROBLEM; i++){ cout<<x[i]<<" ";}
    cout<<endl<<"----------------------------"<<endl;

    /** Gerando a matriz de direções padrão*/
    for(int j=0; j<SIZEBASIS; j++){
        for(int i=0; i<SIZEPROBLEM; i++){
           if(j < SIZEBASIS/2){
            if( i == j){ pattern[j][i] = 1.0;}
            else { pattern[j][i] = 0.0; }
           }
           else{
                if(j - i == SIZEPROBLEM){ pattern[j][i] = -1.0;}
                else { pattern[j][i] = 0.0; }
           }
        }
      }
    cout<<"---------------------------------------------"<<endl;
    cout<<"MATRIX OF PATTERNS"<<endl;
    for(int i=0; i<SIZEBASIS; i++){
        cout<<i<<"| ";
        for(int j=0; j<SIZEPROBLEM; j++){
            cout<<pattern[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"---------------------------------------------"<<endl;

    f_best = GeneralPatternSearch(DELTA, x, pattern, SIZEPROBLEM, 0.00001);
    cout<<"f_best "<<f_best<<endl;

    cout<<"Mínimo:"<<endl;
    for(int i=0; i<SIZEPROBLEM; i++){ cout<<x[i]<<"|";}
    cout<<endl;

    delete[]x;
    for(int i=0; i<SIZEPROBLEM; i++){ delete pattern[i];}
    delete[]pattern;
    return 0;
}
