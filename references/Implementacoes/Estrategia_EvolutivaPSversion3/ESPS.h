#ifndef ESPS_H_INCLUDED
#define ESPS_H_INCLUDED

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function, double *lb, double *ub);
double Normal_distribuition(double mean, double desvio_padrao);
void Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void VerificadorSolucao(double *x, int dimension, int number_function);



#endif // ESPS_H_INCLUDED
