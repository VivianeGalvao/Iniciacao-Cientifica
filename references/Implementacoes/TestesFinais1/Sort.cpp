#include <iostream>
#include "Solution.h"

using namespace std;

void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension){

    double pivot;
    Individual *aux = new Individual();
    aux->position = new double[dimension];
    i[0] = left; j[0] = right;
    int mean = (i[0] + j[0])/2;
    pivot = sample[mean]->objective_function;

    do{
        while(pivot > sample[i[0]]->objective_function){ i[0]++; }
        while(pivot < sample[j[0]]->objective_function){ j[0]--; }

        if( i[0] <= j[0]){
            aux->objective_function = sample[i[0]]->objective_function;
            aux->standard_deviation = sample[i[0]]->standard_deviation;
            for(int k=0; k<dimension; k++){ aux->position[k] = sample[i[0]]->position[k]; }

            sample[i[0]]->objective_function = sample[j[0]]->objective_function;
            sample[i[0]]->standard_deviation = sample[j[0]]->standard_deviation;
            for(int k=0; k<dimension; k++){ sample[i[0]]->position[k] = sample[j[0]]->position[k]; }

            sample[j[0]]->objective_function = aux->objective_function;
            sample[j[0]]->standard_deviation = aux->standard_deviation;
            for(int k=0; k<dimension; k++){ sample[j[0]]->position[k] = aux->position[k]; }

            i[0]++; j[0]--;
        }

    }while(i[0] <= j[0]);
    if(aux->sd != NULL){ delete []aux->sd; }
    delete []aux->position;
    delete aux;
}

void QuickSort(Individual **sample, int left, int right, int dimension){

    int *i = new int(), *j = new int();
    Partition(sample, left, right, i, j, dimension);
    if(left < j[0]){ QuickSort(sample, left, j[0], dimension); }
    if(i[0] < right){ QuickSort(sample, i[0], right, dimension); }
    delete i;
    delete j;
}

void quickSort(Individual **sample, int esquerda, int direita, int dimension)
{
    Individual *aux = new Individual();
    aux->position = new double[dimension];
    aux->sd = new double[dimension];
    int i, j;
    i = esquerda;
    j = direita;
    int mean = (i+j)/2;
    double x = sample[mean]->objective_function;


    while(i <= j)
    {
        while(sample[i]->objective_function < x && i < direita){ i++; }
        while(sample[j]->objective_function > x && j > esquerda){ j--; }
        if(i <= j)
        {
            aux->objective_function = sample[i]->objective_function;
            for(int k=0; k<dimension; k++){
                aux->position[k] = sample[i]->position[k];
                aux->sd[k] = sample[i]->sd[k];
            }

            sample[i]->objective_function = sample[j]->objective_function;
            for(int k=0; k<dimension; k++){
                sample[i]->position[k] = sample[j]->position[k];
                sample[i]->sd[k] = sample[j]->sd[k];
            }

            sample[j]->objective_function = aux->objective_function;
            for(int k=0; k<dimension; k++){
                sample[j]->position[k] = aux->position[k];
                sample[j]->sd[k] = aux->sd[k];
            }
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickSort(sample, esquerda, j, dimension);
    }
    if(i < direita)
    {
        quickSort(sample,  i, direita, dimension);
    }


    delete []aux->position;
    delete []aux->sd;
    delete aux;
}
