#include <iostream>
#include "Avaliation_Function.h"
#include "ESPS.h"
#define DIM 2

using namespace std;

int main()
{
    double *x = Evolutionary_Strategy(0, 0.5, DIM, 1, 1);
    for(int i=0; i<DIM; i++){ cout<<"x["<<i<<"]: "<<x[i]<<endl; }

    cout << "Hello world!" << endl;
    return 0;
}
