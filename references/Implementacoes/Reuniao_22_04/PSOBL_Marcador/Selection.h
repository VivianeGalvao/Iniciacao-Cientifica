#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED
#include "Solution.h"

void PlusIsotropic(Individual **progenitor, Individual **progeny, int dimension, int MI, int LAMBDA);
void PlusNonIsotropic(Individual **progenitor, Individual **progeny, int dimension, int MI, int LAMBDA);

#endif // SELECTION_H_INCLUDED
