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


int main(int argc, char** argv)
{
    double *x = new double[DIMENSAO];
    // cout.precision();
    if(argc == 3){
        int funcao = atoi(argv[1]);
        int semente = atoi(argv[2]);

        cout<<funcao<<" ; "<<semente<<" ; "<<DIMENSAO<<";";

        PSwarm(DIMENSAO, semente, INF, funcao, x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy1(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy2(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy3(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; "; }

        Evolutionary_Strategy4(semente, MEDIA_ESPERADA , DIMENSAO, funcao, DELTA , x);
        if(VerificadorSolucao(x, DIMENSAO, funcao)){ cout<<Compute_Function(x, DIMENSAO, funcao)<<";"; }

        cout<<endl;

    }
    else{
        Evolutionary_Strategy3(1,0.7,30,1,0.7,x);
        if(VerificadorSolucao(x, DIMENSAO, 1)){ cout<<Compute_Function(x, DIMENSAO, 1)<<endl; }
        Evolutionary_Strategy4(1,0.7,30,1,0.7,x);
        if(VerificadorSolucao(x, DIMENSAO, 1)){ cout<<Compute_Function(x, DIMENSAO, 1)<<endl; }
    }

    delete []x;
    return 0;
}

