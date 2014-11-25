#include <iostream>
#include "Estrategias.h"
#include "Solution.h"
#include "Avaliation_Function.h"
#include "PatternSearch.h"
#include<cmath>
#include <random>

#define NUMPARTICLES 50
#define MAX_DELTA 0.00001
#define INF 3.40282347E+38F
#define MI 4
#define LAMBDA 8

using namespace std;

int functionEvaluations;
int best_function;
int criteria;

double generate_ramdom() {
    return ((rand())/(RAND_MAX+1.0));
}

double Normal_distribution(double mean, double variancia){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,variancia);
    return distribution(generator);
}

void Evolutionary_Strategy1(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
       functionEvaluations = 0;
       srand(seed);
       int i;
       bool success = false;

       Individual *individuo = new Individual();
       individuo->position = new double[dimension];
       individuo->standard_deviation = expected_mean/sqrt(dimension);

       int *successful = new int[dimension*10];

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);

        for(i=0; i<dimension*10; i++){ successful[i] = 0; }
        //indivíduo inicial
        if(lb != NULL && ub!=NULL){
            for(i=0; i<dimension; i++){
                individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i];
            }
        }
        else{ for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); } }

        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
        functionEvaluations++;

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int t=0;

        while(functionEvaluations < criteria){
            cout<<individuo->objective_function<<"  ";
            success=false;
            //regra de 1/5 de sucessos
            if(t%dimension == 0 && t>=dimension*10){
                double sum=0, ps;
                for(i=0; i<dimension*10; i++){sum += successful[i]; }
                ps = sum/10*dimension;
                if(ps > 1/5){ individuo->standard_deviation = individuo->standard_deviation/0.85;}
                else if(ps < 1/5){ individuo->standard_deviation = individuo->standard_deviation*0.85; }
            }
            double y[dimension];
            for(i=0; i<dimension; i++){
                y[i] = x[i] + Normal_distribution(0, individuo->standard_deviation);
                if(lb != NULL && ub != NULL){
                    if(y[i] < lb[i]){ y[i] = lb[i]; }
                    if(y[i] > ub[i]){ y[i] = ub[i]; }
                }
            }
            double aux = Compute_Function(y, dimension, number_function); functionEvaluations++;
            if(aux < individuo->objective_function){
                individuo->objective_function = aux;
                for(i=0; i<dimension; i++){ individuo->position[i] = y[i]; }
                successful[(t+1)%(dimension*10)] = 1;
                success = true;
            }
            else{ successful[(t+1)%(dimension*10)] = 0;}

            if(!success){
                es++;
                bool exit = false;
                if(functionEvaluations < criteria){
                        if(Exploratory_Moves(delta, individuo, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
                        else{
                            if(delta > MAX_DELTA){ delta = (0.5)*delta; }
                                exit = true;
                        }
                }
                if(exit)ps++;
            }
            t = t+1;
        }

        for(int k=0; k<dimension; k++){ x[k] = individuo->position[k]; }
        delete []successful;

        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
    }
}
