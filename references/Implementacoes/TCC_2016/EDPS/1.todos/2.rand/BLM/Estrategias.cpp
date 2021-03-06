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
#define MAX_DELTA 0.00001

using namespace std;

int func_eval=0;
double delta;
// int success_direction = -1;
int mark;

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

        for(int t=0, i=mark; t<directions; t++, i++){
            if(i==2*size)i=0;
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
//                     if(success_direction == i){
//                         delta = 2*delta;
//                     }
//                     else{
//                         success_direction = i;
//                     }
                    exit = true;
                    mark = i+1;
                }
//                if(functionEvaluations%10==0){
//                        cout<<";"<<setprecision(10)<<sample->fitness;
//                    }
            }
            if(exit)break;
        }

        if(!exit){
//             success_direction = -1;
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

double EvolucaoDiferencialBL(double (*objfun)(double*), double fator_ponderacao, double cr, int dimension, int num_individuos, int seed, double *lb, double *ub, double delta_inicial){
    if(delta_inicial > 0){
        delta = delta_inicial;
//         success_direction = -1;
        mark = 0;
        func_eval=0;
        srand(seed);

        Individuo **pop = new Individuo*[num_individuos];
        Individuo *best = new Individuo(dimension);

        int active[num_individuos];
        int actives = num_individuos;

        if(delta >= INF){
            double mindelta = -INF;
            if(lb && ub){
                for(int i=0; i<dimension; i++){
                    if((ub[i]-lb[i]) > mindelta){
                        mindelta = (ub[i]-lb[i]);
                    }
                }
                delta = mindelta/5;
            }
            if(mindelta >=INF || mindelta <= MAX_DELTA){ delta = 2*sqrt(sqrt(MAX_DELTA)); }
        }
        double limit = delta;

        for(int i=0; i<num_individuos; i++){
            pop[i] = new Individuo(dimension);
            active[i] = 1;

            for(int j=0; j<dimension; j++){
                if(lb && ub){
                    pop[i]->posicao[j] = (ub[j]-lb[j])*random_generate() + lb[j];
                }
                else{
                    pop[i]->posicao[j] = random_generate();
                }
            }
            pop[i]->valor = objfun(pop[i]->posicao);
            func_eval++;
        }

        int ibest = 0;
        best->valor = pop[0]->valor;
        for(int i=0; i<dimension; i++){
            best->posicao[i] = pop[0]->posicao[i];
        }
        for(int i=1; i<num_individuos; i++){
            if(best->valor > pop[i]->valor){
                ibest = i;
                best->valor = pop[i]->valor;
            }
        }
        for(int i=0; i<dimension; i++){
            best->posicao[i] = pop[ibest]->posicao[i];
        }

        int parada = 2000;

        while(func_eval < parada && actives > 3){
            bool succes = false;
            int alpha, beta, gamma;
            double mutado[actives][dimension];
            Individuo **tentativa = new Individuo*[actives];
            for(int i=0; i<actives; i++){
                tentativa[i] = new Individuo(dimension);
            }

            //mutação
            for(int t=0,i=0; t<num_individuos && i<actives && actives > 3; t++){
                if(active[t] == 1){
                    alpha = rand()%num_individuos;
                    beta = rand()%num_individuos;
                    gamma = rand()%num_individuos;
                    while(active[alpha] == 0){
                        alpha = rand()%num_individuos;
                    }
                    while(beta == alpha || active[beta] == 0){
                        beta = rand()%num_individuos;
                    }
                    while(gamma==beta || gamma==alpha || active[gamma] == 0){
                        gamma = rand()%num_individuos;
                    }
                    for(int j=0; j<dimension; j++){
                    mutado[i][j] = pop[gamma]->posicao[j] + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);
//                    mutado[i][j] = best->posicao[j] + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);
//                    mutado[i][j] = pop[i]->posicao[j] + fator_ponderacao*(best->posicao[j] - pop[i]->posicao[j]) + fator_ponderacao*(pop[alpha]->posicao[j] - pop[beta]->posicao[j]);

                        if(lb && ub){
                            if(mutado[i][j] > ub[j]){
                                mutado[i][j] = ub[j];
                            }
                            if(mutado[i][j] < lb[j]){
                                mutado[i][j] = lb[j];
                            }
                        }
                    }
                    i++;
                }
            }

            //cruzamento
            double r;
//            for(int i=0; i<num_individuos; i++){
            for(int i=0; i<actives; i++){
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

            //selecao
            for(int t=0, i=0; t<num_individuos && i<actives; t++, i++){
                if(active[t] == 1){
                    tentativa[i]->valor = objfun(tentativa[i]->posicao);
                    func_eval++;
                    if(tentativa[i]->valor < pop[t]->valor){
                        pop[t]->valor = tentativa[i]->valor;
                        for(int j=0; j<dimension; j++){
                            pop[t]->posicao[j] = tentativa[i]->posicao[j];
                        }
                        if(pop[i]->valor < best->valor){
                            succes=true;
                            ibest = t;
                            best->valor = pop[t]->valor;
                            for(int j=0; j<dimension; j++){
                                best->posicao[j] = pop[t]->posicao[j];
                            }
                        }
                    }
                }
            }

            for(int i=0; i<actives; i++){
                delete tentativa[i];
            }
            delete tentativa;

//            for(int i=0; i<num_individuos; i++){
//                if(active[i] == 1){
//                    double dist = 0;
//                    for(int j=0; j<dimension; j++){
//                        dist += (best->posicao[j] - pop[i]->posicao[j])*(best->posicao[j] - pop[i]->posicao[j]);
//                    }
//                    dist = sqrt(dist);
//
//                    if(dist < limit){
//                        active[i] = 0;
//                        actives--;
//                    }
//                }
//            }

            if(!succes){
               Exploratory_Moves(objfun, best, dimension, lb, ub);
            }
        }

//        cout<<";"<<setprecision(10)<<best->valor;

//        delete best;
        for(int i=0; i<num_individuos; i++){
            delete pop[i];
        }
        delete pop;

        return best->valor;
    }
    else{
        cout<<"Delta menor que zero. Erro."<<endl;
        return 10000000000;
    }
}
