#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "Avaliation_Function.h"
#include<random>
#define STOP 1;
using namespace std;

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function, double* lb, double* ub){


    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx=0.0, fx_perturbation=0.0;

    fx = Compute_Function(x_iteration, size, number_function); /* initializing fx*/
    /* x1 = x0 */
    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){
        /* xk+1 = xk + delta*e1 */
        x_perturbation[i] = x_iteration[i] + delta*pattern[i];

        if(lb != NULL && ub != NULL){
            if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){
                x_perturbation[i] = x_iteration[i];
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function);
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            } else{
                 fx_perturbation = Compute_Function(x_perturbation, size, number_function);
                /* if f(xk+1) > f(xk) => unsuccessful iteration */
                /* try xk+1 = xk - delta*e1 */
                if(fx < fx_perturbation){
//                    x_perturbation[i] = x_iteration[i];
                    x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                    fx_perturbation = Compute_Function(x_perturbation, size, number_function);
                }
                /* if f(xk+1) < f(xk) => successful iteration */
                if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                else{ x_perturbation[i] = x_iteration[i]; }
            }
        }

        else{
            fx_perturbation = Compute_Function(x_perturbation, size, number_function);

            /* if f(xk+1) > f(xk) => unsuccessful iteration */
            /* try xk+1 = xk - delta*e1 */
            if(fx < fx_perturbation){
                x_perturbation[i] = x_iteration[i];
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                fx_perturbation = Compute_Function(x_perturbation, size, number_function);
            }
            /* if f(xk+1) < f(xk) => successful iteration */
            if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
            else{ x_perturbation[i] = x_iteration[i]; }
        }
    }

    delete []x_perturbation;
    return exit;
}

double Normal_distribuition(double mean, double desvio_padrao){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,desvio_padrao);
    return distribution(generator);
}

double* Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        srand(seed);
        double **pattern = new double*[2*dimension+1];
        int i;
        bool success = false;
        double desvio_padrao = expected_mean/sqrt(dimension);
        int *successful = new int[dimension*10];

        //matriz de padrões
        for(i = 0; i<2*dimension+1; i++){
             pattern[i] = new double[dimension];
            for(int j=0; j<dimension; j++){
                if(i<dimension+1){
                    if(j==i-1){pattern[i][j] = 1.0;}
                    else{ pattern[i][j] = 0.0; }
                }
                else{
                    if(i-j == dimension + 1){ pattern[i][j] = -1.0; }
                    else{ pattern[i][j] = 0.0; }
                }
            }
        }

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);

        for(i=0; i<dimension*10; i++){ successful[i] = 0; }
        //indivíduo inicial
        for(i=0; i<dimension; i++){ x[i] = (rand()%10)*0.1; }

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int t=0, stop=0;

        while(stop < criteria){
            success=false;
            //regra de 1/5 de sucessos
            if(t%dimension == 0 && t>=dimension*10){
                double sum=0, ps;
                for(i=0; i<dimension*10; i++){sum += successful[i]; }
                ps = sum/10*dimension;
                if(ps > 1/5){ desvio_padrao = desvio_padrao/0.85;}
                if(ps < 1/5){ desvio_padrao = desvio_padrao*0.85; }
            }
            double y[dimension], normalDistribuition = Normal_distribuition(0, desvio_padrao);
            for(i=0; i<dimension; i++){ y[i] = x[i] + normalDistribuition; }
            if(lb != NULL && ub != NULL){
                for(i = 0; i<dimension; i++){
                    if(y[i] < lb[i]){ if(t%dimension==0){y[i] = lb[i];} }
                    if(y[i] > ub[i]){ if(t%dimension==0){y[i] = ub[i];} }
                }
            }
            if(Compute_Function(y, dimension, number_function) < Compute_Function(x, dimension, number_function)){
                for(i=0; i<dimension; i++){ x[i] = y[i]; }
                successful[(t+1)%(dimension*10)] = 1;
                success = true;
            }
            else{ successful[(t+1)%(dimension*10)] = 0;}

            if(!success){
                es++;
                bool exit = false;
                for(i=0; i<2*dimension+1; i++){
                        if(Exploratory_Moves(pattern[i],delta, x, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
                        else{ delta = (0.5)*delta; exit = true; }
                }
                if(exit)ps++;
            }
            t = t+1;
            stop++;
        }
        cout<<"NUMERO DE ITERACOES ----------------- "<<stop<<endl;
        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
        cout<<"ITERACOES DE SUCESSO ---------------- "<<(stop - es) + (es - ps)<<endl;
        cout<<"NUMERO DA FUNÇAO -------------------- "<<number_function<<endl;
        cout<<endl;
//        cout<<"FUNCAO OBJETIVO --------------------- "<<Compute_Function(x,dimension, number_function)<<endl;
//        cout<<"DELTA ------------------------------- "<<delta<<endl;

        delete []successful;
        for(i=0; i<2*dimension+1; i++){ delete []pattern[i]; }
        delete []pattern;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
        return x;
    }
    return NULL;
}
