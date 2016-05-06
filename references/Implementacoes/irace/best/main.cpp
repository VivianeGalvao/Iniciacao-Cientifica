#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "asl.h"
#include "getstub.h"
#include "Estrategias.h"
#include "string.h"
#include <iomanip>

#define INF 1E+21
#define asl cur_ASL

#define SEED 6

using namespace std;

static fint NERROR = -1;

double objfun(double *x){
    return objval(0, x, &NERROR);
}

int main(int argc, char** argv)
{
    if(argc > 2){
        NERROR = -1;
        ASL *asl;
        FILE *nl;
        char *fmt, *stub, *func;
        cgrad *cg;
        ograd *og;

        asl = ASL_alloc(ASL_read_fg);
        stub = argv[1];
        nl = jac0dim(stub, (fint)strlen(stub));

        fg_read_ASL(asl, nl, 0);

        double *lb = NULL;
        double *ub = NULL;

        if(LUv[0] > -Infinity && LUv[1] < Infinity){
            lb = new double[n_var];
            ub = new double[n_var];
            for(int i=0; i<n_var; i++){
                lb[i] = LUv[2*i];
                ub[i] = LUv[2*i+1];
            }
        }
//        cout<<";"<<n_var;

        double mean = 0;
       // for(int seed=1; seed<=30; seed++){
            mean += EvolucaoDiferencial(&objfun, FP, CR, n_var, NI, 30, lb, ub);
        //}
        //mean = mean/30.0;
//        EvolucaoDiferencial(&objfun, FP, CR, n_var, NI, SD, lb, ub);

//        cout<<";"<<setprecision(10)<<mean;
	cout<<setprecision(10)<<mean;

    }
    else{

    }
    return 0;
}
