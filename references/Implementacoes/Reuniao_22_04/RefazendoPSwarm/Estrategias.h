#ifndef ESTRATEGIAS_H_INCLUDED
#define ESTRATEGIAS_H_INCLUDED
#include "Solution.h"

class Estrategia{
    private:
       static bool Exploratory_Moves(double delta, Particle *sample, int size, int number_function, double* lb, double* ub);

    public:
        static double *sampling[2];
        static int iterations[2];
        /*
            0 -> PSOBL
            1 -> PSO
        */
        static void PSOBL(int dimension, int seed, double delta_initial, int number_function, double* position_global);
        static void PSO(int dimension, int seed, int number_function, double* position_global);
};

bool VerificadorSolucao(double *x, int dimension, int number_function);




#endif // ESTRATEGIAS_H_INCLUDED
