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

void Exploratory_Moves(double (*objfun)(double *), Individuo *sample, int size, double* lb, double* ub){
    if(sample){
        int directions = 2*size;
        double **points = new double*[directions];
        double aux;
        for(int i=0; i<directions; i++){
            points[i] = new double[size];
        }

        bool fail;
        bool exit=false;
        for(int i=0; i<directions; i++){
             for(int j=0; j<size; j++){
                if(i<size){
                    if(i == j){
                        points[i][j] = sample->posicao[j] + delta;
                    }
                    else{
                        points[i][j] = sample->posicao[j];
                    }
                }
                else{
                    if((i - j) == size){
                        points[i][j] = sample->posicao[j] - delta;
                    }
                    else{
                        points[i][j] = sample->posicao[j];
                    }
                }
            }
        }

        for(int i=0; i<directions; i++){
            fail = false;
            for(int j=0; j<size; j++){
                if(lb && ub){
                    if(points[i][j] < lb[j] || points[i][j] > ub[j]){
                        fail = true;
                        break;
                    }
                }
            }
            if(!fail){
                aux = objfun(points[i]); func_eval++;
                if(sample->valor > aux){
                    sample->valor = aux;
                    for(int j=0; j<size; j++){
                        sample->posicao[j] = points[i][j];
                    }
                    if(success_direction == i){
                        delta = 2*delta;
                    }
                    else{
                        success_direction = i;
                    }
                    exit = true;
                }
            }
            if(exit)break;
        }

        if(!exit){
            success_direction = -1;
            delta = 0.5*delta;
        }

        for(int i=0; i<directions; i++){
            delete []points[i];
        }
        delete []points;

    }
    else{
        cout<<"Ponto nulo. Com amor, Pattern Search"<<endl;
    }
}


double EvolucaoDiferencial(double (*objfun)(double*), double fator_ponderacao, double cr, int dimension, int num_individuos, int seed, double *lb, double *ub){

    func_eval=0;
    srand(seed);
    int npop = num_individuos;
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
        int success = 0;

        int alpha, beta, gamma;
        double mutado[npop][dimension];
        Individuo **tentativa = new Individuo*[npop];
        for(int i=0; i<npop; i++){
            tentativa[i] = new Individuo(dimension);
        }

        //mutação
        for(int i=0; i<npop; i++){

            int ind = rand()%npop;
            if(pop[i]->valor < pop[ind]->valor){
                active[i] = 1;

                alpha = rand()%npop;
                beta = rand()%npop;
    //            gamma = rand()%num_individuos;

                while(alpha == i){
                    alpha = rand()%npop;
                }
                while(beta == alpha || beta == i){
                    beta = rand()%npop;
                }
    //            while(gamma == beta || gamma == alpha || gamma == i){
    //                gamma = rand()%num_individuos;
    //            }

                for(int j=0; j<dimension; j++){
                    mutado[i][j] = pop[i]->posicao[j] + fator_ponderacao*(best->posicao[j] - pop[i]->posicao[j]) + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);

                    if(mutado[i][j] > ub[j]){
                        mutado[i][j] = ub[j];
                    }
                    if(mutado[i][j] < lb[j]){
                        mutado[i][j] = lb[j];
                    }
                }
            }
            else{
                active[i] = 0;
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
                        success = 1;
                        best->valor = pop[i]->valor;
                        for(int j=0; j<dimension; j++){
                            best->posicao[j] = pop[i]->posicao[j];
                        }
                    }
                }
            }
            active[i] = 0;
        }

        if(success == 0){
            Exploratory_Moves(objfun, best, dimension, lb, ub);
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
