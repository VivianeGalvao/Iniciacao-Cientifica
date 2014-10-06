#include <iostream>
#include<math.h>
#define PI 3.14159265359
#define EULER 2.71828182845
using namespace std;



double Sphere_function(double *x, int size){
    cout<<endl<<"SPHERE FUNCTION"<<endl;
    for(int i=0; i<size; i++){ cout<<x[i]<<" ";}
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i];
        cout<<"fx: "<<fx<<endl;
    }
    return fx;
}
//
//void Ackleys_function(double fx, double *x, int size){
//    double square_root = -0.2*(sqrt(0.5*(x[0]*x[0] + x[1]*x[1])));
//    double term1 = -20*exp(square_root);
//    double term2 = -exp(0.5*(cos(2*PI*x[0]) + cos(2*PI*x[1]))) + 20 + EULER;
//    fx = term1 + term2;
//}
//
//void Rosenbrock_function(double fx, double* x, int size){
//    fx = 0.0;
//    double a1, a2;
//    for(int i=0; i<size-1; i++){
//        a1 = (x[i+1] - x[i]*x[i]);
//        a2 = (x[i]-1);
//        fx += 100*(a1*a1) + a2*a2;
//    }
//}

double Compute_Function(double* x, int size, int num_func){
    switch(num_func){
        case 1:
            return Sphere_function(x, size);
        break;
//        case 2:
//            Ackleys_function(fx, x, size);
//        break;
//        case 3:
//            Rosenbrock_function(fx, x, size);
//        break;

    }
}

