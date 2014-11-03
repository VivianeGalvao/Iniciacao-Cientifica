#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include "Avaliation_Function.h"
#include "Solution.h"
#include<random>

#define DLB_MAX 1.7976931348623158e+308
#define EULER 2.71828182845
#define MI 2
#define LAMBDA 6

using namespace std;

int stop=0;

void VerificadorSolucao(double *x, int dimension, int number_function){
    if(x != NULL){
        double *lb = new double[dimension], *ub = new double[dimension];
        Lower_Bounds(number_function, dimension, lb);
        Upper_Bounds(number_function, dimension, ub);
        for(int i=0; i<dimension; i++){
            if(x[i] < lb[i]){ cout<<"Solucao nao-factivel"<<endl; break; }
            if(x[i] > ub[i]){ cout<<"Solucao nao-factivel"<<endl; break; }
        }
        delete []lb;
        delete []ub;
    }
}

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, double function, int size, int number_function, double* lb, double* ub){

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx = function, fx_perturbation=0.0;

    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){

        x_perturbation[i] = x_iteration[i] + delta*pattern[i];

        if(lb != NULL && ub != NULL){
            if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            } else{
                 fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                if(fx < fx_perturbation){
                    x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                }
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            }
        }

        else{
            fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
            if(fx < fx_perturbation){
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
            }
            if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
            else{ x_perturbation[i] = x_iteration[i]; }
        }
    }

    delete []x_perturbation;
    return exit;
}

double Normal_distribution(double mean, double variancia){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,variancia);
    return distribution(generator);
}

void Selection(Individual *progenitor, Individual *progeny, int dimension){
        double sample[MI+LAMBDA][dimension];
        for(int i=0; i<MI+LAMBDA; i++){
            for(int j=0; j<dimension; j++){
                if(i<MI){
                    sample[i][j] = progenitor[i]->position[j];
                }
                else{
                    sample[i][j] = progeny[i]->position[j];
                }
            }
        }
        //QuickSort
        for(int i=0; i<MI; i++){
            for(int j=0; j<dimension; j++){
                progenitor[i]->position[j] = sample[i][j];
            }
        }
}

void Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        srand(seed);
        double **pattern = new double*[2*dimension];
        Individual *progenitor = new Individual[MI];
        Individual *progeny = new Individual[LAMBDA];
        for(i=0; i<LAMBDA; i++){ progeny[i]->position = new double[dimension]; }
        int i;
        bool success = false;

        for(i = 0; i<2*dimension; i++){
             pattern[i] = new double[dimension];
            for(int j=0; j<dimension; j++){
                if(i<dimension){
                    if(j==i){pattern[i][j] = 1.0;}
                    else{ pattern[i][j] = 0.0; }
                }
                else{
                    if(i-j == dimension){ pattern[i][j] = -1.0; }
                    else{ pattern[i][j] = 0.0; }
                }
            }
        }

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);
       stop = 0;
       for(i=0; i<MI; i++){
            progenitor[i].position = new double[dimension];
            if(lb != NULL && ub != NULL){
                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = (ub[i] - lb[i])*(rand()%10*0.01) + lb[i]*0.01; }
            }
            else{ for(int j=0; j<dimension; j++){ progenitor[i].position[j] = rand()%10*0.01; } }
            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
            stop++;
            progenitor[i]->standard_deviation = expected_mean/sqrt(dimension);
        }

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int q = 0;
        while(stop < criteria){
            q++;
            for(i=0; i<MI; i++){
                success = false;
                int t=0;
                for(int j=0; j<LAMBDA/MI && t<LAMBDA; j++, t++){
                    for(int k=0; k<dimension; k++){
                        progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->standard_deviation);
                        if(lb != NULL && ub != NULL){
                            if(progeny[t]->position[k] < lb[i]){ progeny[t]->position[k] = progenitor[i]->position[k]; }
                            if(progeny[t]->position[k] > ub[i]){ progeny[t]->position[k] = progenitor[i]->position[k]; }
                        }
                    }
                    progeny[t]->standard_deviation = progenitor[i]->standard_deviation;
                    progeny[t]->objective_function = Compute_Function(progeny[t], dimension, number_function);
                    stop++;
                    if(progeny[t]->objective_function < progenitor[i]->objective_function){ success = true; }

                }
                if(!success){
                    es++;
                    bool exit = false;
                    for(int k=0; k<2*dimension && stop < criteria; k++){
                            if(Exploratory_Moves(pattern[k],delta, progenitor[i], progenitor[i]->objective_function, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
                            else{ delta = (0.5)*delta; exit = true; }
                    }
                    if(exit)ps++;
                }
                progenitor[i]->standard_deviation = progenitor[i]->standard_deviation + Normal_distribution(0, 1/dimension);
            }
            Selection(progenitor, progeny, dimension);
        }
        for(i=0; i<dimension; i++){ x[i] = progenitor[0]->position[i]; }


        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;

        for(i=0; i<MI; i++){
            delete progenitor[i].position;
            delete progeny[i].position;
        }
        delete []progenitor;
        delete []progeny;
        for(i=0; i<2*dimension+1; i++){ delete []pattern[i]; }
        delete []pattern;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
     }
}

