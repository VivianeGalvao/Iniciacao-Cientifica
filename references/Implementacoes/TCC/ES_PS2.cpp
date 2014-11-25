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

void Evolutionary_Strategy2(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        functionEvaluations = 0;
        srand(seed);
//        double **pattern = new double*[2*dimension];
        int i;
        bool success = false;
        Individual *individuo = new Individual();
        individuo->position = new double[dimension];
 //       individuo->standard_deviation = expected_mean/sqrt(dimension);
        individuo->standard_deviation = Normal_distribution(0, 1/(sqrt(dimension)));
//        individuo->standard_deviation = generate_ramdom();

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);


        if(lb != NULL && ub != NULL){ for(i=0; i<dimension; i++){ individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i]; } }
        else{ for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); } }
        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
        functionEvaluations++;

        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
        int t=0, functionEvaluations=0;

        while(functionEvaluations < criteria){
            cout<<individuo->objective_function<<"  ";
            success=false;
            double y[dimension];
            for(i=0; i<dimension; i++){
                y[i] = individuo->position[i] + Normal_distribution(0, individuo->standard_deviation);
                if(lb != NULL && ub != NULL){
                        if(y[i] < lb[i]){ y[i] = lb[i]; }
                        if(y[i] > ub[i]){ y[i] = ub[i]; }
                }
            }
            double aux = Compute_Function(y, dimension, number_function); functionEvaluations++;
            if(aux < best_function){
                individuo->objective_function = aux;
                for(i=0; i<dimension; i++){ individuo->position[i] = y[i]; }
                success = true;
            }
            //else{ individuo->standard_deviation = individuo->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension))); }
            individuo->standard_deviation = individuo->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));

            if(!success){
                es++;
                bool exit = false;
                if(functionEvaluations < criteria){
                        if(Exploratory_Moves(delta, individuo, dimension, number_function, lb, ub)){delta = 1.5*delta; exit = false; }
                        else{
                            if( delta > MAX_DELTA){ delta = (0.5)*delta; }
                            exit = true;
                        }
                }
                if(exit)ps++;
            }
            t = t+1;
        }

        for(int k=0; k<dimension; k++){ x[k] = individuo->position[k]; }
//        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
//        cout<<"AVALIACOES DA FUNCAO OBJETIVO ------- "<<functionEvaluations<<endl;
//        cout<<"NUMERO DE ITERACOES ----------------- "<<t<<endl;
//        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
//        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
//        cout<<"ITERACOES DE SUCESSO ---------------- "<<(t - es) + (es - ps)<<endl;


//        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
//        delete []pattern;
        delete individuo;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
    }
}
