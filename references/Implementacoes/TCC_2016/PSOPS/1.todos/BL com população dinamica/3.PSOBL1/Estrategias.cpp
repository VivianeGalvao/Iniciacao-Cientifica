#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "Estrategias.h"
#include "Solution.h"

#define NUMPARTICLES 42
#define MAX_DELTA 0.00001
//#define INF 3.40282347E+38F
#define INF 1E+21

using namespace std;
//TO DO: to verify the initial velocity in the PSwarm => in PSwarm, the velocity is initialized with zero.
int functionEvaluations = 0;
int maxEval = 0;
// int success_direction= -1;
int mark = 0;
double delta;

double generate_ramdom() {
    return ((rand())/(RAND_MAX+1.0));
}

void Exploratory_Moves(double (*objfun)(double *), Particle *sample, int size, double* lb, double* ub){
        if(sample){
        int directions = 2*size;
        double **points = new double*[directions];
        double aux;
        for(int i=0; i<directions; i++){
            points[i] = new double[size];
        }

        bool fail;
        bool exit=false;

        for(int i=0; i<directions; i++){
             for(int j=0; j<size; j++){
                if(i<size){
                    if(i == j){
                        points[i][j] = sample->position[j] + delta;
                    }
                    else{
                        points[i][j] = sample->position[j];
                    }
                }
                else{
                    if((i - j) == size){
                        points[i][j] = sample->position[j] - delta;
                    }
                    else{
                        points[i][j] = sample->position[j];
                    }
                }
            }
        }

        for(int t=0, i=mark; t<directions; t++, i++){
            if(i==2*size)i=0;
            fail = false;
            for(int j=0; j<size; j++){
                if(lb && ub){
                    if(points[i][j] < lb[j] || points[i][j] > ub[j]){
                        fail = true;
                        break;
                    }
                }
            }
            if(!fail){
                aux = objfun(points[i]); functionEvaluations++;
                if(sample->fitness > aux){
                    sample->fitness = aux;
                    for(int j=0; j<size; j++){
                        sample->position[j] = points[i][j];
                    }
//                     if(success_direction == i){
                        delta = 2*delta;
//                     }
//                     else{
//                         success_direction = i;
//                     }
                    exit = true;
                    mark = i+1;
                }
//                if(functionEvaluations%10==0){
//                        cout<<";"<<setprecision(10)<<sample->fitness;
//                    }
            }
            if(exit)break;
        }

        if(!exit){
//             success_direction = -1;
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


double PSO(double (*objfun)(double*), int dimension, int seed, double delta_inicial, double *lb, double *ub){
    if(delta_inicial > 0){
        functionEvaluations = 0;
        int number_particles = NUMPARTICLES;
	int ps=0;

        int i, j;
        srand(seed);

        Particle **population = new Particle*[NUMPARTICLES], *best_particle = new Particle();

	int active[number_particles];
        int actives = 0;
        int sucessos[number_particles];
       // int minparticles;
	
        double limit;
	if(delta_inicial >= INF){
	  double mindelta = INF;
	  if(lb && ub){
	      for(i = 0; i<dimension; i++){
		  if(mindelta > (ub[i] - lb[i])){ mindelta = ub[i] - lb[i]; }
	      }
	  }
	  if(mindelta >=INF || mindelta <= MAX_DELTA){ limit = 2*sqrt(sqrt(MAX_DELTA)); }
	  else{ 
	    delta = mindelta/5;
	    limit = delta;
	  }
	}
	else{
	  delta = delta_inicial;
	  limit = delta_inicial;
	}
	  
	
	//minparticles = number_particles;

         //velocity parameters
        double initialWeight = 0.9, finalWeight = 0.4;
        double weight;
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
            population[i]->fitness = objfun(population[i]->position);
            functionEvaluations++;
            population[i]->best_fitness = population[i]->fitness;
	    
	    int flag = rand()%2;
// 	    if(i < minparticles){
	    if(flag){
                active[i] = 1;
                actives++;
            }
            else{
                active[i] = 0;
            }

            sucessos[i] = 0;
        }
        //population intialized


       int gbest = 0;
        best_particle->fitness = population[0]->fitness;
        best_particle->position = new double[dimension];
        for(j=0; j<dimension; j++){ best_particle->position[j] = population[0]->position[j]; }
        for(i=1; i<number_particles; i++){
            if(population[i]->fitness < best_particle->fitness){
                best_particle->fitness = population[i]->fitness;
                for(j=0; j<dimension; j++){ best_particle->position[j] = population[i]->position[j];}
                gbest = i;
            }
        }
        sucessos[gbest]++;

        int iteracoes = 0, maxEval = 2000;
         while(functionEvaluations < maxEval){
//            cout<<fitness_global<<"  ";
            bool successful = false;
            weight = initialWeight - (initialWeight - finalWeight)*((double)functionEvaluations)/((double)maxEval);
	    
            for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
		double aux = 0;
// 		if(active[i] && i!=gbest){
		if(active[i]){  
		  for(j=0; j<dimension; j++){
		  
                    population[i]->velocity[j] = (weight*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
                                                population[i]->position[j])) + (social_parameter*generate_ramdom()*(best_particle->position[j] - population[i]->position[j]));


                    population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
                    if(lb != NULL && ub != NULL){
                        if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
                        if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
                    }
                    aux += (population[i]->position[j] - best_particle->position[j])*(population[i]->position[j] - best_particle->position[j]);
		  }
		  population[i]->fitness = objfun(population[i]->position);
		  functionEvaluations++;
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
			 gbest = i;
                        sucessos[i]++;
                    }
                }
	      }
	      
	      double dist = sqrt(aux);
	      if(dist <= limit){
		  if(actives > 2){
		      active[i] = 0;
		      actives--;
  // 			cout<<"ativos: "<<actives<<endl;
		  }
	      }
	      else{
		  if(actives < number_particles){
		      active[i] = 1;
		      actives++;
  // 			cout<<"ativos: "<<actives<<endl;
		  }
	      }
            }
            
            if(!successful){
		  ps++;
		  Exploratory_Moves(objfun, best_particle, dimension, lb, ub);
		  if(best_particle->fitness < population[gbest]->best_fitness){
                    sucessos[gbest]++;
		  }
	    }	    
                
	    for(i = 0; i<number_particles; i++){
		if(i != gbest){
		  if(sucessos[i] > ps){
		      if(actives > 2){
			  active[i] = 0;
			  actives--;
		      }
		  }
		  else{
		      if(actives < number_particles){
			  active[i] = 1;
			  actives++;
		      }
		  }
	      }
	    }
        }

        double valor_final = best_particle->fitness;
        delete []best_particle->position;
        delete best_particle;
        for(i=0; i<number_particles; i++){
            delete []population[i]->position;
            delete []population[i]->best_position;
            delete []population[i]->velocity;
            delete population[i];
        }
        delete []population;

        return valor_final;
    }
    else{ cout<<"Delta menor que zero"; return INF;}
}
