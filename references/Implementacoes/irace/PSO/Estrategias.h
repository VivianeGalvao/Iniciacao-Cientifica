#ifndef ESTRATEGIAS_H_INCLUDED
#define ESTRATEGIAS_H_INCLUDED
#include "Solution.h"


double PSO(double (*objfun)(double*), int dimension, int seed, double *lb, double *ub, double iW, double fW, double cogP, double socP);

bool VerificadorSolucao(double *x, int dimension, int number_function);




#endif // ESTRATEGIAS_H_INCLUDED
