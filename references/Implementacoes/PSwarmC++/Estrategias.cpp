#include <iostream>
#include "Estrategias.h"
#include "Solution.h"
#include "Avaliation_Function.h"
#include "Sort.h"
#include "Selection.h"
#include<cmath>
#include <random>
#include <iomanip>

#define NUMPARTICLES 42
#define MAX_DELTA 0.00001
//#define INF 3.40282347E+38F
#define INF 1E+21

using namespace std;
//TO DO: to verify the initial velocity in the PSwarm => in PSwarm, the velocity is initialized with zero.
int functionEval = 0;
int iterations = 0;
int maxEval = 0;
int maxIter = 0;
int success_direction = -1;
double delta;

double generate_ramdom() {
    return ((rand())/(RAND_MAX+1.0));
}

void PatternSearch(double *sample, double *function, int dimension, double *lb, double *ub, int numFunction){
    if(sample){
        int directions = 2*dimension, best;
        double **points = new double*[directions];
        double functions = INF;
        double aux = INF;
        for(int i=0; i<directions; i++){
            points[i] = new double[dimension];
        }

        bool fail;

        for(int i=0; i<directions; i++){
             for(int j=0; j<dimension; j++){
                if(i<dimension){
                    if(i == j){
                        points[i][j] = sample[j] + delta;
                    }
                    else{
                        points[i][j] = sample[j];
                    }
                }
                else{
                    if((i - j) == dimension){
                        points[i][j] = sample[j] - delta;
                    }
                    else{
                        points[i][j] = sample[j];
                    }
                }
            }
        }

        for(int i=0; i<directions; i++){
            fail = false;
            for(int j=0; j<dimension; j++){
                if(points[i][j] < lb[j] || points[i][j] > ub[j]){
                    fail = true;
                    break;
                }
            }
            if(!fail){
                functions = Compute_Function(points[i], dimension, numFunction); functionEval++;
                if(functions < aux){
                    best = i;
                    aux=functions;
                }
            }
        }


        if(*function > aux){
            *function = aux;
            for(int i=0; i<dimension; i++){
                sample[i] = points[best][i];
            }
            if(success_direction == best){
                delta = 2*delta;
            }
            else{
                success_direction = best;
            }
        }
        else{
            success_direction = -1;
            delta = 0.5*delta;
        }

        for(int i=0; i<directions; i++){
            delete []points[i];
        }
        delete []points;

    }
    else{
        cout<<"Ponto nulo. Com amor, Pattern Search"<<endl;
    }
}

void PSO(int dimension, int seed, double delta_initial, int number_function, double* x){

        if(delta_initial > 0){

            srand(seed);
            functionEval = 0;
            iterations = 0;
            delta  = delta_initial;

            double normtmp = 0.0, normtmp2 = 0.0;
            double maxFactorVelocity = 0.5, initialDeltaFactor = 5.0, maxVNorm = INF;

            double initialWeight = 0.9, finalWeight = 0.4;

            double cognition_parameter = 0.5;
            double social_parameter = 0.5;

            double *maxVelocity = new double[dimension];
            double actives = NUMPARTICLES;
            double *active = new double[NUMPARTICLES];
            double *velocity_global = new double[dimension];
            double weight;
            double *alphaMax = new double[dimension];
            int a0=0;

            double *position_global = new double[dimension];
            for(int i=0; i<dimension; i++){
                position_global[i] = -1;
                velocity_global[i] = -1;
            }

            Particle **population = new Particle*[NUMPARTICLES];
            double best= INF;
            double *lb = new double[dimension], *ub=new double[dimension];
            Lower_Bounds(number_function, dimension, lb);
            Upper_Bounds(number_function, dimension, ub);

            if(delta_initial >= INF){ /* User didn't provide delta */
                double mindelta=INF;
                for(int j=0;j<dimension;j++){
                    if(lb[j] > -INF && ub[j] < INF){
                        if(mindelta > (ub[j]-lb[j])){
                            mindelta=(ub[j]-lb[j]);
                        }
                        maxVelocity[j]=(ub[j]-lb[j])*maxFactorVelocity;
                    }
                    else {
                        maxVelocity[j]=INF;
                    }
                }
                if(mindelta>= INF || mindelta<2*sqrt(MAX_DELTA)){
                    delta=2*sqrt(sqrt(MAX_DELTA));
                }
                else {
                    delta=mindelta/initialDeltaFactor;
                }
            }
            delta_initial = delta;

            for(int i=0; i<NUMPARTICLES; i++){
                active[i] = 1;
                population[i] = new Particle();
                population[i]->position = new double[dimension];
                population[i]->velocity = new double[dimension];
                population[i]->best_position = new double[dimension];
                for(int j=0; j<dimension; j++){

                    if(lb != NULL && ub != NULL){
                        population[i]->position[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
                        population[i]->velocity[j] = 0.0;
                    }
                    else{
                        population[i]->position[j] = generate_ramdom();
                        population[i]->velocity[j] = 0.0;
                    }
                }

                population[i]->best_fitness = INF;
            }

//            maxEval = Number_Evaluations(number_function);
            int count =0;
            maxEval = 2000;
            maxIter = 2000;
            bool success;
            while(functionEval < maxEval && iterations < maxIter){

                success = false;
                if(maxVNorm<MAX_DELTA && delta<MAX_DELTA){cout<<"Stopping by maxVnorm and delta"<<endl; break;}
                if(actives <=1 && delta<MAX_DELTA){cout<<"Stopping by actives and delta"<<endl; break;}
                iterations++;

                for(int i=0; i<NUMPARTICLES; i++){
                    if(active[i]){
                      population[i]->fitness = Compute_Function(population[i]->position, dimension, number_function);
                      functionEval++;
                    }
                }

                for(int i=0; i<NUMPARTICLES; i++){
                    if(active[i]){
                           if(population[i]->fitness < population[i]->best_fitness){
                            population[i]->best_fitness = population[i]->fitness;
                            for(int j=0; j<dimension; j++){
                                population[i]->best_position[j] = population[i]->position[j];
                            }
                            if(population[i]->best_fitness < best){
                                count++;
                                for(int j=0; j<dimension; j++){
                                    position_global[j] = population[i]->best_position[j];
                                    velocity_global[j] = population[i]->velocity[j];
                                }
                                success=true; success_direction = -1;
                                best=population[i]->best_fitness;
                                a0 = i;
                            }
                        }
                    }
                }

                if(!success){
                    if(delta >= MAX_DELTA){
                        PatternSearch(position_global, &best, dimension, lb, ub, number_function);
                        population[a0]->best_fitness = best;
                        for(int j=0; j<dimension; j++){
                            population[a0]->best_position[j] = position_global[j];
                        }
                    }
                }
                else{
                   if(delta < delta_initial){
                        delta*=2;
                    }
                    if(delta < MAX_DELTA){
                        delta = 2*MAX_DELTA;
                    }
                }

                weight = initialWeight - (initialWeight - finalWeight)*((double)iterations)/((double)maxIter);
                for(int i=0; i<NUMPARTICLES; i++){
                    if(active[i]){
                        for(int j=0; j<dimension; j++){
                            population[i]->velocity[j] = weight*population[i]->velocity[j] +
                                                        cognition_parameter*generate_ramdom()*(population[i]->best_position[j] - population[i]->position[j]) +
                                                        social_parameter*generate_ramdom()*(position_global[j] - population[i]->position[j]);

                            if(population[i]->velocity[j] > maxVelocity[j]){
                                population[i]->velocity[j] = maxVelocity[j];
                            }
                            if(population[i]->velocity[j] < -maxVelocity[j]){
                                population[i]->velocity[j] = -maxVelocity[j];
                            }

                            alphaMax[j] = 1;
                        }

                        for(int j=0; j<dimension; j++){
                            alphaMax[j] = 1;
                            double a1 = (lb[j] - population[i]->position[j])/population[i]->velocity[j];
                            double a2 = (ub[j] - population[i]->position[j])/population[i]->velocity[j];
                            if(population[i]->velocity[j] < 0.0){
                                if(alphaMax[j] > a1){
                                    alphaMax[j] = a1;
                                }
                            }
                            if(population[i]->velocity[j] > 0.0){
                                if(alphaMax[j] > a2 ){
                                    alphaMax[j] = a2;
                                }
                            }
                            if(alphaMax[j] < 0.0){
                                cout<<"isso não deveria acontecer"<<endl;
                            }
                        }

                        for(int j=0; j<dimension; j++){
                            population[i]->position[j] = population[i]->position[j] + alphaMax[j]*population[i]->velocity[j];

                            if(population[i]->position[j] > ub[j]){
                                population[i]->position[j] = ub[j];
                            }
                            if(population[i]->position[j] < lb[j]){
                                population[i]->position[j] = lb[j];
                            }

                        }
                    }
                }

                normtmp = 0.0;
                for(int j=0; j<dimension; j++){
                    normtmp += velocity_global[j]*velocity_global[j];
                }
                maxVNorm = sqrt(normtmp);

                actives=0;
                for(int i=0; i<NUMPARTICLES; i++){
                    if(active[i] && i!=a0){
                        normtmp=0.0; normtmp2=0.0;
                        for(int j=0; j<dimension; j++){
                            normtmp += (population[i]->best_position[j] - position_global[j])*(population[i]->best_position[j] - position_global[j]);
                            normtmp2 += population[i]->velocity[j]*population[i]->velocity[j];
                        }
                        normtmp = sqrt(normtmp); normtmp2 = sqrt(normtmp2);

                        if(normtmp < delta_initial && normtmp2 < delta_initial){
                            active[i]--;
                        }
                        else{
                            if(maxVNorm < normtmp2){
                                maxVNorm = normtmp2;
                            }
                        }

                    }
                    if(active[i]){
                        actives++;
                    }
                }

            }

            cout<<"iteracoes: "<<iterations<<endl;
            cout<<"avaliacoes: "<<functionEval<<endl;
            cout<<"resultado final: "<<setprecision(10)<<best<<endl;
//            cout<<setprecision(10)<<";"<<best;

            delete []maxVelocity;
            delete []alphaMax;
            delete []position_global;
            delete []active;
            delete []velocity_global;
            for(int i=0; i<NUMPARTICLES; i++){
                delete []population[i]->best_position;
                delete []population[i]->position;
                delete []population[i]->velocity;
                delete population[i];
            }
            delete []population;
            delete []lb;
            delete []ub;
#if SYS_RANDOM == 1
            delete rand_seed;
#endif
        }
}

bool VerificadorSolucao(double *x, int dimension, int number_function){
    if(x != NULL){
        double *lb = new double[dimension], *ub = new double[dimension];
        Lower_Bounds(number_function, dimension, lb);
        Upper_Bounds(number_function, dimension, ub);
        if(lb && ub){
            for(int i=0; i<dimension; i++){
                if(x[i] < lb[i]){ cout<<"Solucao nao-factivel: "<<x[i]<<";"; return false; }
                if(x[i] > ub[i]){ cout<<"Solucao nao-factivel: "<<x[i]<<";"; return false; }
            }
        }
        delete []lb;
        delete []ub;
        return true;
    }
    return false;
}
