#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

class Individual{
    public:
        double *position;
        double objective_function;
     //   double fitness;
        double standard_deviation;
      //  double size_step;
        Individual(){}
        ~Individual(){}
};

class Particle{
    public:
        double *position;
        double *best_position;
        double *velocity;
        double fitness;
        double best_fitness;
        Particle(){}
        ~Particle(){}
};

#endif // SOLUTION_H_INCLUDED
