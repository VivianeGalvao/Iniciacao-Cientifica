#include<iostream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <string>
#include <sstream>
#include <cfloat>
#include "Avaliation_Function.h"

#define dimension 30
#define number_functions 21

using namespace std;

int main(){
    double *x = new double[dimension]();
    for(int i=0; i<dimension; i++){
        x[i] = 0.0;
    }
    for(int i=1; i<=number_functions; i++){
        cout<<i<<": "<<Compute_Function(x, dimension, i)<<endl;
    }

    delete []x;
    return 0;
}
