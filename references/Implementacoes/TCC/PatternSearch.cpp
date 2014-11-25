#include <iostream>
#include "Estrategias.h"
#include "Solution.h"
#include "Avaliation_Function.h"
#include<cmath>
#include <random>

#define NUMPARTICLES 50
#define MAX_DELTA 0.00001
#define INF 3.40282347E+38F
#define MI 4
#define LAMBDA 8

using namespace std;

int functionEvaluations;

bool Exploratory_Moves(double delta, double *x, int size, int number_function, double* lb, double* ub){
    bool exit = false;
    int i;
    double *x_aux = new double[size];
    double *x_best = new double[size];
    double fx_best=best_function, fx_aux=0.0;

    for(i = 0; i<size; i++){x_aux[i] = x[i]; x_best[i] = x[i];}

    for(i=0; i<size; i++){
        x_aux[i] = x[i] + delta;

        if(lb != NULL && ub != NULL){
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    x_best[i] = x_aux[i];
                    fx_best = fx_aux;
                }
            }
            x_aux[i] = x[i] - delta;
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    x_best[i] = x_aux[i];
                    fx_best = fx_aux;
                }
            }
        }

        else{
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function);functionEvaluations++;
            if(fx_best > fx_aux){
                x_best[i] = x_aux[i];
                fx_best = fx_aux;
            }

            x_aux[i] = x[i] - delta;
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
            if(fx_aux < fx_best){
                x_best[i] = x_aux[i];
                fx_best = fx_aux;

            }
        }
    }

    if (fx_best < best_function) {
        exit = true;
        best_function = fx_best;
        for(i = 0; i<size; i++){x[i] = x_best[i];}
    }


    delete []x_aux;
    delete []x_best;
    return exit;
}

bool Exploratory_Moves(double delta, Individual *sample, int size, int number_function, double* lb, double* ub){

    bool exit = false;
    int i;
    double *x_aux = new double[size], *x_best = new double[size];
    double fx_best = sample->objective_function, fx_aux=0.0;

    for(i = 0; i<size; i++){ x_aux[i] = sample->position[i]; x_best[i] = sample->position[i]; }

    for(i=0; i<size; i++){

        x_aux[i] = sample->position[i] + delta;

        if(lb != NULL && ub != NULL){
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    fx_best = fx_aux;
                    x_best[i] = x_aux[i];
                }
            }
            x_aux[i] = sample->position[i] - delta;
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    fx_best = fx_aux;
                    x_best[i] = x_aux[i];
                }
            }
        }

        else{
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
            if(fx_aux < fx_best){
                fx_best = fx_aux;
                x_best[i] = x_aux[i];
            }

            x_aux[i] = sample->position[i] - delta;
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
            if(fx_aux < fx_best){
                fx_best = fx_aux;
                x_best[i] = x_aux[i];
            }
        }
    }

    if(fx_best < sample->objective_function){
         sample->objective_function = fx_best;
         for(i=0; i<size; i++){ sample->position[i] = x_best[i]; }
         exit = true;
    }
    delete []x_aux;
    delete []x_best;

    return exit;
}
