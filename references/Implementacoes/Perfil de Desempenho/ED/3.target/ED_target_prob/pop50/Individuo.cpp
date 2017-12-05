#include "Individuo.h"
#include <iostream>

Individuo::Individuo(int dimension){
    double *aux = new double[dimension];
    posicao =aux;
    aux=NULL;
}

Individuo::~Individuo(){
    delete []posicao;
}
