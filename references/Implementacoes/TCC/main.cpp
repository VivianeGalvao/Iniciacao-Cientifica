#include <iostream>
#include <fstream>
#include "Avaliation_Function.h"
#include "Estrategias.h"
#include "Solution.h"

#define DIMENSAO 30
#define DELTA 0.7
#define INF 3.40282347E+38F
#define MEDIA_ESPERADA 0.7
#define DELTA 0.7

using namespace std;

int main(int argc, char** argv)
{
    if(argc == 4){
        int a = atoi(argv[0]);
        int funcao = atoi(argv[1]);
        int semente = atoi(argv[2]);
        //int estrategia = atoi(argv[3]);
        double *x = new double[DIMENSAO];
        cout<<funcao<<" ; "<<semente<<" ; ";
        PSwarm(DIMENSAO, semente, INF, funcao, x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy1(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy2(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy3(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }
        cout<<endl;

        delete []x;
    }
    return 0;
}
