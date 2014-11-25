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
//            cout<<"sample1>> "<<sample[i]->objective_function<<endl;
            sample[i]->standard_deviation = progenitor[i]->standard_deviation;
            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progenitor[i]->position[j]; }
        }
        if(i >=MI){
            sample[i]->objective_function = progeny[t]->objective_function;
//            cout<<"sample2>> "<<sample[i]->objective_function<<endl;
            sample[i]->standard_deviation = progeny[t]->standard_deviation;
            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progeny[t]->position[j]; }
            t++;
        }
    }
    QuickSort(sample, 0, (MI+LAMBDA)-1, dimension);
    for(int i=0; i<MI; i++){
        progenitor[i]->objective_function = sample[i]->objective_function;
//        cout<<"progenitor<< "<<progenitor[i]->objective_function<<endl;
        progenitor[i]->standard_deviation = sample[i]->standard_deviation;
        for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = sample[i]->position[j]; }
        delete []sample[i]->position;
        delete sample[i];
    }
    //cout<<progenitor[0]->objective_function<<endl;
    delete []sample;
}

void Evolutionary_Strategy3(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

        if(delta > 0){
        srand(seed);
        criteria = 0;
        Individual **progenitor = new Individual*[MI];
        Individual **progeny = new Individual*[LAMBDA];
        Individual *best_individual = new Individual();

        int i;
        for(i=0; i<LAMBDA; i++){ progeny[i] = new Individual(); progeny[i]->position = new double[dimension]; }
        bool success = false;

       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);
       functionEvaluations = 0;
       for(i=0; i<MI; i++){
            progenitor[i] = new Individual();
            progenitor[i]->position = new double[dimension];
            if(lb != NULL && ub != NULL){
                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = (ub[i] - lb[i])*generate_ramdom() + lb[i]; }
            }
            else{ for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = generate_ramdom(); } }
            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
            functionEvaluations++;
            progenitor[i]->standard_deviation = Normal_distribution(0, 1/(sqrt(dimension)));
        }

        best_individual->position = new double[dimension];
        best_individual->objective_function = progenitor[0]->objective_function;
        best_individual->standard_deviation = progenitor[0]->standard_deviation;
        for(int i=0; i<dimension; i++){ best_individual->position[i] = progenitor[0]->position[i]; }
        for(int i=1; i<MI; i++){
            if(progenitor[i]->objective_function < best_individual->objective_function){
                best_individual->standard_deviation = progenitor[i]->standard_deviation;
                best_individual->objective_function = progenitor[i]->objective_function;
                for(int j=0; j<dimension; j++){ best_individual->position[j] = progenitor[i]->position[j]; }
            }
        }

        criteria = Number_Evaluations(number_function);
        int es = 0, ps  = 0;
        int q = 0;
        while(functionEvaluations < criteria){
            cout<<best_individual->objective_function<<"  ";
            success = false;
            q++;
            for(i=0; i<MI; i++){
                for(int t=0; t<LAMBDA && functionEvaluations<criteria; ){
                    for(int j=0; j<LAMBDA/MI && functionEvaluations<criteria; j++, t++){
                        for(int k=0; k<dimension; k++){
                            progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->standard_deviation);
                            if(lb != NULL && ub != NULL){
                                if(progeny[t]->position[k] < lb[i]){ progeny[t]->position[k] = lb[i];}
                                if(progeny[t]->position[k] > ub[i]){ progeny[t]->position[k] = ub[i];}
                            }
                        }
                        progeny[t]->standard_deviation = progenitor[i]->standard_deviation;
                        progeny[t]->objective_function = Compute_Function(progeny[t]->position, dimension, number_function);
                        functionEvaluations++;
                        if(progeny[t]->objective_function < progenitor[i]->objective_function){
                            if(progeny[t]->objective_function < best_individual->objective_function){
                                best_individual->objective_function = progeny[t]->objective_function;
                                best_individual->standard_deviation = progeny[t]->standard_deviation;
                                for(int w=0; w<dimension; w++){ best_individual->position[w] = progeny[t]->position[w]; }
                                success = true;
                            }
                        }
                    }
                }
                progenitor[i]->standard_deviation = progenitor[i]->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));
            }
            if(!success){
                    es++;
                    bool exit = false;
                    if(functionEvaluations < criteria){
                            if(Exploratory_Moves(delta, best_individual, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
                            else{
                                if(delta > MAX_DELTA){
                                    delta = (0.5)*delta;
                                }
                                    exit = true;
                            }
                    }
                    if(exit)ps++;
            }
            Selection(progenitor, progeny, dimension);
        }

        for(i=0; i<dimension; i++){ x[i] = best_individual->position[i]; }
//        cout<<Compute_Function(x, dimension, number_function)<<endl;
//        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
//        cout<<"AVALIACOES DE FUNCAO ---------------- "<<functionEvaluations<<endl;
//        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
//        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
//        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
//        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;

        for(i=0; i<MI; i++){
            delete []progenitor[i]->position;
            delete []progeny[i]->position;
            delete progenitor[i];
            delete progeny[i];
        }
        delete []progenitor;
        delete []progeny;
//        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
//        delete []pattern;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
     }
}
