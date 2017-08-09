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
double delta;

double generate_ramdom() {
     return ((rand())/(RAND_MAX+1.0));
}

double PSO(double (*objfun)(double*), int dimension, int seed, double *lb, double *ub, double iW, double fW, double cogP, double socP){
        
  functionEvaluations = 0;
  int number_particles = NUMPARTICLES;

  int i, j;
  srand(seed);

  Particle **population = new Particle*[NUMPARTICLES], *best_particle = new Particle();

  double limit;
  double mindelta = INF;
  if(lb && ub){
      for(i = 0; i<dimension; i++){
	  if(mindelta > (ub[i] - lb[i])){ mindelta = ub[i] - lb[i]; }
      }
  }
  if(mindelta >=INF || mindelta <= MAX_DELTA){ limit = 2*sqrt(sqrt(MAX_DELTA)); }
  else{ limit = mindelta/5;}

    //velocity parameters
  double initialWeight = iW, finalWeight = fW;
  double weight;
  double cognition_parameter = cogP;
  double social_parameter = cogP;

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
  }
  //population intialized


  int gbest = 0;
  best_particle->fitness = population[0]->fitness;
  best_particle->position = new double[dimension];
  for(j=0; j<dimension; j++){ best_particle->position[j] = population[0]->position[j]; }
  for(i=1; i<number_particles; i++){      
      if(population[i]->fitness < best_particle->fitness){	  
	  gbest = i;
      }
  }
  best_particle->fitness = population[gbest]->fitness;
  for(j=0; j<dimension; j++){ best_particle->position[j] = population[gbest]->position[j];}
  
  int iteracoes = 0, maxEval = 2000;
  while(functionEvaluations < maxEval){
      bool successful = false;
      weight = initialWeight - (initialWeight - finalWeight)*((double)functionEvaluations)/((double)maxEval);

      for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
	  for(j=0; j<dimension; j++){
	    
	      population[i]->velocity[j] = (weight*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
					  population[i]->position[j])) + (social_parameter*generate_ramdom()*(best_particle->position[j] - population[i]->position[j]));


	      population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
	      if(lb != NULL && ub != NULL){
		  if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
		  if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
	      }
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


// double PSO(double (*objfun)(double*), int dimension, int seed, double *lb, double *ub){
// 
//         functionEvaluations = 0;
//         int number_particles = NUMPARTICLES;
// 
//         int i, j;
//         srand(seed);
// 
//         Particle **population = new Particle*[NUMPARTICLES], *best_particle = new Particle();
// 	int active[number_particles];
//         int actives = 0;
// 
//         //velocity parameters
//         double initialWeight = 0.9, finalWeight = 0.4;
//         double weight;
//         double cognition_parameter = 0.5;
//         double social_parameter = 0.5;
// 
//         //initialize a population of particles with random positions and velocities
//         functionEvaluations = 0;
//         for(i = 0; i<number_particles; i++){
//             population[i] = new Particle();
//             population[i]->position = new double[dimension];
//             population[i]->velocity = new double[dimension];
//             population[i]->best_position = new double[dimension];
//             //velocity parameters
//             for(j=0; j<dimension; j++){
// 
//                 if(lb != NULL && ub != NULL){
//                     population[i]->position[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
//                     //population[i]->velocity[j] = (ub[j]-lb[j])*generate_ramdom() + lb[j];
//                     population[i]->velocity[j] = 0.0;
//                 }
//                 else{
//                     population[i]->position[j] = generate_ramdom();
//                     population[i]->velocity[j] = 0.0;
//                 }
//                 population[i]->best_position[j] = population[i]->position[j];
//                 //velocity paramenters
//             }
//             population[i]->fitness = objfun(population[i]->position);
//             functionEvaluations++;
//             population[i]->best_fitness = population[i]->fitness;
// 	    
// 	   int flag = rand()%2;
// 	    if(flag){
//                 active[i] = 1;
//                 actives++;
//             }
//             else{
//                 active[i] = 0;
//             }
//         }
//         //population intialized
// 
// 
//         best_particle->fitness = population[0]->fitness;
//         best_particle->position = new double[dimension];
//         for(j=0; j<dimension; j++){ best_particle->position[j] = population[0]->position[j]; }
//         for(i=1; i<number_particles; i++){
//             if(population[i]->fitness < best_particle->fitness){
//                 best_particle->fitness = population[i]->fitness;
//                 for(j=0; j<dimension; j++){ best_particle->position[j] = population[i]->position[j];}
//             }
//         }
// 
//         int iteracoes = 0, maxEval = 2000;
//          while(functionEvaluations < maxEval){
// // 	   cout<<"("<<actives<<";"<<functionEvaluations<<");\n";
// //            cout<<fitness_global<<"  ";
//             bool successful = false, test=false;
//             weight = initialWeight - (initialWeight - finalWeight)*((double)functionEvaluations)/((double)maxEval);
// 
//             for(i=0; i<number_particles && functionEvaluations < maxEval; i++){
// 		 double aux = 0;
// 		 if(active[i]){
// 		   for(j=0; j<dimension; j++){
// 			population[i]->velocity[j] = (weight*population[i]->velocity[j]) + (cognition_parameter*generate_ramdom()*(population[i]->best_position[j] -
// 						    population[i]->position[j])) + (social_parameter*generate_ramdom()*(best_particle->position[j] - population[i]->position[j]));
// 
// 
// 			population[i]->position[j] = population[i]->position[j] + population[i]->velocity[j];
// 			if(lb != NULL && ub != NULL){
// 			    if(population[i]->position[j] < lb[j]){ population[i]->position[j] = lb[j]; }
// 			    if(population[i]->position[j] > ub[j]){ population[i]->position[j] = ub[j]; }
// 			}
// 			aux += (population[i]->position[j] - best_particle->position[j])*(population[i]->position[j] - best_particle->position[j]);
// 		    }
// 		    population[i]->fitness = objfun(population[i]->position);
// 		    functionEvaluations++;
// 		    if(population[i]->fitness < population[i]->best_fitness){
// 			population[i]->best_fitness = population[i]->fitness;
// 			for(j=0; j<dimension; j++){
// 			    population[i]->best_position[j] = population[i]->position[j];
// 			}
// 			if(population[i]->fitness < best_particle->fitness){
// 			    best_particle->fitness = population[i]->fitness;
// 			    for(j=0; j<dimension; j++){
// 				best_particle->position[j] = population[i]->position[j];
// 			    }
// 			}
// 		    }
// 		 }
// 		    
// 		double dist = sqrt(aux);
// 		if(dist <= weight){
// 		    if(actives > 2){
// 			active[i] = 0;
// 			actives--;
// // 			cout<<"ativos: "<<actives<<endl;
// 		    }
// 		}
// 		else{
// 		    if(actives < number_particles){
// 			active[i] = 1;
// 			actives++;
// // 			cout<<"ativos: "<<actives<<endl;
// 		    }
// 		}		    
//             }        
//         }
// 
//         double valor_final = best_particle->fitness;
//         delete []best_particle->position;
//         delete best_particle;
//         for(i=0; i<number_particles; i++){
//             delete []population[i]->position;
//             delete []population[i]->best_position;
//             delete []population[i]->velocity;
//             delete population[i];
//         }
//         delete []population;
// 
//         return valor_final;
// }
