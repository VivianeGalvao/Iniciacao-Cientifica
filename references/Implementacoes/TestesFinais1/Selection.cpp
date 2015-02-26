#include <iostream>
#include "Solution.h"
#include "Sort.h"

using namespace std;

void PlusIsotropic(Individual **progenitor, Individual **progeny, int dimension, int MI, int LAMBDA){

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
    }
    //cout<<progenitor[0]->objective_function<<endl;
    for(int i=0; i<MI+LAMBDA; i++){
        delete []sample[i]->position;
        delete sample[i];
    }
    delete []sample;
}

void PlusNonIsotropic(Individual **progenitor, Individual **progeny, int dimension, int MI, int LAMBDA){

    Individual **sample = new Individual*[MI+LAMBDA];
    for(int i=0, t=0; i<MI+LAMBDA && t<LAMBDA; i++){
        sample[i] = new Individual();
        sample[i]->position = new double[dimension];
        sample[i]->sd = new double[dimension];
        if(i < MI){

            sample[i]->objective_function = progenitor[i]->objective_function;
//            cout<<"sample1>> "<<sample[i]->objective_function<<endl;
           for(int j=0; j<dimension; j++){
               sample[i]->position[j] = progenitor[i]->position[j];
               sample[i]->sd[j] = progenitor[i]->position[j];
            }
        }
        if(i >=MI){

            sample[i]->objective_function = progeny[t]->objective_function;
//            cout<<"sample2>> "<<sample[i]->objective_function<<endl;
            for(int j=0; j<dimension; j++){
                sample[i]->position[j] = progeny[t]->position[j];
                sample[i]->sd[j] = progeny[t]->sd[j];
            }
            t++;
        }
    }
    quickSort(sample, 0, (MI+LAMBDA)-1, dimension);
    for(int i=0; i<MI; i++){
        progenitor[i]->objective_function = sample[i]->objective_function;
//        cout<<"progenitor<< "<<progenitor[i]->objective_function<<endl;
        for(int j=0; j<dimension; j++){
            progenitor[i]->position[j] = sample[i]->position[j];
            progenitor[i]->sd[j] = sample[i]->sd[j];
        }
    }
    //cout<<progenitor[0]->objective_function<<endl;
    for(int i=0; i<MI+LAMBDA; i++){
        delete []sample[i]->position;
        delete []sample[i]->sd;
        delete sample[i];
    }
    delete []sample;
}

