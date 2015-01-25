#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<cmath>
#include<string.h>
#define PI 3.14159265359
#define EULER 2.71828182845
#define SEED 0
using namespace std;



double Sphere_function(double *x, int size){
//    for(int i=0; i<size; i++){
//        cout<<" >> "<<x[i]<<" ";
//    }
//    cout<<endl;
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i];
    }
//    cout<<" >> "<<(double)fx<<endl;
    return (double)fx;

    /**Best Values*/
    ///return 5.7*Math.pow(10, -4); //FEP
	///return 0.00096;
	///return 0.004073416; //icaris2010
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

    /**Best Values*/
    //return 8.1*Math.pow(10, -3); //FEP
	//return 0.000077;
	//return 0.0002222402; //icaris2010
}

double f03(double *x, int size){
    //TO DO
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

    //return 1.6*Math.pow(10, -2); //FEP
	//return 22000;
	//return 0.00000000000000009781800; //icaris2010
}

double f04(double *x, int size){
    double a, max = abs(x[0]);
    for(int i=1; i<size; i++){
        a = abs(x[i]);
        if(a > max){ max = a; }
    }
    return max;

    //return 0.3; //FEP
	//return 9.44;
	//return 0.00005325212; //icaris2010
}

double f05(double* x, int size){
    double fx = 0.0;
    double a1, a2;
    for(int i=0; i<size-1; i++){
        a1 = (x[i+1] - x[i]*x[i]);
        a2 = (x[i]-1);
        fx += 100.0*(a1*a1) + a2*a2;
    }
    return fx;

    //return 5.06; //avg value from FEP
	//return 27.6; //avg value from Cutello2005
	//return 31.07;
	//return 27.32140; //icaris2010
}

double f06(double* x, int size){
    double sum=0;
    for(int i=0; i<size; i++){
        sum += int(x[i] + 0.5);
    }
    return sum;

    //return 0; //FEP
	//return 0.52;
	//return 0.0; //icaris2010
}

double f07(double* x, int size){
    double sum = 0;
    for(int i=0; i<size; i++){
        sum += (i+1)*x[i]*x[i]*x[i]*x[i];
    }
    return sum + ((rand()-1.0)/RAND_MAX);

    //return 7.6*Math.pow(10, -3); //FEP
	//return 0.13;
	//return 0.005583648; //icaris2010
}

double f08(double* x, int size){
    double sum=0;
    for(int i = 0; i<size; i++){
        sum += -x[i]*sin(sqrt(abs(x[i])));
    }
    return sum;

    //return -12554.5;
	//return -7917.1; //average value found by CEP
	//return -4680.455; //icaris2010
}

double f09(double *x, int size){
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i] - 10.0*cos(2.0*PI*x[i]) + 10.0;
    }
    return fx;

    //return 4.6*Math.pow(10, -2); //FEP
	//return 42.93;
	//return 0.0000000001447365; //icaris2010
}

double f10(double *x, int size){
    double sum1=0, sum2=0;
    for(int i=0; i<size; i++){
        sum1 += x[i]*x[i];
        sum2 += cos(2*PI*x[i]);
    }
    sum1 = sum1/(double)size;
    sum2 = sum2/(double)size;
    return -20.0*exp(-0.2*sqrt(sum1)) - exp(sum2) + 20.0 + EULER;

    //return 1.8*Math.pow(10, -2); //FEP
	//return 18.96;
	//return 0.002172668; //icaris2010
}

double f11(double *x, int size){
    double sum=0, prod=1;
    for(int i = 0; i<size; i++){
        sum += x[i]*x[i];
        prod = prod*cos(x[i]/sqrt(i+1));
    }
    return sum/4000.0 - prod +1.0;

    //return 1.6*Math.pow(10, -2); //FEP
	//return 0.036;
	//return 0.0002537034; //icaris2010
}

double u(double x, double a, double k, double m){
    if(x > a)return k*pow((x-a),m);
    if(x >= -a && x <= a)return 0.0;
    if(x < -a)return k*pow((-x-a), m);
}

double y12(double x){ return (1 + (1/4)*(x + 1)); }

double f12(double *x, int size){
    double sum1=0, sum2=0, aux1 = 0;
    double y[size];
    for(int i=0; i<size; i++){
        y[i] = y12(x[i]);
        sum2 += u(x[i],10,100,4);
    }
    double aux;
    for(int i=0; i<size-1; i++){
        aux = (y[i] - 1);
        sum1 += aux*aux*(1.0 + 10.0*pow(sin(PI*y[i+1]), 2));
    }

    aux = y[size - 1] -1;
    return (PI/size)*(10.0*pow(sin(PI*y[0]), 2) + sum1 + aux*aux) + sum2;

    //return 9.2*Math.pow(10, -6); //FEP
	//return 0.632;
	//return 0.7701294; //icaris2010
}

double f13(double *x, int size){
    double sum1=0, sum2=0, aux1 = 0;

    for(int i=0; i<size; i++){
        sum2 += u(x[i],5,100,4);
    }
    double aux;
    for(int i=0; i<size-1; i++){
        aux = (x[i] - 1);
        sum1 += aux*aux*(1 + pow(sin(3*PI*x[i+1]), 2));
    }

    aux = x[size - 1] -1;
    return (0.1)*(pow(sin(3.0*PI*x[0]), 2) + sum1 + aux*aux*(1.0 + pow(2.0*PI*x[size-1], 2))) + sum2;

    //return 1.6*Math.pow(10, -4); //FEP
	//return 1.83;
	//return 2.857273; //icaris2010
}

double f14(double *x, int size){
    double a[11] = {0.1957, 0.1947, 0.1735, 0.1600, 0.0844, 0.0627, 0.0456, 0.0342, 0.0323, 0.0235, 0.0246};
	double b[11] = {0.25, 0.5, 1, 2, 4, 6, 8, 10, 12, 14, 16};

	for (int i = 0; i < 11; i++) {
	    b[i] = 1/b[i];
	}
	double aux, result = 0;
	for (int i = 0; i < 11; i++) {
	    aux = a[i] - (x[0]*(b[i]*b[i]+b[i]*x[1]))/(b[i]*b[i] + b[i]*x[2] + x[3]);
	    result += aux * aux;
	}
    return result;

    //return 5.0*Math.pow(10, -4); //FEP
	//return 0.0014;
	//return 0.0003913586; //icaris2010
}

void rotate(double *results, double *x, double **A, int size_results){
    for(int i=0; i<size_results; i++){
        results[i] = 0.0;
        for(int j=0; j<size_results; j++){
            results[i] += (x[j]*A[j][i]);
        }
    }
}

void shift(double *results, double *x, double *o, int size_x){
        for(int i=0; i<size_x; i++){
            results[i] = x[i] - o[i];
        }
}
void loadMatriz(string namefile, int row, int colunm, double** M){
    if(M != NULL){
        ifstream matriz;
        string line;
        matriz.open(namefile.c_str());
        if(matriz.is_open()){
            for(int i=0; i<row; i++){
                for(int j=0; j<colunm; j++){
                    matriz >> M[i][j];
                }
            }
        }
    }
    else{cout<<"Problema matriz loadMatriz"<<endl;}
}
double f20(double *x, int size){
    string namefile = "/home/viviane/Área de Trabalho/codigo_cec/supportData";
    double bias = 120.0;
    double sigma[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double lambda[] = {1.0, 1.0, 10.0, 10.0, 5.0/60.0, 5.0/60.0, 5.0/32.0, 5.0/32.0, 5.0/100.0, 5.0/100.0};
    double biases[] = {0.0, 100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0};
    double **o = new double*[5];
    double ***M = new double**[5];
    double *fmax = new double[5];
    double *w = new double[5];
    double **z = new double*[5];
    double **zM = new double*[5];
    double *testPoint = new double[size];
    double *testPointM = new double[size];

    for(int i=0; i<5; i++){
        o[i] = new double[size];
        M[i] = new double*[size];
        z[i] = new double[size];
        zM[i] = new double[size];
    }

}

double f22(double *x, int size){
    double sum = 0.0;

    for(int i=0; i<size-1; i++)}{
        sum += -x[i]*sen(sqrt(fabs(x[i] - (x[i+1] + 47)))) - (x[i+1] + 47)*sen(sqrt(x[i+1] + 47 + (x[i]/2)));
    }

    return sum;
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
        case 12:
            return f12(x, size);
        break;
        case 13:
            return f13(x, size);
        break;
        case 14:
            return f14(x,size);
        break;
        case 22:
            return f22(x,size);
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
        case 12:
            for(int i=0; i<size; i++){ lb[i] = -50.0; }
        break;
        case 13:
            for(int i=0; i<size; i++){ lb[i] = -50.0; }
        break;
        case 14:
            for(int i=0; i<size; i++){ lb[i] = -5.0; }
        break;
        case 22:
            for(int i=0; i<size; i++){ lb[i] = -512.0; }
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
        case 12:
            for(int i=0; i<size; i++){ ub[i] = 50.0; }
        break;
        case 13:
            for(int i=0; i<size; i++){ ub[i] = 50.0; }
        break;
        case 14:
            for(int i=0; i<size; i++){ ub[i] = 5.0; }
        break;
        case 22:
            for(int i=0; i<size; i++){ ub[i] = 512.0; }
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
        case 12:
            return 15000;
        break;
        case 13:
            return 15000;
        break;
        case 14:
            return 40000;
        break;
        case 22:
            return 15000;
        break;
    }
}
