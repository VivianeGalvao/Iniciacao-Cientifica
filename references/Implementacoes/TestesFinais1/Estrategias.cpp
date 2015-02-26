#include <iostream>
#include "Estrategias.h"
#include "Solution.h"
#include "Avaliation_Function.h"
#include "Sort.h"
#include "Selection.h"
#include<cmath>
#include <random>

#define NUMPARTICLES 50
#define MAX_DELTA 0.00001
#define INF 3.40282347E+38F
#define MI 4
#define LAMBDA 3*MI

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

        double delta = delta_initial;

        int i, j, NUMFUNC = number_function;
        srand(seed);

        Particle **population = new Particle*[NUMPARTICLES], *best_particle = new Particle();
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
    else{ cout<<"Delta informado menor que zero"; }

}

//double Normal_distribution(double mean, double variancia){
//    default_random_engine generator;
//    normal_distribution<double> distribution(mean,variancia);
//    double aux = distribution(generator);
//    cout<<aux<<" ";
//    return aux;
//}

//double Normal_distribution(double mean, double variancia){
//    random_device rd; // A random number generator that produces non-deterministic random numbers, if supported.
//    mt19937 gen(rd());
//    normal_distribution<double> distribution(mean,variancia);
//    double aux = distribution(gen);
////    cout<<aux<<" ";
//    return aux;
//}

double Normal_distribution(double mean, double variancia){
    mt19937 gen(rand());
    normal_distribution<double> distribution(mean,variancia);
    double aux = distribution(gen);
//    cout<<aux<<" ";
    return aux;
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


       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);
       functionEvaluations = 0;
       for(i=0; i<MI; i++){

            progenitor[i] = new Individual();
            progenitor[i]->position = new double[dimension];
            if(lb != NULL && ub != NULL){
                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = (ub[j] - lb[j])*generate_ramdom() + lb[j]; }
                progenitor[i]->standard_deviation = (ub[0] - lb[0])*Normal_distribution(0,1/sqrt(dimension));
            }
            else{
                for(int j=0; j<dimension; j++){ progenitor[i]->position[j] = generate_ramdom(); }
                progenitor[i]->standard_deviation = Normal_distribution(0,1/sqrt(dimension));
            }
            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
            functionEvaluations++;
//            progenitor[i]->standard_deviation = Normal_distribution(0,1);
//            progenitor[i]->standard_deviation = generate_ramdom();
//            progenitor[i]->standard_deviation = (ub[0] - lb[0])*generate_ramdom();

        }

        best_individual->position = new double[dimension];
        best_individual->objective_function = progenitor[0]->objective_function;
        best_individual->standard_deviation = progenitor[0]->standard_deviation;
        for( i=0; i<dimension; i++){ best_individual->position[i] = progenitor[0]->position[i]; }
        for( i=1; i<MI; i++){
            if(progenitor[i]->objective_function < best_individual->objective_function){
                best_individual->standard_deviation = progenitor[i]->standard_deviation;
                best_individual->objective_function = progenitor[i]->objective_function;
                for(int j=0; j<dimension; j++){ best_individual->position[j] = progenitor[i]->position[j]; }
            }
        }
        criteria = Number_Evaluations(number_function);
        int p=0;
        int q = 0;

        while(functionEvaluations < criteria){
            int t=0;
            q++;
            for(i=0; i<MI; i++){
                for(int j=0; j<LAMBDA/MI && functionEvaluations<criteria; j++, t++){

                    for(int k=0; k<dimension; k++){
                        progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->standard_deviation);
                        if(progeny[t]->position[k] < lb[k]){ progeny[t]->position[k] = lb[k];}
                        if(progeny[t]->position[k] > ub[k]){ progeny[t]->position[k] = ub[k];}
                    }

                    progeny[t]->standard_deviation = progenitor[i]->standard_deviation;
                    progeny[t]->objective_function = Compute_Function(progeny[t]->position, dimension, number_function);
                    functionEvaluations++;
                    if(progeny[t]->objective_function < progenitor[i]->objective_function){
                        if(progeny[t]->objective_function < best_individual->objective_function){
                            best_individual->objective_function = progeny[t]->objective_function;
                            best_individual->standard_deviation = progeny[t]->standard_deviation;
                            for(int w=0; w<dimension; w++){
                               best_individual->position[w] = progeny[t]->position[w];
                            }
                            p++;
                        }
                    }
                }

                progenitor[i]->standard_deviation = progenitor[i]->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));
            }
            PlusIsotropic(progenitor, progeny, dimension, MI, LAMBDA);
        }


        for(i=0; i<dimension; i++){ x[i] = best_individual->position[i];}
//        cout<<endl;
//        cout<<Compute_Function(x, dimension, number_function)<<endl;
//        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
//        cout<<"AVALIACOES DE FUNCAO ---------------- "<<functionEvaluations<<endl;
//        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
//        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
//        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
//        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;

        for(i=0; i<MI; i++){
            delete []progenitor[i]->position;
            delete progenitor[i];
        }
        for(i=0; i<LAMBDA; i++){
             delete []progeny[i]->position;
            delete progeny[i];
        }
        delete []progenitor;
        delete []progeny;
        delete []best_individual->position;
        delete best_individual;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
     }
      else{ cout<<"Delta informado menor que zero"; }
}

void Evolutionary_Strategy4(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){
    if(delta > 0){
        srand(seed);
        criteria = 0;
        Individual **progenitor = new Individual*[MI];
        Individual **progeny = new Individual*[LAMBDA];
        Individual *best_individual = new Individual();

        int i;
        for(i=0; i<LAMBDA; i++){ progeny[i] = new Individual(); progeny[i]->position = new double[dimension]; progeny[i]->sd = new double[dimension]; }


       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);
       functionEvaluations = 0;
       for(i=0; i<MI; i++){

            progenitor[i] = new Individual();
            progenitor[i]->position = new double[dimension];
            progenitor[i]->sd = new double[dimension];
            if(lb != NULL && ub != NULL){
               // double aux = (ub[0] - lb[0])*Normal_distribution(0,1/sqrt(dimension));
                for(int j=0; j<dimension; j++){
                    progenitor[i]->position[j] = (ub[j] - lb[j])*generate_ramdom() + lb[j];
                    progenitor[i]->sd[j] = (ub[j] - lb[j])*Normal_distribution(0,1/sqrt(dimension));
               //     progenitor[i]->sd[j] = aux;
                }
            }
            else{
//                double aux = Normal_distribution(0,1/sqrt(dimension));
                for(int j=0; j<dimension; j++){
                    progenitor[i]->position[j] = generate_ramdom();
                    progenitor[i]->sd[j] = Normal_distribution(0,1/sqrt(dimension));
//                    progenitor[i]->sd[j] = aux;
                }
            }
            progenitor[i]->objective_function = Compute_Function(progenitor[i]->position, dimension, number_function);
            functionEvaluations++;
//            progenitor[i]->standard_deviation = Normal_distribution(0,1);
//            progenitor[i]->standard_deviation = generate_ramdom();
//            progenitor[i]->standard_deviation = (ub[0] - lb[0])*generate_ramdom();

        }

        best_individual->position = new double[dimension];
        best_individual->objective_function = progenitor[0]->objective_function;
        for( i=0; i<dimension; i++){ best_individual->position[i] = progenitor[0]->position[i]; }
        for( i=1; i<MI; i++){
            if(progenitor[i]->objective_function < best_individual->objective_function){
                best_individual->objective_function = progenitor[i]->objective_function;
                for(int j=0; j<dimension; j++){ best_individual->position[j] = progenitor[i]->position[j]; }
            }
        }
        criteria = Number_Evaluations(number_function);
        int p=0;
        int q = 0;

        while(functionEvaluations < criteria){
            int t=0;
            q++;
            for(i=0; i<MI; i++){
                for(int j=0; j<LAMBDA/MI && functionEvaluations<criteria; j++, t++){

                    for(int k=0; k<dimension; k++){
                        progeny[t]->position[k] = progenitor[i]->position[k] + Normal_distribution(0, progenitor[i]->sd[k]);
                        progeny[t]->sd[k] = progenitor[i]->sd[k];
                        if(progeny[t]->position[k] < lb[k]){ progeny[t]->position[k] = lb[k];}
                        if(progeny[t]->position[k] > ub[k]){ progeny[t]->position[k] = ub[k];}
                    }

                    progeny[t]->objective_function = Compute_Function(progeny[t]->position, dimension, number_function);
                    functionEvaluations++;
                    if(progeny[t]->objective_function < progenitor[i]->objective_function){
                        if(progeny[t]->objective_function < best_individual->objective_function){
                            best_individual->objective_function = progeny[t]->objective_function;
                            for(int w=0; w<dimension; w++){
                               best_individual->position[w] = progeny[t]->position[w];
                            }
                            p++;
                        }
                    }
                }

                double aux = exp(Normal_distribution(0, 1/sqrt(2*dimension)));
                for(int k=0; k<dimension; k++){
                    progenitor[i]->sd[k] = progenitor[i]->sd[k]*aux*exp(Normal_distribution(0, 1/sqrt(2*sqrt(dimension))));
                }
            }

            PlusNonIsotropic(progenitor, progeny, dimension, MI, LAMBDA);
        }


        for(i=0; i<dimension; i++){ x[i] = best_individual->position[i];}
//        cout<<endl;
//        cout<<Compute_Function(x, dimension, number_function)<<endl;
//        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
//        cout<<"AVALIACOES DE FUNCAO ---------------- "<<functionEvaluations<<endl;
//        cout<<"NUMERO DE ITERACOES ----------------- "<<q<<endl;
//        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
//        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
//        cout<<"ITERACOES DE SUCESSO ---------------- "<<(q - es) + (es - ps)<<endl;

        for(i=0; i<MI; i++){
            delete []progenitor[i]->position;
            delete []progenitor[i]->sd;
            delete progenitor[i];
        }
        for(i=0; i<LAMBDA; i++){
             delete []progeny[i]->position;
             delete []progeny[i]->sd;
            delete progeny[i];
        }
        delete []progenitor;
        delete []progeny;
        delete []best_individual->position;
        delete best_individual;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
     }
      else{ cout<<"Delta informado menor que zero"; }
}


void Evolutionary_Strategy2(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        functionEvaluations = 0;
        srand(seed);
        int i;
        Individual *individuo = new Individual();
        individuo->position = new double[dimension];


       double *lb = new double[dimension], *ub = new double[dimension];
       Lower_Bounds(number_function, dimension, lb);
       Upper_Bounds(number_function, dimension, ub);


        if(lb != NULL && ub != NULL){
            for(i=0; i<dimension; i++){ individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i]; }
             individuo->standard_deviation = (ub[0]-lb[0])*Normal_distribution(0, 1/(sqrt(dimension)));
        }
        else{
            for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); }
             individuo->standard_deviation = Normal_distribution(0, 1/(sqrt(dimension)));
        }
        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
        functionEvaluations++;

        criteria = Number_Evaluations(number_function);
        int t=0, functionEvaluations=0;

        while(functionEvaluations < criteria){
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

            }

            individuo->standard_deviation = individuo->standard_deviation*exp(Normal_distribution(0, 1/sqrt(dimension)));

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
     else{ cout<<"Delta informado menor que zero"; }
}

void Evolutionary_Strategy1(int seed, double expected_mean, int dimension, int number_function, double delta, double *x){

    if(delta > 0){
        functionEvaluations = 0;
        srand(seed);
        int i;

        Individual *individuo = new Individual();
        individuo->position = new double[dimension];
        individuo->standard_deviation = expected_mean/sqrt(dimension);

        int *successful = new int[dimension*10];

        double *lb = new double[dimension], *ub = new double[dimension];
        Lower_Bounds(number_function, dimension, lb);
        Upper_Bounds(number_function, dimension, ub);

        for(i=0; i<dimension*10; i++){ successful[i] = 0; }

        if(lb != NULL && ub!=NULL){
            for(i=0; i<dimension; i++){
                individuo->position[i] = (ub[i] - lb[i])*generate_ramdom() + lb[i];
            }
        }
        else{ for(i=0; i<dimension; i++){ individuo->position[i] = generate_ramdom(); } }

        individuo->objective_function = Compute_Function(individuo->position, dimension, number_function);
        functionEvaluations++;

        criteria = Number_Evaluations(number_function);

        int t=0;

        while(functionEvaluations < criteria){
             if(t%dimension == 0 && t>=dimension*10){
                double sum=0, pt;
                for(i=0; i<dimension*10; i++){sum += successful[i]; }
                pt = sum/10*dimension;
                if(pt > 1/5){ individuo->standard_deviation = individuo->standard_deviation/0.85;}
                else if(pt < 1/5){ individuo->standard_deviation = individuo->standard_deviation*0.85; }
            }
            double y[dimension];
            for(i=0; i<dimension; i++){
                y[i] = individuo->position[i] + Normal_distribution(0, individuo->standard_deviation);
                if(lb != NULL && ub != NULL){
                    if(y[i] < lb[i]){ y[i] = lb[i]; }
                    if(y[i] > ub[i]){ y[i] = ub[i]; }
                }
            }
            double aux = Compute_Function(y, dimension, number_function); functionEvaluations++;
            if(aux < individuo->objective_function){
                individuo->objective_function = aux;
                for(i=0; i<dimension; i++){ individuo->position[i] = y[i]; }
                successful[(t+1)%(dimension*10)] = 1;

            }
            else{ successful[(t+1)%(dimension*10)] = 0;}

            t = t+1;
        }
//        cout<<"NUMERO FUNCAO ------------------ "<<number_function<<endl;
//        cout<<"AVALIACOES DA FUNCAO OBJETIVO ------- "<<functionEvaluations<<endl;
//        cout<<"NUMERO DE ITERACOES ----------------- "<<t<<endl;
//        cout<<"ITERACOES SEM SUCESSO ES ------------ "<<es<<endl;
//        cout<<"ITERACOES SEM SUCESSO PS ------------ "<<ps<<endl;
//        cout<<"ITERACOES DE SUCESSO ---------------- "<<(t - es) + (es - ps)<<endl;

        for(int k=0; k<dimension; k++){ x[k] = individuo->position[k]; }
        delete []successful;
        if(lb != NULL && ub != NULL){
            delete []lb;
            delete []ub;
        }
    }
     else{ cout<<"Delta informado menor que zero"; }
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

