#include <iostream>
#include "Avaliation_Function.h"
#include "ParticleSwarm.h"
#define SIZEPOPULATION 2
#define SIZEPROBLEM 1

using namespace std;

int main()
{
    double *x;
    x = ParticleSwarm(SIZEPROBLEM,SIZEPOPULATION);

    cout<<"Minimizador: ";
    for(int i=0; i<SIZEPROBLEM; i++){ cout<<x[i]<<" ";}
    cout<<endl<<"Hello world!"<<endl;

    return 0;
}
