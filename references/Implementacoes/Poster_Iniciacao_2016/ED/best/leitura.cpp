#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

int main(int argc, char **argv){

    if(argc >= 3){
        int numprob = atoi(argv[1]);
        int numresol = atoi(argv[2]);

        for(int i=0; i<numresol; i++){
//        for(int i=0; i<2; i++){
             ostringstream convert;
             convert<<"N"<<i+1<<".dat";
             string namefile_atual = convert.str();
//              cout<<namefile_atual<<endl;

             ifstream myfile(namefile_atual.c_str());
             if(myfile.is_open()){
                for(int j=0; j<numprob; j++){
//                for(int j=0; j<3; j++){
                    string probname, probvalue;
                    myfile >> probname;
                    myfile >> probvalue;
                    for(int k=0; k<probvalue.size(); k++){
                        if(probvalue[k] == ','){
                            probvalue[k] = '.';
                        }
                    }
                    double aux = atof(probvalue.c_str());
                    aux = fabs(aux);
                    if(aux <= 1E-05){
                        for(int ii=0; ii<numresol; ii++){
                                ostringstream convert2;
                                convert2<<"N"<<ii+1<<".dat";
                                string namefile = convert2.str();
                                fstream file(namefile.c_str());

                                ofstream aux_file;
                                aux_file.open("dataAux.dat");

                                if(file.is_open() && aux_file.is_open()){
                                    string aux_probname, aux_probvalue;
                                    for(int jj=0; jj<numprob; jj++){
                                        file >> aux_probname;
                                        file >> aux_probvalue;

                                        if(j == jj){
                                            ostringstream convert3;
                                            convert3.str("");
                                            convert3.clear();
                                            double aux2 = atof(aux_probvalue.c_str());
//                                            cout<<aux2<<" ";
//                                             int flag = 0;
//                                             if(aux2 < 0) flag = 1;
//                                             aux2 = fabs(aux2);
                                            aux2 += 1.0;
//                                             if(flag == 1) aux2 *= -1;
//                                            cout<<aux2<<endl;
                                            convert3 << aux2;
                                            aux_probvalue = convert3.str();
                                        }
                                        aux_file << aux_probname<<" "<<aux_probvalue<<endl;
                                    }
                                    file.close();
                                    aux_file.close();
                                }

                                file.open(namefile.c_str(), fstream::out | fstream::trunc);
                                ifstream file2("dataAux.dat");

                                if(file2.is_open() && file.is_open()){
                                    string aux_probname, aux_probvalue;
                                    for(int jj=0; jj<numprob && !file2.eof(); jj++){
                                        file2 >> aux_probname;
                                        file2 >> aux_probvalue;

                                      file << aux_probname <<" "<< aux_probvalue << endl;
//                                      cout << aux_probname <<" "<< aux_probvalue << endl;
                                    }
                                    file2.close();
                                    file.close();
                                }

                            }
                        }
                }
             myfile.close();
             }else{
                cout<<"Error reading the data!"<<endl;
             }
        }
    }

//    if(argc == 4){
//        string namefile = argv[1];
//        int numprob = atoi(argv[2]);
//        int numresol= atoi(argv[3]);
//
//        double **mat =new double*[numresol];
//        for(int i=0; i<numresol; i++){
//            mat[i] = new double[numprob];
//        }
//
//        ifstream myfile(namefile.c_str());
//
//
//        if(myfile.is_open()){
//            string aux;
//            for(int i=0; i<numresol; i++){
//             for(int j=0; j<numprob+2; j++){
//                    myfile >> aux;
//                    if(j>0 && j<numprob+1){
//                        aux.erase(0,1);
//                        for(int k=0; k<aux.size(); k++){
//                            if(aux[k] == ','){
//                                aux[k] = '.';
//                            }
//                        }
//                        mat[i][j-1] = atof(aux.c_str());
//                        if(fabs(mat[i][j-1]) <= 1E-04){
//                            mat[i][j-1] += 1.0;
//                        }
//                        cout<<aux<<" j:"<<j<<" "<<mat[i][j-1]<<endl;
//                    }
//                }
//                cout<<endl;
//            }
//        }
//        else{
//            cout<<"Error reading the data!"<<endl;
//        }
//    }

    return 0;
}
