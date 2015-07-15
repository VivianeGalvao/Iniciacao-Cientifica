#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <string>
#include <sstream>
#include <cfloat>
#define PI 3.14159265359
#define EULER 2.71828182845
#define SEED 0
using namespace std;



double Sphere_function(double *x, int size){
    double fx=0.0;
    for(int i=0; i<size; i++){
        fx += x[i]*x[i];
    }

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
        fx += x[i]*x[i] - 10.0*cos(2.0*PI*x[i]);
    }
    return fx + ((double)10*size);

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
        sum += (x[i]*x[i])/4000.0;
        prod = prod*cos(x[i]/sqrt(i+1));
    }
    return sum - prod +1.0;

    //return 1.6*Math.pow(10, -2); //FEP
	//return 0.036;
	//return 0.0002537034; //icaris2010
}

double u(double x, double a, double k, double m){
    if(x > a)return k*pow((x-a),m);
    if(x >= -a && x <= a)return 0.0;
    if(x < -a)return k*pow((-x-a), m);
    else return NAN;
}

double y12(double x){ return (1 + (1/4)*(x + 1)); }

double f12(double *x, int size){
    double sum1=0, sum2=0;
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
    double sum1=0, sum2=0;

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

double f15(double *x, int size){
     double a[4][6] = {{10,3,17,3.5,1.7,8}, {0.05,10,17,0.1,8,14}, {3,3.5,1.7,10,17,8}, {17,8,0.05,10,14}};
     double c[4] = {1, 1.2, 3, 3.2};
     double p[4][6] ={{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886}, {0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
                {0.2348, 0.1415, 0.3522, 0.2883, 0.3047, 0.6650}, {0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
     double sum=0, aux=0;

     for(int i=0; i<4; i++){
        for(int j=0; j<6; j++){
            aux+=a[i][j]*(x[j] - p[i][j])*(x[j] - p[i][j]);
        }
        sum += c[i]*exp(-aux);
     }

     return -sum;
}

double vectorProduct(double a[], double b[], int tam){
    double sum=0;
    for(int i=0; i<tam; i++){
        sum += a[i]*b[i];
    }
    return sum;
}

double f16(double *x, int size){
    double a[10][4] = {{4,4,4,4}, {1,1,1,1}, {8,8,8,8}, {6,6,6,6}, {3,7,3,7}, {2,9,2,9}, {5,5,3,3}, {8,1,8,1}, {6,2,6,2}, {7,3.6,7,3.6,}};
    double c[10] = {0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3, 0.7, 0.5, 0.5};
    double aux = 0;
    for(int i=0; i<10; i++){
        aux += 1/(vectorProduct(a[i], a[i], 4) + c[i]);
    }

    return -aux;
}

double ScafferF6(double x, double y) {
	double temp1 = x*x + y*y;
	double temp2 = sin(sqrt(fabs(temp1)));
	double temp3 = 1.0 + 0.001 * temp1;
	return (0.5 + ((temp2 * temp2 - 0.5)/(temp3 * temp3)));
}

double EScafferF6(double* x, int size) {
		double sum = 0.0;
		for (int i = 0 ; i < size-1 ; i ++) {
			sum += ScafferF6(x[i], x[i+1]);
		}
		sum += ScafferF6(x[size-1], x[0]);
		return (sum);
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

void loadVector(string namefile, int row, double *v){
    if(v != NULL){
        ifstream vetor;
        vetor.open(namefile.c_str());
        if(vetor.is_open()){
            float aux = 0.0;
            for(int i=0; i<row; i++){
                vetor >> aux;
                v[i] = aux;
            }
        }
    }else{
        cout<<"Problema vetor leitura loadVector"<<endl;
    }
}

void loadMatriz(string namefile, int row, int colunm, double** M){
    if(M != NULL){
        ifstream matriz;
        matriz.open(namefile.c_str());
        if(matriz.is_open()){
            double aux = 0.0;
            for(int i=0; i<row; i++){
                if(M[i] != NULL){
                    for(int j=0; j<colunm; j++){
                        matriz >> aux;
                        M[i][j] = (double)aux;
//                        M[i][j] = 0.0;
                    }
                }else{cout<<"Problema matriz linha nula loadMatriz";}
            }
        }
        matriz.close();
    }
    else{cout<<"Problema matriz loadMatriz"<<endl;}
}

double f17(double *x, int size){
    ostringstream convert;
    convert<<"/home/viviane/Área de Trabalho/codigo_cec/supportData/elliptic_M_D"<<size<<".txt";
    string namefileMatrix = convert.str();
    string namefileVector = "/home/viviane/Área de Trabalho/codigo_cec/supportData/high_cond_elliptic_rot_data.txt";

    double bias = -450;

    double *o = new double[size];
    double **M = new double*[size];
    double *z = new double[size];
    double *zM = new double[size];
    for(int i=0; i<size; i++){
        M[i] = new double[size];
    }
    double constante = pow(1000000.0, 1.0/(size-1.0));

    loadVector(namefileVector, size, o);
    loadMatriz(namefileMatrix, size, size, M);

    shift(z, x, o, size);
    rotate(zM, z, M, size);

    double sum = 0.0;

    for (int i = 0 ; i < size ; i ++) {
        sum += pow(constante, i) * zM[i] * zM[i];
    }

    for(int i=0; i<size; i++){
        delete []M[i];
    }

    delete []o;
    delete []M;
    delete []z;
    delete []zM;

    return sum + bias;
}

double f18(double *x, int size){
    ostringstream convert;
    convert<<"codigo_cec/supportData/E_ScafferF6_M_D"<<size<<".txt";
    string namefileMatrix = convert.str();
    string namefileVector = "codigo_cec/supportData/E_ScafferF6_func_data.txt";

    double *o = new double[size];
    double **M = new double*[size];
    double *z = new double[size];
    double *zM = new double[size];

    for(int i=0; i<size; i++){
        M[i] = new double[size];
    }

    double bias = -300;

    loadVector(namefileVector, size, o);
    loadMatriz(namefileMatrix, size, size, M);

    shift(z, x, o, size);
    rotate(zM, z, M, size);

    double result = EScafferF6(zM, size);


    for(int i=0; i<size; i++){
        delete []M[i];
    }

    delete []o;
    delete []M;
    delete []z;
    delete []zM;

    return result + bias;
}

void loadMatriz_21(string namefile, int a, int b, int c, double ***M){
    if(M != NULL){
        ifstream matriz;
        matriz.open(namefile.c_str());
        if(matriz.is_open()){
            for(int i=0; i<a; i++){
                loadMatriz(namefile, b, c, M[i]);
            }
        }else{ cout<<"arquivo nao pode ser aberto"<<endl; }
    }
    else{
        cout<<"Problema matriz loadMatriz_21"<<endl;
    }

}

double weierstrass(double* x, int size) {
        double a = 0.5, b = 3.0;
        int Kmax = 20;
		double sum1 = 0.0;
		for (int i = 0 ; i < size ; i ++) {
			for (int k = 0 ; k <= Kmax ; k ++) {
				sum1 += pow(a, k) * cos(PI*2 * pow(b, k) * (x[i] + 0.5));
			}
		}

		double sum2 = 0.0;
		for (int k = 0 ; k <= Kmax ; k ++) {
			sum2 += pow(a, k) * cos(PI*2 * pow(b, k) * (0.5));
		}

		return (sum1 - sum2*((double )(size)));
}

double F2(double x, double y) {
    double temp1 = (x * x) - y;
	double temp2 = x - 1.0;
	return ((100.0 * temp1 * temp1) + (temp2 * temp2));
}

double F8(double x) {
	return (((x * x) / 4000.0) - cos(x) + 1.0);
}

double F8F2(double* x, int size) {
		double sum = 0.0;
		for (int i = 1 ; i < size ; i ++) {
			sum += F8(F2(x[i-1], x[i]));
		}
		sum += F8(F2(x[size-1], x[0]));
		return sum;
}

double signum(double x){
    if(x == 0){ return 0; }
    else{
        if(x > 0){ return 1;}
        else{ return -1; }
    }
}

double myRound(double x) {
	return (signum(x) * round(fabs(x)));
}

double myXRound(double x, double o) {
		return ((fabs(x - o) < 0.5) ? x : (myRound(2.0 * x) / 2.0));
}

double basic_func20(int i, double *test, int size){
    switch(i){
        case 0:
            return f09(test, size);
        break;
        case 1:
            return weierstrass(test, size);
        break;
        case 2:
            return f11(test, size);
        break;
        case 3:
            return f10(test, size);
        break;
        case 4:
            return Sphere_function(test, size);
        break;
    }
    return NAN;
}

double basic_func21(int i, double *test, int size){
    switch(i){
        case 0:
            return EScafferF6(test, size);
        break;
        case 1:
            return f09(test, size);
        break;
        case 2:
            return F8F2(test, size);
        break;
        case 3:
            return weierstrass(test, size);
        break;
        case 4:
            return f11(test, size);
        break;
    }
    return NAN;
}

double f19(double *x, int size){
    string namefile = "codigo_cec/supportData/hybrid_func1_data.txt";
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
    for(int i=0; i<5; i++){
        for(int j=0; j<size; j++){
            M[i][j] = new double[size];
        }
    }
    loadMatriz(namefile, 5, size, o);
    for (int i = 0 ; i < 5 ; i ++) {
			for (int j = 0 ; j < size ; j ++) {
				for (int k = 0 ; k < size ; k ++) {
					M[i][j][k] = 0.0;
				}
			}
			for (int j = 0 ; j < size ; j ++) {
				M[i][j][j] = 1.0;
			}
    }
    double C = 2000.0;

    for (int i = 0 ; i < 5 ; i ++) {
			for (int j = 0 ; j < size ; j ++) {
				testPoint[j] = (5.0 / lambda[i]);
			}
			rotate(testPointM, testPoint, M[i], size);
			fmax[i] = fabs(basic_func20(i, testPointM, size));
    }

    double wMax = -FLT_MAX;
    for (int i = 0 ; i < 5 ; i ++) {
			double sumSqr = 0.0;
			shift(z[i], x, o[i], size);
			for (int j = 0 ; j < size ; j ++) {
				sumSqr += (z[i][j] * z[i][j]);
			}
			w[i] = exp(-1.0 * sumSqr / (2.0 * size * sigma[i] * sigma[i]));
			if (wMax < w[i]){
				wMax = w[i];
			}
    }

    double wSum = 0.0;
    double w1mMaxPow = 1.0 - pow(wMax, 10.0);
    for (int i = 0 ; i < 5 ; i ++) {
        if (w[i] != wMax) {
            w[i] *= w1mMaxPow;
        }
        wSum += w[i];
	}
    for (int i = 0 ; i < 5 ; i ++) {
			w[i] /= wSum;
    }

    double sumF = 0.0;
    for (int i = 0 ; i < 5 ; i ++) {
        for (int j = 0 ; j < size ; j ++) {
            z[i][j] /= lambda[i];
        }
        rotate(zM[i], z[i], M[i], size);
        sumF += w[i]*(C * basic_func20(i,zM[i], size) / fmax[i] + biases[i]);
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<size; j++){
            delete []M[i][j];
        }
    }

    for(int i=0; i<5; i++){
        delete []o[i];
        delete []M[i];
        delete []z[i];
        delete []zM[i];
    }

    delete []o;
    delete []M;
    delete []fmax;
    delete []w;
    delete []z;
    delete []zM;
    delete []testPoint;
    delete []testPointM;

	return sumF + bias;
}

double f20(double* x, int size){
    ostringstream convert;
    convert<<"codigo_cec/supportData/hybrid_func3_M_D"<<size<<".txt";
    string filename = "codigo_cec/supportData/hybrid_func3_data.txt";
    string filenameM = convert.str();
    double bias = 360;
    double sigma[] = {
		1.0,	1.0,	1.0,	1.0,	1.0,
		2.0,	2.0,	2.0,	2.0,	2.0
	};
	double lambda[] = {
		5.0*5.0/100.0,	5.0/100.0,	5.0*1.0,	1.0,			5.0*1.0,
		1.0,			5.0*10.0,	10.0,		5.0*5.0/200.0,	5.0/200.0
	};
	double biases[] = {
		0.0,	100.0,	200.0,	300.0,	400.0,
		500.0,	600.0,	700.0,	800.0,	900.0
	};
    double **o = new double*[5];
    double ***M = new double**[5];
    double *testPoint = new double[size];
    double *testPointM = new double[size];
    double *fmax = new double[5];
    double *w = new double[5];
    double **z = new double*[5];
    double **zM = new double*[5];

    for(int i=0; i<5; i++){
        o[i] = new double[size];
        M[i] = new double*[size];
        z[i] = new double[size];
        zM[i] = new double[size];
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<size; j++){
            M[i][j] = new double[size];
        }
    }

    loadMatriz(filename, 5, size, o);
    loadMatriz_21(filenameM, 5, size, size, M);

    double C = 2000.0;

    for (int i = 0 ; i < 5 ; i ++) {
        for (int j = 0 ; j < size ; j ++) {
            testPoint[j] = (5.0 / lambda[i]);
        }
        rotate(testPointM, testPoint, M[i], size);
        fmax[i] = fabs(basic_func21(i, testPointM, size));
    }

    double* newX = new double[size];

    for (int i = 0 ; i < size ; i ++) {
        newX[i] = myXRound(x[i], o[0][i]);
    }

    double wMax = -FLT_MAX;
    for (int i = 0 ; i < 5 ; i ++) {
			double sumSqr = 0.0;
			shift(z[i], x, o[i], size);
			for (int j = 0 ; j < size ; j ++) {
				sumSqr += (z[i][j] * z[i][j]);
			}
			w[i] = exp(-1.0 * sumSqr / (2.0 * size * sigma[i] * sigma[i]));
			if (wMax < w[i]){
				wMax = w[i];
			}
    }

    double wSum = 0.0;
    double w1mMaxPow = 1.0 - pow(wMax, 10.0);
    for (int i = 0 ; i < 5 ; i ++) {
        if (w[i] != wMax) {
            w[i] *= w1mMaxPow;
        }
        wSum += w[i];
	}
    for (int i = 0 ; i < 5 ; i ++) {
			w[i] /= wSum;
    }

    double sumF = 0.0;
    for (int i = 0 ; i < 5 ; i ++) {
        for (int j = 0 ; j < size ; j ++) {
            z[i][j] /= lambda[i];
        }
        rotate(zM[i], z[i], M[i], size);
        sumF += w[i]*(C * basic_func21(i,zM[i], size) / fmax[i] + biases[i]);
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<size; j++){
            delete []M[i][j];
        }
    }

    for(int i=0; i<5; i++){
        delete []o[i];
        delete []M[i];
        delete []z[i];
        delete []zM[i];
    }

    delete []o;
    delete []newX;
    delete []M;
    delete []fmax;
    delete []w;
    delete []z;
    delete []zM;
    delete []testPoint;
    delete []testPointM;

    return sumF + bias;
}

double f21(double *x, int size){
    double sum = 0.0;

    for(int i=0; i<size-1; i++){
        sum += -x[i]*sin(sqrt(fabs(x[i] - (x[i+1] + 47)))) - (x[i+1] + 47)*sin(sqrt(fabs(x[i+1] + 47 + (x[i]/2))));
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
        case 15:
            return f15(x,size);
        break;
        case 16:
            return f16(x,size);
        break;
        case 17:
            return f17(x,size);
        break;
        case 18:
            return f18(x,size);
        break;
        case 19:
            return f19(x,size);
        break;
        case 20:
            return f20(x,size);
        break;
        case 21:
            return f21(x,size);
        break;
    }
    return -1;
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
        case 15:
            for(int i=0; i<size; i++){ lb[i] = 0.0; }
        break;
        case 16:
            for(int i=0; i<size; i++){ lb[i] = 0.0; }
        break;
        case 17:
            for(int i=0; i<size; i++){ lb[i] = -100.0;}
        break;
        case 18:
            for(int i=0; i<size; i++){ lb[i] = -100.0;}
        break;
        case 19:
            for(int i=0; i<size; i++){ lb[i] = -5.0; }
        break;
        case 20:
            for(int i=0; i<size; i++){ lb[i] = -5.0; }
        break;
        case 21:
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
        case 15:
            for(int i=0; i<size; i++){ ub[i] = 1.0; }
        break;
        case 16:
            for(int i=0; i<size; i++){ ub[i] = 10.0; }
        break;
        case 17:
            for(int i=0; i<size; i++){ ub[i] = 100.0;}
        break;
        case 18:
            for(int i=0; i<size; i++){ ub[i] = 100.0;}
        break;
        case 19:
            for(int i=0; i<size; i++){ ub[i] = 5.0; }
        break;
        case 20:
            for(int i=0; i<size; i++){ ub[i] = 5.0; }
        break;
        case 21:
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
        case 15:
            return 2000;
        break;
        case 16:
            return 1000;
        break;
        case 17:
            return 30000;
        break;
        case 18:
            return 30000;
        break;
        case 19:
            return 30000;
        break;
        case 20:
            return 30000;
        break;
        case 21:
            return 15000;
        break;
    }
    return 0;
}
