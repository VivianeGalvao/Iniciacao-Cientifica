#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<cmath>
#define PI 3.14159265359
#define EULER 2.71828182845
#define SEED 0
using namespace std;



double Sphere_function(double *x, int size){
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i];
    }
    return fx;
}

double f02(double *x, int size){
    int i;
    double sum=0, prod=1, a;
    for(i=0; i<size; i++){
        a = abs(x[i]);
        sum += a;
        prod = prod*a;
    }
    return sum+prod;
}

double f03(double *x, int size){
    int i, j;
    double sum1=x[0], sum2=0;
    for(i=0; i<size; i++){
        for(j=0; j<i; j++){
            sum1 += x[j];
        }
        sum2 += sum1*sum1;
        sum1=0;
    }
    return sum2;
}

double f04(double *x, int size){
//    cout<<"Posicao : "<<endl;\
//    for(int t=0; t<1; t++){
//        cout<<" \\\\\\\\\\\\\\\\\\\\\\\"<<x[0];
//    cout<<endl;
    double max = abs(x[0]), a;
    for(int i=1; i<size; i++){
        a = abs(x[i]);
        if(a > max){ max = a; }
    }
    return max;
}

double f05(double* x, int size){
    double fx = 0.0;
    double a1, a2;
    for(int i=0; i<size-1; i++){
        a1 = (x[i+1] - x[i]*x[i]);
        a2 = (x[i]-1);
        fx += 100*(a1*a1) + a2*a2;
    }
    return fx;
}

double f06(double* x, int size){
    double sum=0;
    for(int i=0; i<size; i++){
        sum += int(x[i] + 0.5);
    }
    return sum;
}

double f07(double* x, int size){
    srand(SEED);
    double sum = 0;
    for(int i=0; i<size; i++){
        sum += i*x[i]*x[i]*x[i]*x[i];
    }
    return sum + rand()%10*0.1;
}

double f08(double* x, int size){
    double sum=0;
    for(int i = 0; i<size; i++){
        sum += -x[i]*sin(sqrt(abs(x[i])));
    }
    return sum;
}

double f09(double *x, int size){
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i] - 10*cos(2*PI*x[i]) + 10;
    }
    return fx;
}

double f10(double *x, int size){
    double sum1=0, sum2=0;
    for(int i=0; i<size; i++){
        sum1 += x[i]*x[i];
        sum2 += cos(2*PI*x[i]);
    }
    sum1 = sum1/size;
    sum2 = sum2/size;
    return -20*exp(-0.2*sqrt(sum1)) - exp(sum2) + 20 + EULER;
}

double f11(double *x, int size){
    double sum=0, prod=1;
    for(int i = 0; i<size; i++){
        sum += x[i]*x[i];
        prod = prod*cos(x[i]/sqrt(i+1));
    }
    return sum/4000 - prod +1;
}

double u(double x, double a, double k, double m){
    if(x > a)return k*pow((x-a),m);
    if(x >= -a && x <= a)return 0.0;
    if(x < -a)return k*pow((-x-a), m);
}

double Compute_Function(double* x, int size, int num_func){
    switch(num_func){
        case 1:
            return Sphere_function(x, size);
        break;
        case 2:
            return f02(x, size);
        break;
        case 3:
            return f03(x, size);
        break;
        case 4:
            return f04(x, size);
        break;
        case 5:
            return f05(x, size);
        break;
        case 6:
            return f06(x, size);
        break;
        case 7:
            return f07(x, size);
        break;
        case 8:
            return f08(x, size);
        break;
        case 9:
            return f09(x, size);
        break;
        case 10:
            return f10(x, size);
        break;
        case 11:
            return f11(x, size);
        break;
    }
}

void Lower_Bounds(int num_fun, int size, double *lb){
    switch(num_fun){
        case 1:
            for(int i=0; i<size; i++){ lb[i] = -100.0; }
        break;
        case 2:
            for(int i=0; i<size; i++){ lb[i] = -10.0; }
        break;
        case 3:
            for(int i=0; i<size; i++){ lb[i] = -100.0; }
        break;
        case 4:
            for(int i=0; i<size; i++){ lb[i] = -100.0; }
        break;
        case 5:
            for(int i=0; i<size; i++){ lb[i] = -30.0; }
            break;
        case 6:
            for(int i=0; i<size; i++){ lb[i] = -100.0; }
        break;
        case 7:
            for(int i=0; i<size; i++){ lb[i] = -1.28; }
        break;
        case 8:
            for(int i=0; i<size; i++){ lb[i] = -500.0; }
        break;
        case 9:
            for(int i=0; i<size; i++){ lb[i] = -5.12; }
        break;
        case 10:
            for(int i=0; i<size; i++){ lb[i] = -32.0; }
        break;
        case 11:
            for(int i=0; i<size; i++){ lb[i] = -600.0; }
        break;
    }
}

void Upper_Bounds(int num_fun, int size, double* ub){
    switch(num_fun){
        case 1:
            for(int i=0; i<size; i++){ ub[i] = 100.0; }
        break;
        case 2:
            for(int i=0; i<size; i++){ ub[i] = 10.0; }
        break;
        case 3:
            for(int i=0; i<size; i++){ ub[i] = 100.0; }
        break;
        case 4:
            for(int i=0; i<size; i++){ ub[i] = 100.0; }
        break;
         case 5:
            for(int i=0; i<size; i++){ ub[i] = 30.0; }
        break;
        case 6:
            for(int i=0; i<size; i++){ ub[i] = 100.0; }
        break;
        case 7:
            for(int i=0; i<size; i++){ ub[i] = 1.28; }
        break;
        case 8:
            for(int i=0; i<size; i++){ ub[i] = 500.0; }
        break;
        case 9:
            for(int i=0; i<size; i++){ ub[i] = 5.12; }
        break;
        case 10:
            for(int i=0; i<size; i++){ ub[i] = 32.0; }
        break;
        case 11:
            for(int i=0; i<size; i++){ ub[i] = 600.0; }
        break;
    }
}

int Number_Evaluations(int number_function){
    switch(number_function){
        case 1:
            return 15000;
        break;
        case 2:
            return 20000;
        break;
        case 3:
            return 40000;
        break;
        case 4:
            return 40000;
        break;
        case 5:
            return 40000;
        break;
        case 6:
            return 15000;
        break;
        case 7:
            return 30000;
        break;
        case 8:
            return 40000;
        break;
        case 9:
            return 40000;
        break;
        case 10:
            return 15000;
        break;
        case 11:
            return 20000;
        break;
    }
}
