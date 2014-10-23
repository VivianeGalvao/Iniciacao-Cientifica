#include <iostream>
#include "Avaliation_Function.h"
#include "ParticleSwarm.h"
#define SIZEPOPULATION 200
#define SIZEPROBLEM 2

using namespace std;

int main()
{
    double *x;
    x = ParticleSwarm(SIZEPROBLEM,SIZEPOPULATION, 0);

    cout<<"Minimizador: ";
    for(int i=0; i<SIZEPROBLEM; i++){ cout<<x[i]<<" ";}
    cout<<endl<<"Valor da funçao objetivo: "<<Compute_Function(x, SIZEPROBLEM, 1)<<endl;

    return 0;
}
