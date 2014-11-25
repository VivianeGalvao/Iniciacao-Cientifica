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

void PSwarm(int dimension, int seed, double delta_initial, int number_function, double* position_global){

    if(delta_initial > 0){
        functionEvaluations = 0;
        int number_particles = NUMPARTICLES;
        int ps=0, pso=0;
        double delta = delta_initial;

        int i, j, NUMFUNC = number_function;
        srand(seed);

        Particle **population = new Particle*[NUMPARTICLES];
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


        double fitness_global = population[0]->fitness;
        for(j=0; j<dimension; j++){ position_global[j] = population[0]->position[j]; }
        for(i=1; i<number_particles; i++){
            if(population[i]->fitness < fitness_global){
                fitness_global = population[i]->fitness;
                for(j=0; j<dimension; j++){ position_global[j] = population[i]->position[j];}
            }
        }

        int iteracoes = 0, maxEval = Number_Evaluations(number_function);
        criteria = maxEval;
         while(functionEvaluations < maxEval){
            cout<<fitness_global<<"  ";
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
                    if(population[i]->fitness < fitness_global){
                        fitness_global = population[i]->fitness;
                        for(j=0; j<dimension; j++){
                            position_global[j] = population[i]->position[j];
                        }
                        successful = true;
                    }
                }
            }

            if(!successful){
                pso++;
                if( functionEvaluations<maxEval ){
                    best_function = fitness_global;
                    if(Exploratory_Moves(delta, position_global, dimension, NUMFUNC, lb, ub)){ delta = 1.5*delta; test = false; fitness_global = best_function;}
                    else{
                        if(delta > MAX_DELTA){ delta = (0.5)*delta; }
                        test=true;
                    }
                }
                if(test){ ps++; }
            }
            iteracoes++;
        }

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

//        for(int i=0; i<dimension*2; i++){ delete []pattern[i]; }
//        delete []pattern;

//        cout<<endl;
//        cout<<"NUMERO FUNCAO ------------------ "<<NUMFUNC<<endl;
//        cout<<"AVALIACOES DE FUNCAO ----------- "<<functionEvaluations<<endl;
//        cout<<"ITERAÇOES TOTAIS --------------- "<<iteracoes<<endl;
//        cout<<"ITERACOES DE SUCESSO ----------- "<<(iteracoes - pso) + (pso - ps)<<endl;
//        cout<<"ITERAÇÕES SEM SUCESSO - PSO ---- "<<pso<<endl;
//        cout<<"ITERAÇÕES SEM SUCESSO - PS ----- "<<ps<<endl;
//       // cout<<"DELTA FINAL -------------------- "<<delta<<endl;
//        cout<<endl;
    }

}
