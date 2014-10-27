#ifndef PSPSO_H_INCLUDED
#define PSPSO_H_INCLUDED

float Size_Velocity(double* velocity, int dimension);
bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, double *lb, double *ub);
void PSwarm(int dimension, int seed, double delta_initial, int number_function, double* position_global);

#endif // PSPSO_H_INCLUDED
