#include <iostream>
#include <fstream>
#include "Avaliation_Function.h"
#include "Estrategias.h"
#include "Solution.h"


#define DIMENSAO 10
#define DELTA 0.7
#define INF 3.40282347E+38F
#define MEDIA_ESPERADA 0.7


using namespace std;


int main(int argc, char *argv[])
{

    if(argc == 4){
        int seed = atoi(argv[2]);
        int function = atoi(argv[1]);
        int dimension = atoi(argv[3]);

        PSO(dimension, seed, INF, function, NULL);
    }
    else{
        PSO(DIMENSAO, 2, INF, 5, NULL);
    }
    return 0;
}

