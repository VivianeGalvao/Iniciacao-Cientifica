#include <iostream>
#include<cmath>
#include <random>
#include "Estrategias.h"
#include "Solution.h"
#include "Avaliation_Function.h"
#include "Sort.h"
#include "Selection.h"


#define NUMPARTICLES 50
#define tam_avaliations 1000
#define MAX_DELTA 0.00001
#define INF 3.40282347E+38F
#define MI 4
#define LAMBDA 3*MI

using namespace std;

double *Estrategia::sampling[2];
int Estrategia::iterations[2];

int mark;
int functionEvaluations;
int best_function;
int criteria;

double generate_ramdom() {
    return ((rand())/(RAND_MAX+1.0));
}

bool Estrategia::Exploratory_Moves(double delta, Particle *sample, int size, int number_function, double* lb, double* ub){
    bool exit = false;
    int i, t;
    double *x_aux = new double[size];
    double *x_best = new double[size];
    double fx_best=sample->fitness, fx_aux=0.0;

    for(i = 0; i<size; i++){x_aux[i] = sample->position[i]; x_best[i] = sample->position[i];}

    for(t=0, i=mark; t<size; t++, i++){
        if(i == size)i=0;
        x_aux[i] = sample->position[i] + delta;

        if(lb != NULL && ub != NULL){
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    x_best[i] = x_aux[i];
                    fx_best = fx_aux;
                    i++;
                    mark = i;
                    break;
                }
		else{ x_aux[i] = sample->position[i]; }
            }
            x_aux[i] = sample->position[i] - delta;
            if(x_aux[i] >= lb[i] && x_aux[i] <= ub[i]){
                if(functionEvaluations > criteria){return false;}
                fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
                if(fx_aux < fx_best){
                    x_best[i] = x_aux[i];
                    fx_best = fx_aux;
                    mark = i;
                    i++;
                    break;
                }
		else{ x_aux[i] = sample->position[i]; }
            }
        }

        else{
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function);functionEvaluations++;
            if(fx_best > fx_aux){
                x_best[i] = x_aux[i];
                fx_best = fx_aux;
                mark = i;
                i++;
                break;
            }
	    else{ x_aux[i] = sample->position[i]; }

            x_aux[i] = sample->position[i] - delta;
            if(functionEvaluations > criteria){return false;}
            fx_aux = Compute_Function(x_aux, size, number_function); functionEvaluations++;
            if(fx_aux < fx_best){
                x_best[i] = x_aux[i];
                fx_best = fx_aux;
                mark = i;
                i++;
                break;
            }
	    else{ x_aux[i] = sample->position[i]; }
        }
    }

    if (fx_best < sample->fitness) {
        exit = true;
        sample->fitness = fx_best;
        for(i = 0; i<size; i++){sample->position[i] = x_best[i];}
    }

    delete []x_aux;
    delete []x_best;
    return exit;
}

void Estrategia::PSOBL(int dimension, int seed, double delta_initial, int number_function, double* position_global){
    mark = 0;
    if(delta_initial > 0){
        double bests[tam_avaliations];
        int amount = 0;
        functionEvaluations = 0;
        int number_particles = NUMPARTICLES;
        int ps=0, pso=0;
        double delta = delta_initial;

        int i, j, NUMFUNC = number_function;
        srand(seed);

        Particle **population = new Particle*[NUMPARTICLES];
        Particle *best_particle = new Particle();
        double *lb = new double[dimension], *ub = new double[dimension] ;
        Lower_Bounds(NUMFUNC, dimension, lb);
        Upper_Bounds(NUMFUNC, dimension, ub);

        if(delta >= INF){
            double mindelta = INF;
            if(lb && ub){
                for(i = 0; i<dimension; i++){
                    if(mindelta > (ub[i] - lb[i])){ mindelta = ub[i] - lb[i]; }
                }
            }
            if(mindelta >=INF || mindelta <= MAX_DELTA){ delta = 2*sqrt(sqrt(MAX_DELTA)); }
            else{ delta = mindelta/5;}
        }


         //velocity parameters
        double inertia_factor = 0.9;
        double cognition_parameter = 0.5;
        double social_parameter = 0.5;



        //initialize a population of particles with random positions and velocities
        functionEvaluations = 0;
        for(i = 0; i<number_particles; i++){
            population[i] = new Particle();
            population[i]->position = new double[dimension];
            population[i]->velocity = new double[dimension];
            population[i]->best_position = new double[dimension];
            //velocity parameters
            for(j=0; j<dimension; j++){

                if(lb != NULL && ub != NULL){
                    population[i]->position[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
                    //population[i]->velocity[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
                    population[i]->velocity[j] = 0.0;
                }
                else{
                    population[i]->position[j] = generate_ramdom();
                    population[i]->velocity[j] = 0.0;
                }
                population[i]->best_position[j] = population[i]->position[j];
                //velocity paramenters
            }
            population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC);functionEvaluations++;
            population[i]->best_fitness = population[i]->fitness;
        }
        //population intialized


        best_particle->fitness = population[0]->fitness;
        best_particle->position = new double[dimension];
        for(j=0; j<dimension; j++){ best_particle->position[j] = population[0]->position[j]; }
        for(i=1; i<number_particles; i++){
            if(population[i]->fitness < best_particle->fitness){
                best_particle->fitness = population[i]->fitness;
                for(j=0; j<dimension; j++){ best_particle->position[j] = population[i]->position[j];}
            }
        }

        int iteracoes = 0, maxEval = Number_Evaluations(number_function);
        criteria = maxEval;
         while(functionEvaluations < maxEval){

             if(iteracoes%2 == 0){
                bests[amount] = best_particle->fitness;
                amount++;
             }

            bool successful = false, test=false;
            for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
                for(j=0; j<dimension; j++){
                    population[i]->velocity[j] = (inertia_factor*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
                                                population[i]->position[j])) + (social_parameter*generate_ramdom()*(position_global[j] - population[i]->position[j]));


                    population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
                    if(lb != NULL && ub != NULL){
                        if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
                        if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
                    }
                }
                population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC); functionEvaluations++;
                if(population[i]->fitness < population[i]->best_fitness){
                    population[i]->best_fitness = population[i]->fitness;
                    for(j=0; j<dimension; j++){
                        population[i]->best_position[j] = population[i]->position[j];
                    }
                    if(population[i]->fitness < best_particle->fitness){
                        best_particle->fitness = population[i]->fitness;
                        for(j=0; j<dimension; j++){
                            best_particle->position[j] = population[i]->position[j];
                        }
                        successful = true;
                        delta = 2*delta;
                    }
                }
            }

            if(!successful){
                pso++;
                if( functionEvaluations<maxEval ){
                    if(Exploratory_Moves(delta, best_particle, dimension, NUMFUNC, lb, ub)){ delta = 2*delta; test = false;}
                    else{
                        if(delta > MAX_DELTA){ delta = (0.5)*delta; }
                        test=true;
                    }
                }
                if(test){ ps++; }
            }
            iteracoes++;
//            cout<<mark<<endl;
            if(mark == dimension)mark=0;
        }


        sampling[0] = new double[amount];
        for(int i=0; i<amount; i++){
            sampling[0][i] = bests[i];
        }
        iterations[0] = amount;

        for(i=0; i<dimension; i++){ position_global[i] = best_particle->position[i]; }
        delete []best_particle->position;
        delete best_particle;
        for(i=0; i<number_particles; i++){
            delete []population[i]->position;
            delete []population[i]->best_position;
            delete []population[i]->velocity;
            delete population[i];
        }
        delete []population;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
    }
    else{ cout<<"Delta informado menor que zero"; }

}


void Estrategia::PSO(int dimension, int seed, int number_function, double* position_global){

    double bests[tam_avaliations];
    int amount = 0;
    functionEvaluations = 0;
    int number_particles = NUMPARTICLES;

    int i, j, NUMFUNC = number_function;
    srand(seed);

    Particle **population = new Particle*[NUMPARTICLES];
    Particle *best_particle = new Particle();
    double *lb = new double[dimension], *ub = new double[dimension] ;
    Lower_Bounds(NUMFUNC, dimension, lb);
    Upper_Bounds(NUMFUNC, dimension, ub);

     //velocity parameters
    double inertia_factor = 0.9;
    double cognition_parameter = 0.5;
    double social_parameter = 0.5;



    //initialize a population of particles with random positions and velocities
    functionEvaluations = 0;
    for(i = 0; i<number_particles; i++){
        population[i] = new Particle();
        population[i]->position = new double[dimension];
        population[i]->velocity = new double[dimension];
        population[i]->best_position = new double[dimension];
        //velocity parameters
        for(j=0; j<dimension; j++){

            if(lb != NULL && ub != NULL){
                population[i]->position[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
                //population[i]->velocity[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
                population[i]->velocity[j] = 0.0;
            }
            else{
                population[i]->position[j] = generate_ramdom();
                population[i]->velocity[j] = 0.0;
            }
            population[i]->best_position[j] = population[i]->position[j];
            //velocity paramenters
        }
        population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC);functionEvaluations++;
        population[i]->best_fitness = population[i]->fitness;
    }
    //population intialized


    best_particle->fitness = population[0]->fitness;
    best_particle->position = new double[dimension];
    for(j=0; j<dimension; j++){ best_particle->position[j] = population[0]->position[j]; }
    for(i=1; i<number_particles; i++){
        if(population[i]->fitness < best_particle->fitness){
            best_particle->fitness = population[i]->fitness;
            for(j=0; j<dimension; j++){ best_particle->position[j] = population[i]->position[j];}
        }
    }

    int iteracoes = 0, maxEval = Number_Evaluations(number_function);
    criteria = maxEval;
     while(functionEvaluations < maxEval){
         if(iteracoes%2 == 0){
            bests[amount] = best_particle->fitness;
            amount++;
         }

//            cout<<fitness_global<<"  ";
        for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
            for(j=0; j<dimension; j++){
                population[i]->velocity[j] = (inertia_factor*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
                                            population[i]->position[j])) + (social_parameter*generate_ramdom()*(position_global[j] - population[i]->position[j]));


                population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
                if(lb != NULL && ub != NULL){
                    if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
                    if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
                }
            }
            population[i]->fitness = Compute_Function(population[i]->position, dimension, NUMFUNC); functionEvaluations++;
            if(population[i]->fitness < population[i]->best_fitness){
                population[i]->best_fitness = population[i]->fitness;
                for(j=0; j<dimension; j++){
                    population[i]->best_position[j] = population[i]->position[j];
                }
                if(population[i]->fitness < best_particle->fitness){
                    best_particle->fitness = population[i]->fitness;
                    for(j=0; j<dimension; j++){
                        best_particle->position[j] = population[i]->position[j];
                    }
                }
            }
        }
        iteracoes++;
    }

    sampling[1] = new double[amount];
    for(int i=0; i<amount; i++){
        sampling[1][i] = bests[i];
    }
    iterations[1] = amount;

    for(i=0; i<dimension; i++){ position_global[i] = best_particle->position[i]; }
    delete []best_particle->position;
    delete best_particle;
    for(i=0; i<number_particles; i++){
        delete []population[i]->position;
        delete []population[i]->best_position;
        delete []population[i]->velocity;
        delete population[i];
    }
    delete []population;
    if(lb != NULL && ub != NULL){
        delete []lb;
        delete []ub;
    }
}

