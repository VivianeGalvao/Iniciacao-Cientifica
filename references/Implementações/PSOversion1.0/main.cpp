#include <iostream>
#include "Avaliation_Function.h"
#include "ParticleSwarm.h"
#define SIZEPOPULATION 2000
#define SIZEPROBLEM 10

using namespace std;

int main()
{
    double *x;
    x = ParticleSwarm(SIZEPROBLEM,SIZEPOPULATION);

    cout<<"Minimizador: ";
    for(int i=0; i<SIZEPROBLEM; i++){ cout<<x[i]<<" ";}
    cout<<endl<<"Valor da funçao objetivo: "<<Compute_Function(x, SIZEPROBLEM, 1)<<endl;

    return 0;
}
