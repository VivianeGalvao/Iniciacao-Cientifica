#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "Avaliation_Function.h"
#include<random>
#define STOP 1;
using namespace std;

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function){
    cout<<endl<<"----------------"<<endl<<"EXPLORATORY MOVES"<<endl;

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx=0.0, fx_perturbation=0.0;

    fx = Compute_Function(x_iteration, size, number_function); /* initializing fx*/
    /* x1 = x0 */
    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){
        cout<<"Iteração: "<<i+1<<endl;
        cout<<"Padrão: "<<"| ";
        for(int t=0; t<size; t++){cout<<pattern[t]<<"| ";}
        cout<<endl;
        /* xk+1 = xk + delta*e1 */
        x_perturbation[i] = x_iteration[i] + delta*pattern[i];
        fx_perturbation = Compute_Function(x_perturbation, size, number_function);
        /* if f(xk+1) > f(xk) => unsuccessful iteration */
        /* try xk+1 = xk - delta*e1 */
        if(fx < fx_perturbation){
            x_perturbation[i] = x_iteration[i];
            x_perturbation[i] = x_iteration[i] - delta*pattern[i];
            fx_perturbation = Compute_Function(x_perturbation, size, number_function);
        }
        /* if f(xk+1) < f(xk) => successful iteration */
        if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true; cout<<"sucesso"<<endl;}
        else{ x_perturbation[i] = x_iteration[i]; }


        cout<<endl<<"-----------------------"<<endl;
           cout<<"f(x): "<<fx<<endl;
           cout<<"Minimizador: ";
           for(int t=0; t<size; t++){ cout<<x_iteration[t]<<" ";}
           cout<<endl<<"-------------------------"<<endl;
    }

    delete []x_perturbation;
    return exit;
}

double Normal_distribuition(double mean, double desvio_padrao){
    default_random_engine generator;
    normal_distribution<double> distribution(mean,desvio_padrao);
    return distribution(generator);
}

double* Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta){

    if(delta > 0){
        srand(seed);
        double **pattern = new double*[2*dimension];
        int t = 0, i, stop = 0;
        bool success = false;
        double *x = new double[dimension], desvio_padrao = expected_mean/sqrt(dimension);
        int *successful = new int[dimension*10];

        //matriz de padrões
        for(i = 0; i<2*dimension; i++){
            for(int j=0; j<dimension; j++){
                pattern[i] = new double[dimension];
                if(i<dimension){
                    if(i==j){pattern[i][j] = 1.0;}
                    else{ pattern[i][j] = 0.0; }
                }
                else{
                    if(i - j == dimension){ pattern[i][j] = -1.0; }
                    else{ pattern[i][j] = 0.0; }
                }
            }
        }

        for(i=0; i<dimension*10; i++){ successful[i] = 0; }
        //população inicial
        for(i=0; i<dimension; i++){ x[i] = (rand()%10)*0.1; }

        while(stop < 20*dimension){
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
            if(Compute_Function(y, dimension, number_function) < Compute_Function(x, dimension, number_function)){
                for(i=0; i<dimension; i++){ x[i] = y[i]; }
                successful[(t+1)%(dimension*10)] = 1;
                success = true;
            }
            else{ successful[(t+1)%(dimension*10)] = 0; }

            if(!success){
                for(i=0; i<2*dimension; i++){
                        if(Exploratory_Moves(pattern[i],delta, x, dimension, number_function)){ delta = 2*delta;}
                        else{ delta = (0.5)*delta; }
                }
            }
            t = t+1;
            stop++;
        }
        delete []successful;
        return x;
    }
    return NULL;
}
