#ifndef ESTRATEGIAS_H_INCLUDED
#define ESTRATEGIAS_H_INCLUDED

double EvolucaoDiferencialBL(double (*objfun)(double*), double fator_ponderacao, double cr, int dimension, int num_individuos, int seed, double *lb, double *ub, double delta_inicial);

#endif // ESTRATEGIAS_H_INCLUDED
