#include<iostream>
#include "Avaliation_Function.h"
#define NUMPARTICLES 200
#define CRITERION_STOP  0.00001
#define NORMA_VELOCIDADE 0.00001
#define NUMFUNC 1

using namespace std;

typedef struct particle{
    double *position;
    double *best_position;
    double *velocity;
    double fitness;
    double best_fitness;
}Particle;

//add bound constraints
bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, double *lb, double *ub){
    cout<<endl<<"----------------"<<endl<<"EXPLORATORY MOVES"<<endl;

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx=0.0, fx_perturbation=0.0;

    fx = Compute_Function(x_iteration, size, NUNFUNC); /* initializing fx*/
    /* x1 = x0 */
    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){
//        cout<<"Iteração: "<<i+1<<endl;
//        cout<<"Padrão: "<<"| ";
//        for(int t=0; t<size; t++){cout<<pattern[t]<<"| ";}
//        cout<<endl;
        /* xk+1 = xk + delta*e1 */
        x_perturbation[i] = x_iteration[i] + delta*pattern[i];
        fx_perturbation = Compute_Function(x_perturbation, size, NUNFUNC);
        /* if f(xk+1) > f(xk) => unsuccessful iteration */
        /* try xk+1 = xk - delta*e1 */
        if(fx < fx_perturbation){
            x_perturbation[i] = x_iteration[i];
            x_perturbation[i] = x_iteration[i] - delta*pattern[i];
            fx_perturbation = Compute_Function(x_perturbation, size, NUNFUNC);
        }
        /* if f(xk+1) < f(xk) => successful iteration */
        if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true; cout<<"sucesso"<<endl;}
        else{ x_perturbation[i] = x_iteration[i]; }


//        cout<<endl<<"-----------------------"<<endl;
//           cout<<"f(x): "<<fx<<endl;
//           cout<<"Minimizador: ";
//           for(int t=0; t<size; t++){ cout<<x_iteration[t]<<" ";}
//           cout<<endl<<"-------------------------"<<endl;
    }

    delete []x_perturbation;
    return exit;
}

void PSwarm(int dimension, int seed, double delta_initial, double* x, double** pattern){
    if(delta_initial){
        double delta = delta_initial;
        int i, j;
        srand(seed);

        Particle *population = new Particle[NUMPARTICLES];
        double *lb, *ub;
        lb = Lower_Bounds(NUMFUNC, dimension);
        ub = Upper_Bounds(NUMFUNC, dimension);
        if(lb != NULL && ub != NULL){ cout<<"Bounds Constraints Defined"<<endl; }
        else{cout<<"Problem without bounds constraints"<<endl<<"Problem Number: "<<NUMFUNC<<endl;}
        cout<<endl;

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
                if(lb != NULL && ub != NULL){ population[i].position[j] = (rand()%(int)lb[j])+ub[j]; }
                else{ population[i].position[j] = (rand()%10)*0.1; }    //atraves das bounds constraints
                population[i].best_position[j] = population[i].position[j];
                population[i].velocity[j] = (rand()%10)*0.1;
                population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC);
                population[i].best_fitness = population[i].fitness;
                //velocity paramenters
                omega1[i][j] = (rand()%10)*0.1;
                omega2[i][j] = (rand()%10)*0.1;
            } //cout<<endl;
        }
        //population intialized

        //find the best fitness
        double fitness_global = population[0].fitness;
        double *position_global = new double[dimension];
        for(j=0; j<dimension; j++){ position_global[j] = population[0].position[j]; }
        for(i=1; i<number_particles; i++){
            if(population[i].fitness < fitness_global){
                fitness_global = population[i].fitness;
                for(j=0; j<dimension; j++){ position_global[j] = population[i].position[j]; }
            }
        }

        while(delta > CRITERION_STOP){
            bool successful = false;
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

                    //CALCULAR O TAMANHO DA VELOCIDADE
                    population[i].position[j] = population[i].position[j] + population[i].velocity[j];
                    if(lb != NULL && ub != NULL){
                        if(population[i].position[j] < lb[j]){ population[i].position[j] = lb[j]; }
                        else if(population[i].position[j] > ub[j]){ population[i].position[j] = ub[j]; }
                    }
                }
                population[i].fitness = Compute_Function(population[i].position, dimension, NUMFUNC);
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
                        delta = delta*2;
                        successful = true;
                    }
                }
            }
            if(!successful){
                for(i=0; i<dimension; i++){
                    if(Exploratory_Moves(pattern[i],delta,position_global,dimension, lb, ub)){ delta = 2*delta;}
                    else{ delta = (0.5)*delta; }
                }
            }
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

    }
}
