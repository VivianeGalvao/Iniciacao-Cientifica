#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "Avaliation_Function.h"
#include "Estrategias.h"
#include "Solution.h"
#include <string>
#include <sstream>

#define DIMENSAO 30
#define tam_avaliation 1000
#define DELTA 0.7
#define INF 3.40282347E+38F
#define MEDIA_ESPERADA 0.7


using namespace std;

int main(int argc, char** argv)
{
    double *x = new double[DIMENSAO];
    // cout.precision();
    if(argc == 3){
        int funcao = atoi(argv[1]);
        int semente = atoi(argv[2]);

        cout<<funcao<<" ; "<<semente<<" ; "<<DIMENSAO<<";";

        Estrategia::PSO(DIMENSAO, semente, funcao, x);
        cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; ";
        Estrategia::PSOBL(DIMENSAO, semente, INF, funcao, x);
        cout<<Compute_Function(x, DIMENSAO, funcao)<<" ; ";
        cout<<endl;

    }
    else{
        ofstream data, outfile;
        int maxEstrategias = 2;
        int maxFunc = 22;
        int maxSeed = 30;
        double *mean[tam_avaliation];
        outfile.open("outfile");

        for(int i=0; i<tam_avaliation; i++){
            mean[i] = new double[maxEstrategias];
            for(int j=0; j<maxEstrategias; j++){
                mean[i][j] = INF;
            }
        }

        for(int j=0; j<maxFunc; j++){            
		if(j==16)j++;
		cout<<"Function: "<<j+1<<" ; ";
            double maxIt = -INF, minIt = INF;
            ostringstream convert;
            convert<<"Data"<<j+1<<".txt";
            data.open(convert.str());
            for(int k=0; k<=maxSeed; k++){
		cout<<"Seed: "<<k<<endl;
                Estrategia::PSOBL(DIMENSAO, k, INF, j+1, x);
                Estrategia::PSO(DIMENSAO, k, j+1, x);

                for(int i=0; i<maxEstrategias; i++){
                    if( maxIt < Estrategia::iterations[i]) maxIt = Estrategia::iterations[i];
                    if( minIt > Estrategia::iterations[i]) minIt = Estrategia::iterations[i];
                    for(int t=0; t<Estrategia::iterations[i]; t++){
                            if(k == 0){
                                mean[t][i] = Estrategia::sampling[i][t]/maxSeed;
                            }
                            else{
                                mean[t][i] += Estrategia::sampling[i][t]/maxSeed;
                            }
                    }
                }
            }
            double ymax = -INF, ymin = INF;
            for(int i=0; i<maxEstrategias; i++){
                if(ymax < mean[0][i]){
                    ymax = mean[0][i];
                }
                if(ymin > mean[(int)maxIt-1][i]){
                    ymin = mean[(int)maxIt-1][i];
                }

                if(ymin > mean[(int)minIt-1][i]){
                    ymin = mean[(int)minIt-1][i];
                }
            }

            outfile<<"set size 1,1 \nset key outside \nset grid \nset xrange [0:"<<maxIt<<"] \nset yrange ["<<ymin<<":"<<100<<"] \n";
            outfile<<"set title \"Function"<<j+1<<"\" \n";
            outfile<<"set xlabel \"x\" \nset ylabel \"f(x)\" \n";
            outfile<<"plot \"Data"<<j+1<<".txt\" u 1:2 t \"Estrategy 1\" with lines \n";
            for(int t=3; t<=maxEstrategias+1; t++){
                outfile<<"replot \"Data"<<j+1<<".txt\" u 1:"<<t<<" t \"Estrategy "<<t-1<<"\" with lines\n";
            }
            outfile<<"set terminal png \nset output \'GraficoFunction"<<j+1<<".png\' \n";
            outfile<<"replot \n";

            for(int t=0; t<maxIt; t++){
                data<<t+1<<"\t";
                for(int i=0; i<maxEstrategias; i++){
                    if(mean[t][i] < INF){
                        data<<mean[t][i]<<"\t";
                    }
                    else{
                        data<<"\t"<<"\t";
                    }
                }
                data<<endl;
            }

            data.close();
        }

        outfile.close();
    }

    delete []x;
    return 0;
}

