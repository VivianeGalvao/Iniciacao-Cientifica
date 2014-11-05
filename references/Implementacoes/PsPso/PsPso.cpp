#include<iostream>
#include<fstream>
#include "Avaliation_Function.h"
#include<math.h>
#include<climits>
#include<time.h>
#include<stdlib.h>
#define NUMPARTICLES 50
#define CRITERION_STOP  0.00001
#define NORMA_VELOCIDADE 0.1
#define INF 3.40282347E+38F

using namespace std;

int evaluations;
double fitness_global;

typedef struct particle{
    double *position;
    double *best_position;
    double *velocity;
    double fitness;
    double best_fitness;
}Particle;

float Size_Velocity(double* velocity, int dimension){
    double size = 0.0;
    for(int i=0; i<dimension; i++){ size += velocity[i]*velocity[i];  }
    return sqrt(size);
}

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, double *lb, double *ub, int NUMFUNC){

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx = fitness_global, fx_perturbation=0.0;

    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){
        x_perturbation[i] = x_iteration[i] + delta*pattern[i];

        if(lb != NULL && ub != NULL){
            if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, NUMFUNC); evaluations++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            } else{
                 fx_perturbation = Compute_Function(x_perturbation, size, NUMFUNC); evaluations++;
                if(fx < fx_perturbation){
                    x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                }
                if(x_perturbation[i] < lb[i] || x_perturbation[i] > ub[i]){  x_perturbation[i] = x_iteration[i]; }
                else{
                    fx_perturbation = Compute_Function(x_perturbation, size, NUMFUNC); evaluations++;
                    if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
                    else{ x_perturbation[i] = x_iteration[i]; }
                }
            }
        }
        else{
            fx_perturbation = Compute_Function(x_perturbation, size, NUMFUNC); evaluations++;

            if(fx < fx_perturbation){
                x_perturbation[i] = x_iteration[i] - delta*pattern[i];
                fx_perturbation = Compute_Function(x_perturbation, size, NUMFUNC); evaluations++;
            }

            if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true;}
            else{ x_perturbation[i] = x_iteration[i]; }
        }
    }

    if(exit)fitness_global = fx;
    delete []x_perturbation;
    return exit;
}

void PSwarm(int dimension, int seed, double delta_initial, int number_function, double* position_global){
    if(delta_initial > 0){
        evaluations = 0;
        double **pattern = new double*[dimension*2];
        for(int i=0; i<dimension*2; i++){ pattern[i] = new double[dimension];}
        /** Gerando a matriz de direções padrão*/ /**MAXIMAL POSITIVE BASE*/
        for(int j=0; j<dimension*2; j++){
            for(int i=0; i<dimension; i++){
               if(j < dimension){
                if( i == j){ pattern[j][i] = 1.0;}
                else { pattern[j][i] = 0.0; }
               }
               else{
                    if(j - i == dimension){ pattern[j][i] = -1.0;}
                    else { pattern[j][i] = 0.0; }
               }
            }
          }
     //   cout<<"---------------------------------------------"<<endl;

        int number_particles = NUMPARTICLES;
        int ps=0, pso=0;
        double delta = delta_initial;

        int i, j, NUMFUNC = number_function;
        srand(seed);

        Particle *population = new Particle[NUMPARTICLES];
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
            if(mindelta >=INF || mindelta <= CRITERION_STOP){ delta = 2*sqrt(sqrt(CRITERION_STOP)); }
            else{ delta = mindelta/5;}
        }
       // cout<<"DELTA INICIAL ----------- "<<delta<<endl;


         //velocity parameters
        double inertia_factor = 1.0;
        double cognition_parameter = 0.5;
        double social_parameter = 0.5;
        double **omega1 = new double*[number_particles], **omega2=new double*[number_particles];


        //initialize a population of particles with random positions and velocities
        for(i = 0; i<number_particles; i++){
            population[i].position = new double[dimension];
            population[i].velocity = new double[dimension];
            population[i].best_position = new double[dimension];
            //velocity parameters
            omega1[i] = new double[dimension];
            omega2[i] = new double[dimension];
            for(j=0; j<dimension; j++){

                if(lb != NULL && ub != NULL){ population[i].position[j] = (ub[j]-lb[j])*(rand()%10)*0.01 + lb[j]*0.01; }
                else{ population[i].position[j] = (rand()%10)*0.01; }    //atraves das bounds constraints
                population[i].best_position[j] = population[i].position[j];
                population[i].velocity[j] = ((rand()%10)*0.01);
                //velocity paramenters
                omega1[i][j] = (rand()%10)*0.1;
                omega2[i][j] = (rand()%10)*0.1;
            }
            population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC);evaluations++;
            population[i].best_fitness = population[i].fitness;
        }
        //population intialized


        fitness_global = population[0].fitness;
        for(j=0; j<dimension; j++){ position_global[j] = population[0].position[j]; }
        for(i=1; i<number_particles; i++){
            if(population[i].fitness < fitness_global){
                fitness_global = population[i].fitness;
                for(j=0; j<dimension; j++){ position_global[j] = population[i].position[j];}
            }
        }

        cout<<"Melhor inicial"<<endl;
        for(i=0; i<dimension; i++){
            cout<<" "<<position_global[i];
        }
        cout<<endl;

        int iteracoes = 0, maxEval = Number_Evaluations(number_function);

         while(iteracoes < maxEval){
            bool successful = false, test=false;
            for(i=0; i<number_particles; i++){
                for(j=0; j<dimension; j++){
                    omega1[i][j] = (rand()%10)*0.1;
                    omega2[i][j] = (rand()%10)*0.1;
                }
            }
            for(i=0; i<number_particles; i++){
                for(j=0; j<dimension; j++){
                    population[i].velocity[j] = (inertia_factor*population[i].velocity[j]) + (cognition_parameter*omega1[i][j]*(population[i].best_position[j] -
                                                population[i].position[j])) + (social_parameter*omega2[i][j]*(position_global[j] - population[i].position[j]));


                    population[i].position[j] = population[i].position[j] + population[i].velocity[j];
                    if(lb != NULL && ub != NULL){
                        if(population[i].position[j] < lb[j]){ population[i].position[j] = lb[j]*0.01; }
                        if(population[i].position[j] > ub[j]){ population[i].position[j] = ub[j]*0.01; }
                    }
                }

                population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC); evaluations++;
                if(population[i].fitness < population[i].best_fitness){
                    population[i].best_fitness = population[i].fitness;
                    for(j=0; j<dimension; j++){
                        population[i].best_position[j] = population[i].position[j];
                    }
                    if(population[i].fitness < fitness_global){
                        fitness_global = population[i].fitness;
                        for(j=0; j<dimension; j++){
                            position_global[j] = population[i].position[j];
                        }
                        successful = true;
                    }
                }
            }

            if(!successful){
                pso++;
                for(i=0; i<2*dimension && iteracoes<maxEval; i++){
                    if(Exploratory_Moves(pattern[i],delta,position_global,dimension, lb, ub, NUMFUNC)){ delta = 1.5*delta; test = false;}
                    else{ delta = (0.5)*delta;  test=true; }
                }
                if(test){ ps++; }
            }
            iteracoes++;
            if(delta == 0){ delta = 0.7;}

        }

        for(i=0; i<number_particles; i++){
            delete []population[i].position;
            delete []population[i].best_position;
            delete []population[i].velocity;
            delete []omega1[i];
            delete []omega2[i];
        }
        delete []population;
        delete []omega1;
        delete []omega2;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }

        for(int i=0; i<dimension*2; i++){ delete []pattern[i]; }
        delete []pattern;

        cout<<endl;
        cout<<"NUMERO DA FUNCAO --------------- "<<number_function<<endl;
        cout<<"AVALIACOES DE FUNCAO ----------- "<<iteracoes<<endl;
        cout<<"ITERACOES DE SUCESSO ----------- "<<(iteracoes - pso) + (pso - ps)<<endl;
        cout<<"ITERAÇÕES SEM SUCESSO - PSO ---- "<<pso<<endl;
        cout<<"ITERAÇÕES SEM SUCESSO - PS ----- "<<ps<<endl;
       // cout<<"DELTA FINAL -------------------- "<<delta<<endl;

        cout<<endl;
    }

}
