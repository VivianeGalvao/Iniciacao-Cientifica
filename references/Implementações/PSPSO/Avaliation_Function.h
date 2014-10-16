#ifndef AVALIATION_FUNCTION_H_INCLUDED
#define AVALIATION_FUNCTION_H_INCLUDED

double Compute_Function(double* x, int size, int num_func);
double Sphere_function(double* x, int size);
double Ackleys_function(double *x, int size);
double Rosenbrock_function(double* x, int size);
double* Lower_Bounds(int num_fun, int size);
double* Upper_Bounds(int num_fun, int size);


#endif // AVALIATION_FUNCTION_H_INCLUDED
