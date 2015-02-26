#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

void QuickSort(Individual **sample, int left, int right, int dimension);
void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension);
void quickSort(Individual **sample, int esquerda, int direita, int dimension);


#endif // SORT_H_INCLUDED
