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

//double generate_ramdom() {
//    return ((rand())/(RAND_MAX+1.0));
//}
//
//bool Exploratory_Moves(double delta, double *x, int size, int number_function, double* lb, double* ub){
//    bool exit = false;
//    int i;
//    double *x_aux = new double[size];
//    double *x_best = new double[size];
//    double fx_best=best_function, fx_aux=0.0;
//
//    for(i = 0; i<size; i++){x_aux[i] = x[i]; x_best[i] = x[i];}
//
//    for(i=0; i<size; i++){
//        x_aux[i] = x[i] + delta;
//
//        if(lb != NULL && ub != NULL){
//            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
//                if(functionEvaluations > criteria){return false;}
//                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//                if(fx_aux < fx_best){
//                    x_best[i] = x_aux[i];
//                    fx_best = fx_aux;
//                }
//            }
//            x_aux[i] = x[i] - delta;
//            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
//                if(functionEvaluations > criteria){return false;}
//                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//                if(fx_aux < fx_best){
//                    x_best[i] = x_aux[i];
//                    fx_best = fx_aux;
//                }
//            }
//        }
//
//        else{
//            if(functionEvaluations > criteria){return false;}
//            fx_aux = Compute_Function(x_aux, size, number_function);functionEvaluations++;
//            if(fx_best > fx_aux){
//                x_best[i] = x_aux[i];
//                fx_best = fx_aux;
//            }
//
//            x_aux[i] = x[i] - delta;
//            if(functionEvaluations > criteria){return false;}
//            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//            if(fx_aux < fx_best){
//                x_best[i] = x_aux[i];
//                fx_best = fx_aux;
//
//            }
//        }
//    }
//
//    if (fx_best < best_function) {
//        exit = true;
//        best_function = fx_best;
//        for(i = 0; i<size; i++){x[i] = x_best[i];}
//    }
//
//
//    delete []x_aux;
//    delete []x_best;
//    return exit;
//}
//
//bool Exploratory_Moves(double delta, Individual *sample, int size, int number_function, double* lb, double* ub){
//
//    bool exit = false;
//    int i;
//    double *x_aux = new double[size], *x_best = new double[size];
//    double fx_best = sample->objective_function, fx_aux=0.0;
//
//    for(i = 0; i<size; i++){ x_aux[i] = sample->position[i]; x_best[i] = sample->position[i]; }
//
//    for(i=0; i<size; i++){
//
//        x_aux[i] = sample->position[i] + delta;
//
//        if(lb != NULL && ub != NULL){
//            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
//                if(functionEvaluations > criteria){return false;}
//                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//                if(fx_aux < fx_best){
//                    fx_best = fx_aux;
//                    x_best[i] = x_aux[i];
//                }
//            }
//            x_aux[i] = sample->position[i] - delta;
//            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
//                if(functionEvaluations > criteria){return false;}
//                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//                if(fx_aux < fx_best){
//                    fx_best = fx_aux;
//                    x_best[i] = x_aux[i];
//                }
//            }
//        }
//
//        else{
//            if(functionEvaluations > criteria){return false;}
//            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//            if(fx_aux < fx_best){
//                fx_best = fx_aux;
//                x_best[i] = x_aux[i];
//            }
//
//            x_aux[i] = sample->position[i] - delta;
//            if(functionEvaluations > criteria){return false;}
//            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
//            if(fx_aux < fx_best){
//                fx_best = fx_aux;
//                x_best[i] = x_aux[i];
//            }
//        }
//    }
//
//    if(fx_best < sample->objective_function){
//         sample->objective_function = fx_best;
//         for(i=0; i<size; i++){ sample->position[i] = x_best[i]; }
//         exit = true;
//    }
//    delete []x_aux;
//    delete []x_best;
//
//    return exit;
//}
//
//
//
//void PSwarm(int dimension, int seed, double delta_initial, int number_function, double* position_global){
//
//    if(delta_initial > 0){
//        functionEvaluations = 0;
//        int number_particles = NUMPARTICLES;
//        int ps=0, pso=0;
//        double delta = delta_initial;
//
//        int i, j, NUMFUNC = number_function;
//        srand(seed);
//
//        Particle **population = new Particle*[NUMPARTICLES];
//        double *lb = new double[dimension], *ub = new double[dimension] ;
//        Lower_Bounds(NUMFUNC, dimension, lb);
//        Upper_Bounds(NUMFUNC, dimension, ub);
//
//        if(delta >= INF){
//            double mindelta = INF;
//            if(lb && ub){
//                for(i = 0; i<dimension; i++){
//                    if(mindelta > (ub[i] - lb[i])){ mindelta = ub[i] - lb[i]; }
//                }
//            }
//            if(mindelta >=INF || mindelta <= MAX_DELTA){ delta = 2*sqrt(sqrt(MAX_DELTA)); }
//            else{ delta = mindelta/5;}
//        }
//
//
//         //velocity parameters
//        double inertia_factor = 0.9;
//        double cognition_parameter = 0.5;
//        double social_parameter = 0.5;
//
//
//
//        //initialize a population of particles with random positions and velocities
//        functionEvaluations = 0;
//        for(i = 0; i<number_particles; i++){
//            population[i] = new Particle();
//            population[i]->position = new double[dimension];
//            population[i]->velocity = new double[dimension];
//            population[i]->best_position = new double[dimension];
//            //velocity parameters
//            for(j=0; j<dimension; j++){
//
//                if(lb != NULL && ub != NULL){
//                    population[i]->position[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
//                    //population[i]->velocity[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
//                    population[i]->velocity[j] = 0.0;
//                }
//                else{
//                    population[i]->position[j] = generate_ramdom();
//                    population[i]->velocity[j] = 0.0;
//                }
//                population[i]->best_position[j] = population[i]->position[j];
//                //velocity paramenters
//            }
//            population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC);functionEvaluations++;
//            population[i]->best_fitness = population[i]->fitness;
//        }
//        //population intialized
//
//
//        double fitness_global = population[0]->fitness;
//        for(j=0; j<dimension; j++){ position_global[j] = population[0]->position[j]; }
//        for(i=1; i<number_particles; i++){
//            if(population[i]->fitness < fitness_global){
//                fitness_global = population[i]->fitness;
//                for(j=0; j<dimension; j++){ position_global[j] = population[i]->position[j];}
//            }
//        }
//
//        int iteracoes = 0, maxEval = Number_Evaluations(number_function);
//        criteria = maxEval;
//         while(functionEvaluations < maxEval){
//            cout<<fitness_global<<"  ";
//            bool successful = false, test=false;
//            for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
//                for(j=0; j<dimension; j++){
//                    population[i]->velocity[j] = (inertia_factor*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
//                                                population[i]->position[j])) + (social_parameter*generate_ramdom()*(position_global[j] - population[i]->position[j]));
//
//
//                    population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
//                    if(lb != NULL && ub != NULL){
//                        if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
//                        if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
//                    }
//                }
//                population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC); functionEvaluations++;
//                if(population[i]->fitness < population[i]->best_fitness){
//                    population[i]->best_fitness = population[i]->fitness;
//                    for(j=0; j<dimension; j++){
//                        population[i]->best_position[j] = population[i]->position[j];
//                    }
//                    if(population[i]->fitness < fitness_global){
//                        fitness_global = population[i]->fitness;
//                        for(j=0; j<dimension; j++){
//                            position_global[j] = population[i]->position[j];
//                        }
//                        successful = true;
//                    }
//                }
//            }
//
//            if(!successful){
//                pso++;
//                if( functionEvaluations<maxEval ){
//                    best_function = fitness_global;
//                    if(Exploratory_Moves(delta, position_global, dimension, NUMFUNC, lb, ub)){ delta = 1.5*delta; test = false; fitness_global = best_function;}
//                    else{
//                        if(delta > MAX_DELTA){ delta = (0.5)*delta; }
//                        test=true;
//                    }
//                }
//                if(test){ ps++; }
//            }
//            iteracoes++;
//        }
//
//        for(i=0; i<number_particles; i++){
//            delete []population[i]->position;
//            delete []population[i]->best_position;
//            delete []population[i]->velocity;
//            delete population[i];
//        }
//        delete []population;
//        if(lb != NULL && ub != NULL){
//            delete []lb;
//            delete []ub;
//        }
//
////        for(int i=0; i<dimension*2; i++){ delete []pattern[i]; }
////        delete []pattern;
//
////        cout<<endl;
////        cout<<"NUMERO FUNCAO ------------------ "<<NUMFUNC<<endl;
////        cout<<"AVALIACOES DE FUNCAO ----------- "<<functionEvaluations<<endl;
////        cout<<"ITERAÇOES TOTAIS --------------- "<<iteracoes<<endl;
////        cout<<"ITERACOES DE SUCESSO ----------- "<<(iteracoes - pso) + (pso - ps)<<endl;
////        cout<<"ITERAÇÕES SEM SUCESSO - PSO ---- "<<pso<<endl;
////        cout<<"ITERAÇÕES SEM SUCESSO - PS ----- "<<ps<<endl;
////       // cout<<"DELTA FINAL -------------------- "<<delta<<endl;
////        cout<<endl;
//    }
//
//}
//
//double Normal_distribution(double mean, double variancia){
//    default_random_engine generator;
//    normal_distribution<double> distribution(mean,variancia);
//    return distribution(generator);
//}
//
//void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension){
//
//    double pivot;
//    Individual *aux = new Individual();
//    aux->position = new double[dimension];
//    i[0] = left; j[0] = right;
//    int mean = (i[0] + j[0])/2;
//    pivot = sample[mean]->objective_function;
//
//    do{
//        while(pivot > sample[i[0]]->objective_function){ i[0]++; }
//        while(pivot < sample[j[0]]->objective_function){ j[0]--; }
//
//        if( i[0] <= j[0]){
//            aux->objective_function = sample[i[0]]->objective_function;
//            aux->standard_deviation = sample[i[0]]->standard_deviation;
//            for(int k=0; k<dimension; k++){ aux->position[k] = sample[i[0]]->position[k]; }
//
//            sample[i[0]]->objective_function = sample[j[0]]->objective_function;
//            sample[i[0]]->standard_deviation = sample[j[0]]->standard_deviation;
//            for(int k=0; k<dimension; k++){ sample[i[0]]->position[k] = sample[j[0]]->position[k]; }
//
//            sample[j[0]]->objective_function = aux->objective_function;
//            sample[j[0]]->standard_deviation = aux->standard_deviation;
//            for(int k=0; k<dimension; k++){ sample[j[0]]->position[k] = aux->position[k]; }
//
//            i[0]++; j[0]--;
//        }
//
//    }while(i[0] <= j[0]);
//    delete aux;
//}
//
//void QuickSort(Individual **sample, int left, int right, int dimension){
//    int *i = new int(), *j = new int();
//    Partition(sample, left, right, i, j, dimension);
//    if(left < j[0]){ QuickSort(sample, left, j[0], dimension); }
//    if(i[0] < right){ QuickSort(sample, i[0], right, dimension); }
//    delete i;
//    delete j;
//}
//
//void Selection(Individual **progenitor, Individual **progeny, int dimension){
//    Individual **sample = new Individual*[MI+LAMBDA];
//    for(int i=0, t=0; i<MI+LAMBDA && t<LAMBDA; i++){
//        sample[i] = new Individual();
//        sample[i]->position = new double[dimension];
//        if(i < MI){
//            sample[i]->objective_function = progenitor[i]->objective_function;
////            cout<<"sample1>> "<<sample[i]->objective_function<<endl;
//            sample[i]->standard_deviation = progenitor[i]->standard_deviation;
//            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progenitor[i]->position[j]; }
//        }
//        if(i >=MI){
//            sample[i]->objective_function = progeny[t]->objective_function;
////            cout<<"sample2>> "<<sample[i]->objective_function<<endl;
//            sample[i]->standard_deviation = progeny[t]->standard_deviation;
//            for(int j=0; j<dimension; j++){ sample[i]->position[j] = progeny[t]->position[j]; }
//            t++;
//        }
//    }
//    QuickSort(sample, 0, (MI+LAMBDA)-1, dimension);
//    for(int i=0; i<MI; i++){
//        progenitor[i]->objective_function = sample[i]->objective_function;
////        cout<<"progenitor<< "<<progenitor[i]->objective_function<<endl;
//        progenitor[i]->standard_deviation = sample[i]->standard_deviation;
//        for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = sample[i]->position[j]; }
//        delete []sample[i]->position;
//        delete sample[i];
//    }
//    //cout<<progenitor[0]->objective_function<<endl;
//    delete []sample;
//}
//
//void Evolutionary_Strategy3(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){
//
//        if(delta > 0){
//        srand(seed);
//        criteria = 0;
//        Individual **progenitor = new Individual*[MI];
//        Individual **progeny = new Individual*[LAMBDA];
//        Individual *best_individual = new Individual();
//
//        int i;
//        for(i=0; i<LAMBDA; i++){ progeny[i] = new Individual(); progeny[i]->position = new double[dimension]; }
//        bool success = false;
//
//       double *lb = new double[dimension], *ub = new double[dimension];
//       Lower_Bounds(number_function, dimension, lb);
//       Upper_Bounds(number_function, dimension, ub);
//       functionEvaluations = 0;
//       for(i=0; i<MI; i++){
//            progenitor[i] = new Individual();
//            progenitor[i]->position = new double[dimension];
//            if(lb != NULL && ub != NULL){
//                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = (ub[i] - lb[i])*generate_ramdom() + lb[i]; }
//            }
//            else{ for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = generate_ramdom(); } }
//            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
//            functionEvaluations++;
//            progenitor[i]->standard_deviation = Normal_distribution(0, 1/(sqrt(dimension)));
//        }
//
//        best_individual->position = new double[dimension];
//        best_individual->objective_function = progenitor[0]->objective_function;
//        best_individual->standard_deviation = progenitor[0]->standard_deviation;
//        for(int i=0; i<dimension; i++){ best_individual->position[i] = progenitor[0]->position[i]; }
//        for(int i=1; i<MI; i++){
//            if(progenitor[i]->objective_function < best_individual->objective_function){
//                best_individual->standard_deviation = progenitor[i]->standard_deviation;
//                best_individual->objective_function = progenitor[i]->objective_function;
//                for(int j=0; j<dimension; j++){ best_individual->position[j] = progenitor[i]->position[j]; }
//            }
//        }
//
//        criteria = Number_Evaluations(number_function);
//        int es = 0, ps  = 0;
//        int q = 0;
//        while(functionEvaluations < criteria){
//            cout<<best_individual->objective_function<<"  ";
//            success = false;
//            q++;
//            for(i=0; i<MI; i++){
//                for(int t=0; t<LAMBDA && functionEvaluations<criteria; ){
//                    for(int j=0; j<LAMBDA/MI && functionEvaluations<criteria; j++, t++){
//                        for(int k=0; k<dimension; k++){
//                            progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->standard_deviation);
//                            if(lb != NULL && ub != NULL){
//                                if(progeny[t]->position[k] < lb[i]){ progeny[t]->position[k] = lb[i];}
//                                if(progeny[t]->position[k] > ub[i]){ progeny[t]->position[k] = ub[i];}
//                            }
//                        }
//                        progeny[t]->standard_deviation = progenitor[i]->standard_deviation;
//                        progeny[t]->objective_function = Compute_Function(progeny[t]->position, dimension, number_function);
//                        functionEvaluations++;
//                        if(progeny[t]->objective_function < progenitor[i]->objective_function){
//                            if(progeny[t]->objective_function < best_individual->objective_function){
//                                best_individual->objective_function = progeny[t]->objective_function;
//                                best_individual->standard_deviation = progeny[t]->standard_deviation;
//                                for(int w=0; w<dimension; w++){ best_individual->position[w] = progeny[t]->position[w]; }
//                                success = true;
//                            }
//                        }
//                    }
//                }
//                progenitor[i]->standard_deviation = progenitor[i]->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));
//            }
//            if(!success){
//                    es++;
//                    bool exit = false;
//                    if(functionEvaluations < criteria){
//                            if(Exploratory_Moves(delta, best_individual, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
//                            else{
//                                if(delta > MAX_DELTA){
//                                    delta = (0.5)*delta;
//                                }
//                                    exit = true;
//                            }
//                    }
//                    if(exit)ps++;
//            }
//            Selection(progenitor, progeny, dimension);
//        }
//
//        for(i=0; i<dimension; i++){ x[i] = best_individual->position[i]; }
////        cout<<Compute_Function(x, dimension, number_function)<<endl;
////        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
////        cout<<"AVALIACOES DE FUNCAO ---------------- "<<functionEvaluations<<endl;
////        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
////        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
////        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
////        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;
//
//        for(i=0; i<MI; i++){
//            delete []progenitor[i]->position;
//            delete []progeny[i]->position;
//            delete progenitor[i];
//            delete progeny[i];
//        }
//        delete []progenitor;
//        delete []progeny;
////        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
////        delete []pattern;
//        if(lb != NULL && ub != NULL){
//            delete []lb;
//            delete []ub;
//        }
//     }
//}
//
//
//void Evolutionary_Strategy2(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){
//
//    if(delta > 0){
//        functionEvaluations = 0;
//        srand(seed);
////        double **pattern = new double*[2*dimension];
//        int i;
//        bool success = false;
//        Individual *individuo = new Individual();
//        individuo->position = new double[dimension];
// //       individuo->standard_deviation = expected_mean/sqrt(dimension);
//        individuo->standard_deviation = Normal_distribution(0, 1/(sqrt(dimension)));
////        individuo->standard_deviation = generate_ramdom();
//
//       double *lb = new double[dimension], *ub = new double[dimension];
//       Lower_Bounds(number_function, dimension, lb);
//       Upper_Bounds(number_function, dimension, ub);
//
//
//        if(lb != NULL && ub != NULL){ for(i=0; i<dimension; i++){ individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i]; } }
//        else{ for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); } }
//        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
//        functionEvaluations++;
//
//        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
//        int t=0, functionEvaluations=0;
//
//        while(functionEvaluations < criteria){
//            cout<<individuo->objective_function<<"  ";
//            success=false;
//            double y[dimension];
//            for(i=0; i<dimension; i++){
//                y[i] = individuo->position[i] + Normal_distribution(0, individuo->standard_deviation);
//                if(lb != NULL && ub != NULL){
//                        if(y[i] < lb[i]){ y[i] = lb[i]; }
//                        if(y[i] > ub[i]){ y[i] = ub[i]; }
//                }
//            }
//            double aux = Compute_Function(y, dimension, number_function); functionEvaluations++;
//            if(aux < best_function){
//                individuo->objective_function = aux;
//                for(i=0; i<dimension; i++){ individuo->position[i] = y[i]; }
//                success = true;
//            }
//            //else{ individuo->standard_deviation = individuo->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension))); }
//            individuo->standard_deviation = individuo->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));
//
//            if(!success){
//                es++;
//                bool exit = false;
//                if(functionEvaluations < criteria){
//                        if(Exploratory_Moves(delta, individuo, dimension, number_function, lb, ub)){delta = 1.5*delta; exit = false; }
//                        else{
//                            if( delta > MAX_DELTA){ delta = (0.5)*delta; }
//                            exit = true;
//                        }
//                }
//                if(exit)ps++;
//            }
//            t = t+1;
//        }
//
//        for(int k=0; k<dimension; k++){ x[k] = individuo->position[k]; }
////        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
////        cout<<"AVALIACOES DA FUNCAO OBJETIVO ------- "<<functionEvaluations<<endl;
////        cout<<"NUMERO DE ITERACOES ----------------- "<<t<<endl;
////        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
////        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
////        cout<<"ITERACOES DE SUCESSO ---------------- "<<(t - es) + (es - ps)<<endl;
//
//
////        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
////        delete []pattern;
//        delete individuo;
//        if(lb != NULL && ub != NULL){
//            delete []lb;
//            delete []ub;
//        }
//    }
//}
//
//void Evolutionary_Strategy1(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){
//
//    if(delta > 0){
//        functionEvaluations = 0;
//        srand(seed);
////        double **pattern = new double*[2*dimension];
//        int i;
//        bool success = false;
//
//        Individual *individuo = new Individual();
//        individuo->position = new double[dimension];
//        individuo->standard_deviation = expected_mean/sqrt(dimension);
//
//        int *successful = new int[dimension*10];
//
//        //matriz de padrões
////        for(i = 0; i<2*dimension; i++){
////             pattern[i] = new double[dimension];
////            for(int j=0; j<dimension; j++){
////                if(i<dimension){
////                    if(j==i){pattern[i][j] = 1.0;}
////                    else{ pattern[i][j] = 0.0; }
////                }
////                else{
////                    if(i-j == dimension){ pattern[i][j] = -1.0; }
////                    else{ pattern[i][j] = 0.0; }
////                }
////            }
////        }
//
//       double *lb = new double[dimension], *ub = new double[dimension];
//       Lower_Bounds(number_function, dimension, lb);
//       Upper_Bounds(number_function, dimension, ub);
//
//        for(i=0; i<dimension*10; i++){ successful[i] = 0; }
//        //indivíduo inicial
//        if(lb != NULL && ub!=NULL){
//            for(i=0; i<dimension; i++){
//                individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i];
//            }
//        }
//        else{ for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); } }
//
//        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
//        functionEvaluations++;
//
//        int es = 0, ps  = 0, criteria = Number_Evaluations(number_function);
//        int t=0;
//
//        while(functionEvaluations < criteria){
//            cout<<individuo->objective_function<<"  ";
//            success=false;
//            //regra de 1/5 de sucessos
//            if(t%dimension == 0 && t>=dimension*10){
//                double sum=0, ps;
//                for(i=0; i<dimension*10; i++){sum += successful[i]; }
//                ps = sum/10*dimension;
//                if(ps > 1/5){ individuo->standard_deviation = individuo->standard_deviation/0.85;}
//                else if(ps < 1/5){ individuo->standard_deviation = individuo->standard_deviation*0.85; }
//            }
//            double y[dimension];
//            for(i=0; i<dimension; i++){
//                y[i] = x[i] + Normal_distribution(0, individuo->standard_deviation);
//                if(lb != NULL && ub != NULL){
//                    if(y[i] < lb[i]){ y[i] = lb[i]; }
//                    if(y[i] > ub[i]){ y[i] = ub[i]; }
//                }
//            }
//            double aux = Compute_Function(y, dimension, number_function); functionEvaluations++;
//            if(aux < individuo->objective_function){
//                individuo->objective_function = aux;
//                for(i=0; i<dimension; i++){ individuo->position[i] = y[i]; }
//                successful[(t+1)%(dimension*10)] = 1;
//                success = true;
//            }
//            else{ successful[(t+1)%(dimension*10)] = 0;}
//
//            if(!success){
//                es++;
//                bool exit = false;
//                if(functionEvaluations < criteria){
//                        if(Exploratory_Moves(delta, individuo, dimension, number_function, lb, ub)){ delta = 1.5*delta; exit = false;}
//                        else{
//                            if(delta > MAX_DELTA){ delta = (0.5)*delta; }
//                                exit = true;
//                        }
//                }
//                if(exit)ps++;
//            }
//            t = t+1;
//        }
////        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
////        cout<<"AVALIACOES DA FUNCAO OBJETIVO ------- "<<functionEvaluations<<endl;
////        cout<<"NUMERO DE ITERACOES ----------------- "<<t<<endl;
////        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
////        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
////        cout<<"ITERACOES DE SUCESSO ---------------- "<<(t - es) + (es - ps)<<endl;
//
//        for(int k=0; k<dimension; k++){ x[k] = individuo->position[k]; }
//        delete []successful;
////        for(i=0; i<2*dimension; i++){ delete []pattern[i]; }
////        delete []pattern;
//        if(lb != NULL && ub != NULL){
//            delete []lb;
//            delete []ub;
//        }
//    }
//}


bool VerificadorSolucao(double *x, int dimension, int number_function){
    if(x != NULL){
        double *lb = new double[dimension], *ub = new double[dimension];
        Lower_Bounds(number_function, dimension, lb);
        Upper_Bounds(number_function, dimension, ub);
        for(int i=0; i<dimension; i++){
            if(x[i] < lb[i]){ cout<<"Solucao nao-factivel: "<<x[i]<<";"; return false; }
            if(x[i] > ub[i]){ cout<<"Solucao nao-factivel: "<<x[i]<<";"; return false; }
        }
        delete []lb;
        delete []ub;
        return true;
    }
    return false;
}

