#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "Estrategias.h"
#include "Individuo.h"
#include <time.h>
#include <string.h>
#include <fstream>
#include <cmath>

#define INF 1E+21

using namespace std;

int func_eval=0;
double delta;
int success_direction = -1;

double random_generate(){
    return ((rand())/(RAND_MAX+1.0));
}

double EvolucaoDiferencial(double (*objfun)(double*), double fator_ponderacao, double cr, int dimension, int num_individuos, int seed, int prob, double *lb, double *ub){

    func_eval=0;
    srand(seed);
    int npop = prob*num_individuos;
    int active[npop];

    Individuo **pop = new Individuo*[npop];
    Individuo *best = new Individuo(dimension);

    for(int i=0; i<npop; i++){
        pop[i] = new Individuo(dimension);

        for(int j=0; j<dimension; j++){
            if(lb && ub){
                pop[i]->posicao[j] = (ub[j]-lb[j])*random_generate() + lb[j];
            }
            else{
                pop[i]->posicao[j] = random_generate();
            }
        }
    }

    for(int i=0; i<npop; i++){
        pop[i]->valor = objfun(pop[i]->posicao);
        func_eval++;
    }

    int ibest = 0;
    best->valor = pop[0]->valor;
    for(int i=0; i<dimension; i++){
        best->posicao[i] = pop[0]->posicao[i];
    }
    for(int i=1; i<npop; i++){
        if(best->valor > pop[i]->valor){
            ibest = i;
            best->valor = pop[i]->valor;
        }
    }
    for(int i=0; i<dimension; i++){
        best->posicao[i] = pop[ibest]->posicao[i];
    }

//    int parada = Number_Evaluations(num_func);
    int parada = 2000;

    while(func_eval < parada){

        int alpha, beta, gamma;
        double mutado[npop][dimension];
        Individuo **tentativa = new Individuo*[npop];
        for(int i=0; i<npop; i++){
            tentativa[i] = new Individuo(dimension);
            active[i] = 0;
        }

        //mutação
        for(int i=0; i<npop; i++){
            double ohm = (double)random_generate();
            if(ohm < (1.0/(double)prob)){
                int ind = rand()%npop;
                if(pop[i]->valor < pop[ind]->valor){
                    alpha = rand()%npop;
                    beta = rand()%npop;

                    while(alpha == i){
                        alpha = rand()%npop;
                    }
                    while(beta == alpha || beta == i){
                        beta = rand()%npop;
                    }

                    for(int j=0; j<dimension; j++){
                        mutado[i][j] = pop[i]->posicao[j] + fator_ponderacao*(best->posicao[j] - pop[i]->posicao[j]) + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);

                        if(mutado[i][j] > ub[j]){
                            mutado[i][j] = ub[j];
                        }
                        if(mutado[i][j] < lb[j]){
                            mutado[i][j] = lb[j];
                        }
                    }

                    if(active[i] == 1){
                         //cruzamento
                        double r;
                        double aux_tentativa[dimension];
                        for(int j=0; j<dimension; j++){
                            r = random_generate();
                            if(r <= cr){
                                aux_tentativa[j] = mutado[i][j];
                            }
                            else{
                                aux_tentativa[j] = pop[i]->posicao[j];
                            }
                        }
                        double aux_valor = objfun(aux_tentativa);
                        func_eval++;

                        if(aux_valor < tentativa[i]->valor){
                            tentativa[i]->valor = aux_valor;
                            for(int j=0; j<dimension; j++){
                                tentativa[i]->posicao[j] = aux_tentativa[j];
                            }
                        }
                    }
                    else{
                        active[i] = 1;
                        //cruzamento
                        double r;
                        for(int j=0; j<dimension; j++){
                            r = random_generate();
                            if(r <= cr){
                                tentativa[i]->posicao[j] = mutado[i][j];
                            }
                            else{
                                tentativa[i]->posicao[j] = pop[i]->posicao[j];
                            }
                        }
                    }
                }
                else{
                    alpha = rand()%npop;
                    beta = rand()%npop;

                    while(alpha == ind){
                        alpha = rand()%npop;
                    }
                    while(beta == alpha || beta == ind){
                        beta = rand()%npop;
                    }

                    for(int j=0; j<dimension; j++){
                        mutado[ind][j] = pop[ind]->posicao[j] + fator_ponderacao*(best->posicao[j] - pop[ind]->posicao[j]) + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);

                        if(mutado[ind][j] > ub[j]){
                            mutado[ind][j] = ub[j];
                        }
                        if(mutado[ind][j] < lb[j]){
                            mutado[ind][j] = lb[j];
                        }
                    }

                    if(active[ind] == 1){
                        //cruzamento
                        double r;
                        double aux_tentativa[dimension];
                        for(int j=0; j<dimension; j++){
                            r = random_generate();
                            if(r <= cr){
                                aux_tentativa[j] = mutado[ind][j];
                            }
                            else{
                                aux_tentativa[j] = pop[ind]->posicao[j];
                            }
                        }
                        double aux_valor = objfun(aux_tentativa);
                        func_eval++;

                        if(aux_valor < tentativa[ind]->valor){
                            tentativa[ind]->valor = aux_valor;
                            for(int j=0; j<dimension; j++){
                                tentativa[ind]->posicao[j] = aux_tentativa[j];
                            }
                        }

                    }else{
                        active[ind] = 1;
                        //cruzamento
                        double r;
                        for(int j=0; j<dimension; j++){
                            r = random_generate();
                            if(r <= cr){
                                tentativa[ind]->posicao[j] = mutado[ind][j];
                            }
                            else{
                                tentativa[ind]->posicao[j] = pop[ind]->posicao[j];
                            }
                        }
                        tentativa[ind]->valor = objfun(tentativa[ind]->posicao);
                        func_eval++;
                    }
                }
            }
        }

        //cruzamento
        double r;
        for(int i=0; i<npop; i++){
            if(active[i] == 1){
               for(int j=0; j<dimension; j++){
                    r = random_generate();
                    if(r <= cr){
                        tentativa[i]->posicao[j] = mutado[i][j];
                    }
                    else{
                        tentativa[i]->posicao[j] = pop[i]->posicao[j];
                    }
                }
            }
        }

        //selecao
        for(int i=0; i<npop; i++){
            if(active[i] == 1){
                tentativa[i]->valor = objfun(tentativa[i]->posicao);
                func_eval++;
                if(tentativa[i]->valor < pop[i]->valor){
                    pop[i]->valor = tentativa[i]->valor;
                    for(int j=0; j<dimension; j++){
                        pop[i]->posicao[j] = tentativa[i]->posicao[j];
                    }
                    if(pop[i]->valor < best->valor){
                        best->valor = pop[i]->valor;
                        for(int j=0; j<dimension; j++){
                            best->posicao[j] = pop[i]->posicao[j];
                        }
                    }
                }
            }
            active[i] = 0;
        }

        for(int i=0; i<npop; i++){
            delete tentativa[i];
        }
        delete tentativa;
    }

//    cout<<";"<<setprecision(10)<<best->valor;
//    cout<<setprecision(10)<<best->valor;

    double aux = best->valor;
    delete best;
    for(int i=0; i<npop; i++){
        delete pop[i];
    }
    delete pop;

    return aux;
}
