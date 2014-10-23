#ifndef ESPS_H_INCLUDED
#define ESPS_H_INCLUDED

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function);
double Normal_distribuition(double mean, double desvio_padrao);
double* Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta);




#endif // ESPS_H_INCLUDED
