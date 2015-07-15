#include <iostream>
#include <fstream>
#include "Avaliation_Function.h"
#include "Estrategias.h"
#include "Solution.h"


#define DIMENSAO 30
#define DELTA 0.7
#define INF 3.40282347E+38F
#define MEDIA_ESPERADA 0.7


using namespace std;


int main(int argc, char *argv[])
{

    if(argc == 4){
        int seed = atoi(argv[2]);
        int function = atoi(argv[1]);
//        int dimension = atoi(argv[3]);

//        cout<<function<<";"<<seed<<";"<<DIMENSAO<<";";
        double *x = new double[DIMENSAO];
        PSO(DIMENSAO, seed, INF, function, x);
//        VerificadorSolucao(x, DIMENSAO, function);
       // cout<<"Resultado final: "<<Compute_Function(x, DIMENSAO, function)<<endl;
//        cout<<endl<<endl;
        delete []x;
    }
    else{
        double *x = new double[DIMENSAO];
        PSO(DIMENSAO, 0, INF, 1, x);
       // cout<<"Resultado final: "<<Compute_Function(x, DIMENSAO, 1)<<endl;
        delete []x;
    }
    return 0;
}

