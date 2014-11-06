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

bool Exploratory_Moves(double *pattern, double delta, Individual *sample, int size, int number_function, double* lb, double* ub){

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx = sample->objective_function, fx_perturbation=0.0;

    for(i = 0; i<size; i++){x_perturbation[i] = sample->position[i];}

    for(i=0; i<size; i++){

        x_perturbation[i] = sample->position[i] + delta*pattern[i];

        if(lb != NULL && ub != NULL){
            if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){
                x_perturbation[i] = sample->position[i] - delta*pattern[i];
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = sample->position[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){ sample->position[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = sample->position[i]; }
                }
            } else{
                 fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                if(fx < fx_perturbation){
                    x_perturbation[i] = sample->position[i] - delta*pattern[i];
                }
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = sample->position[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
                    if(fx > fx_perturbation){   sample->position[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = sample->position[i]; }
                }
            }
        }

        else{
            fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
            if(fx < fx_perturbation){
                x_perturbation[i] = sample->position[i] - delta*pattern[i];
                fx_perturbation = Compute_Function(x_perturbation, size, number_function); stop++;
            }
            if(fx > fx_perturbation){ sample->position[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
            else{ x_perturbation[i] = sample->position[i]; }
        }
    }

    if(exit){ sample->objective_function = fx; }
    delete []x_perturbation;
    return exit;
}

double Normal_distribution(double mean, double variancia){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,variancia);
    return distribution(generator);
}

void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension){

    double pivot;
    Individual *aux = new Individual();
    aux->position = new double[dimension];
    i[0] = left; j[0] = right;
    int mean = (i[0] + j[0])/2;
    pivot = sample[mean]->objective_function;

    do{
        while(pivot > sample[i[0]]->objective_function){ i[0]++; }
        while(pivot < sample[j[0]]->objective_function){ j[0]--; }

        if( i[0] <= j[0]){
            aux->objective_function = sample[i[0]]->objective_function;
            aux->standard_deviation = sample[i[0]]->standard_deviation;
            for(int k=0; k<dimension; k++){ aux->position[k] = sample[i[0]]->position[k]; }

            sample[i[0]]->objective_function = sample[j[0]]->objective_function;
            sample[i[0]]->standard_deviation = sample[j[0]]->standard_deviation;
            for(int k=0; k<dimension; k++){ sample[i[0]]->position[k] = sample[j[0]]->position[k]; }

            sample[j[0]]->objective_function = aux->objective_function;
            sample[j[0]]->standard_deviation = aux->standard_deviation;
            for(int k=0; k<dimension; k++){ sample[j[0]]->position[k] = aux->position[k]; }

            i[0]++; j[0]--;
        }

    }while(i[0] <= j[0]);
    delete aux;
}

void QuickSort(Individual **sample, int left, int right, int dimension){
    int *i = new int(), *j = new int();
    Partition(sample, left, right, i, j, dimension);
    if(left < j[0]){ QuickSort(sample, left, j[0], dimension); }
    if(i[0] < right){ QuickSort(sample, i[0], right, dimension); }
    delete i;
    delete j;
}

void Selection(Individual **progenitor, Individual **progeny, int dimension){
    Individual **sample = new Individual*[MI+LAMBDA];
    for(int i=0, t=0; i<MI+LAMBDA && t<LAMBDA; i++){
        sample[i] = new Individual();
        sample[i]->position = new double[dimension];
        if(i < MI){
            sample[i]->objective_function = progenitor[i]->objective_function;
            sample[i]->standard_deviation = progenitor[i]->standard_deviation;
            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progenitor[i]->position[j]; }
        }
        if(i >=MI){
            sample[i]->objective_function = progeny[t]->objective_function;
            sample[i]->standard_deviation = progeny[t]->standard_deviation;
            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progeny[t]->position[j]; }
            t++;
        }
    }
  QuickSort(sample, 0, (MI+LAMBDA)-1, dimension);
    for(int i=0; i<MI; i++){
        progenitor[i]->objective_function = sample[i]->objective_function;
        progenitor[i]->standard_deviation = sample[i]->standard_deviation;
        for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = sample[i]->position[j]; }
        delete []sample[i]->position;
        delete sample[i];
    }
    delete []sample;
}

void Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        srand(seed);
        double **pattern = new double*[2*dimension];
        Individual **progenitor = new Individual*[MI];
        Individual **progeny = new Individual*[LAMBDA];

        int i;
        for(i=0; i<LAMBDA; i++){ progeny[i] = new Individual(); progeny[i]->position = new double[dimension]; }
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
            progenitor[i] = new Individual();
            progenitor[i]->position = new double[dimension];
            if(lb != NULL && ub != NULL){
                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = (ub[i] - lb[i])*(rand()%10) + lb[i]; }
            }
            else{ for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = rand()%10*0.01; } }
            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
            stop++;
            progenitor[i]->standard_deviation = expected_mean/sqrt(dimension);
        }

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int q = 0;
        while(stop < criteria){

            for(i=0; i<MI; i++){
                success = false;
                int t=0;
                for(int j=0; j<LAMBDA/MI && t<LAMBDA && stop<criteria; j++, t++){
                    q++;
                    for(int k=0; k<dimension; k++){
                        progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->standard_deviation);
                        if(lb != NULL && ub != NULL){
                            if(progeny[t]->position[k] < lb[i]){ progeny[t]->position[k] = progenitor[i]->position[k]; }
                            if(progeny[t]->position[k] > ub[i]){ progeny[t]->position[k] = progenitor[i]->position[k]; }
                        }
                    }
                    progeny[t]->standard_deviation = progenitor[i]->standard_deviation;
                    progeny[t]->objective_function = Compute_Function(progeny[t]->position, dimension, number_function);
                    stop++;
                    if(progeny[t]->objective_function < progenitor[i]->objective_function){ success = true; }
                }
                if(!success){
                    es++;
                    bool exit = false;
                    for(int k=0; k<2*dimension && stop < criteria; k++){
                            if(Exploratory_Moves(pattern[k],delta, progenitor[i], dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
                            else{ delta = (0.5)*delta; exit = true; }
                    }
                    if(exit)ps++;
                    if(delta == 0)delta = 0.7;
                }
                progenitor[i]->standard_deviation = progenitor[i]->standard_deviation*exp(Normal_distribution(0, 1/dimension));
            }
            Selection(progenitor, progeny, dimension);
        }

        for(i=0; i<dimension; i++){ x[i] = progenitor[0]->position[i]; }

        cout<<"AVALIACOES DE FUNCAO ---------------- "<<stop<<endl;
        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;

        for(i=0; i<MI; i++){
            delete []progenitor[i]->position;
            delete []progeny[i]->position;
            delete progenitor[i];
            delete progeny[i];
        }
        delete []progenitor;
        delete []progeny;
        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
        delete []pattern;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
     }
}

