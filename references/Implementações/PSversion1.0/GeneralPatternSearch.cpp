#include <iostream>
#include <math.h>
#include "Avaliation_Function.h"
#define NUNFUNC 1

using namespace std;

//double Compute_Function(double*, int, int);

//add bound constrained
bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size){
    cout<<endl<<"----------------"<<endl<<"EXPLORATORY MOVES"<<endl;

    bool exit = false;
    int i;
    double *x_perturbation = new double[size];
    double fx=0.0, fx_perturbation=0.0;

    fx = Compute_Function(x_iteration, size, NUNFUNC); /* initializing fx*/
    /* x1 = x0 */
    for(i = 0; i<size; i++){x_perturbation[i] = x_iteration[i];}

    for(i=0; i<size; i++){
        cout<<"Iteração: "<<i+1<<endl;
        cout<<"Padrão: "<<"| ";
        for(int t=0; t<size; t++){cout<<pattern[t]<<"| ";}
        cout<<endl;
        /* xk+1 = xk + delta*e1 */
        x_perturbation[i] = x_iteration[i] + delta*pattern[i];
        fx_perturbation = Compute_Function(x_perturbation, size, NUNFUNC);
        /* if f(xk+1) > f(xk) => unsuccessful iteration */
        /* try xk+1 = xk - delta*e1 */
        if(fx < fx_perturbation){
            x_perturbation[i] = x_iteration[i] - delta*pattern[i];
            fx_perturbation = Compute_Function(x_perturbation, size, NUNFUNC);
        }
        /* if f(xk+1) < f(xk) => successful iteration */
        if(fx > fx_perturbation){ x_iteration[i] = x_perturbation[i]; fx = fx_perturbation; exit = true; cout<<"sucesso"<<endl;}
        else{ x_perturbation[i] = x_iteration[i]; }


        cout<<endl<<"-----------------------"<<endl;
           cout<<"f(x): "<<fx<<endl;
           cout<<"Minimizador: ";
           for(int t=0; t<size; t++){ cout<<x_iteration[t]<<" ";}
           cout<<endl<<"-------------------------"<<endl;
    }

    delete []x_perturbation;
    return exit;
}
double GeneralPatternSearch(double delta_initial, double *x_best, double **Pattern_initial, int size_problem, double criterion_stop){

    if(delta_initial > 0){
        int i;
        double delta = delta_initial, fx;

        for(i=0; i<2*size_problem && delta >= criterion_stop; i++){

           fx = Compute_Function(x_best, size_problem, NUNFUNC);
           cout<<endl<<"-----------------------"<<endl;
           cout<<"GENERAL PATTERN SEARCH"<<endl;
           cout<<"Iteração: "<<i+1<<endl;
           cout<<"f(x): "<<fx<<endl;
           cout<<"Delta: "<<delta<<endl;
           cout<<"Minimizador: ";
           for(int l=0; l<size_problem; l++){ cout<<x_best[l]<<" ";}
           cout<<endl<<"-------------------------"<<endl;

            //compute f(x)
            //determine a new step using the Exploratory Moves
            //if f(xk + sk), the xk+1 = xk + sk. otherwise, xk+1 = xk
            //Update (delta, PK)
            if(!Exploratory_Moves(Pattern_initial[i], delta, x_best, size_problem)){ delta = delta*(0.5); } // if unsuccessful perturbation
            else {delta  = delta*2; } // successful iteration

            //update Pk
           // for(int j=0; j<size_problem; j++){ Pattern[j] = Pattern_initial[i+1][j]; }

        }

        fx = Compute_Function(x_best, size_problem, NUNFUNC);

        return fx;
    }

    return 10000;
}
