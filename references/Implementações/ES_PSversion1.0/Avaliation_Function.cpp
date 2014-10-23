#include <iostream>
#include<math.h>
#define PI 3.14159265359
#define EULER 2.71828182845
using namespace std;



double Sphere_function(double *x, int size){
    //cout<<endl<<"SPHERE FUNCTION"<<endl;
    //for(int i=0; i<size; i++){ cout<<x[i]<<" ";}
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i];
        //cout<<"fx: "<<fx<<endl;
    }
    return fx;
}

double Ackleys_function(double *x, int size){
    if(size == 2){
    cout<<endl<<"ACKLEYS FUNCTION"<<endl<<"VERTOR X: ";
    for(int i=0; i<size; i++){ cout<<x[i]<<" ";}
        double square_root = -0.2*(sqrt(0.5*(x[0]*x[0] + x[1]*x[1])));
        double term1 = -20*exp(square_root);
        double term2 = -exp(0.5*(cos(2*PI*x[0]) + cos(2*PI*x[1]))) + 20 + EULER;
         cout<<"fx: "<<term1+term2<<endl;
        return term1 + term2;
    }
    else return 10000;
}

double Rosenbrock_function(double* x, int size){
    double fx = 0.0;
    double a1, a2;
    for(int i=0; i<size-1; i++){
        a1 = (x[i+1] - x[i]*x[i]);
        a2 = (x[i]-1);
        fx += 100*(a1*a1) + a2*a2;
    }
    return fx;
}

double Compute_Function(double* x, int size, int num_func){
    switch(num_func){
        case 1:
            return Sphere_function(x, size);
        break;
        case 2:
            return Ackleys_function(x, size);
        break;
        case 3:
            return Rosenbrock_function(x, size);
        break;

    }
}

double* Lower_Bounds(int num_fun, int size){
    double *lb = NULL;
    switch(num_fun){
        case 1:
            return lb;
            break;
        case 2:
            if(size == 2){
                lb = new double[size];
                lb[0] = lb[1] = -5;
            }
            return lb;
            break;
        case 3:
            return lb;
            break;
    }
}

double* Upper_Bounds(int num_fun, int size){
    double *ub = NULL;
    switch(num_fun){
        case 1:
            return ub;
            break;
        case 2:
            if(size == 2){
                ub = new double[size];
                ub[0] = ub[1] = 5;
            }
            return ub;
            break;
        case 3:
            return ub;
            break;
    }
}

