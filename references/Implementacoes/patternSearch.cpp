void Exploratory_Moves(double delta, Particle *sample, int size, int number_function, double* lb, double* ub){
    if(sample){
        int directions = 2*size;
        double **points = new double*[directions];
        double aux;
        for(int i=0; i<directions; i++){
            points[i] = new double[size];
        }

        bool fail;
        bool exit=false;

        for(int i=0; i<directions; i++){
             for(int j=0; j<size; j++){
                if(i<size){
                    if(i == j){
                        points[i][j] = sample->position[j] + delta;
                    }
                    else{
                        points[i][j] = sample->position[j];
                    }
                }
                else{
                    if((i - j) == size){
                        points[i][j] = sample->position[j] - delta;
                    }
                    else{
                        points[i][j] = sample->position[j];
                    }
                }
            }
        }

        for(int i=0; i<directions; i++){
            fail = false;
            for(int j=0; j<size; j++){
                if(points[i][j] < lb[j] || points[i][j] > ub[j]){
                    fail = true;
                    break;
                }
            }
            if(!fail){
                aux = Compute_Function(points[i], size, number_function); functionEvaluations++;
                if(sample->fitness > aux){
                    sample->fitness = aux;
                    for(int j=0; j<size; j++){
                        sample->position[j] = points[i][j];
                    }
//                    if(success_direction == i){
                        delta = 2*delta;
//                    }
//                    else{
//                        success_direction = i;
//                    }
                    exit = true;
                }
            }
            if(exit)break;
        }

        if(!exit){
//            success_direction = -1;
            delta = 0.5*delta;
        }

        for(int i=0; i<directions; i++){
            delete []points[i];
        }
        delete []points;

    }
    else{
        cout<<"Ponto nulo. Com amor, Pattern Search"<<endl;
    }
}

//weight = initialWeight - (initialWeight - finalWeight)*((double)iterations)/((double)maxIter);
