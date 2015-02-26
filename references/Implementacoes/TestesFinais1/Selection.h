#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED

void PlusIsotropic(Individual **progenitor, Individual **progeny, int dimension, int mi, int lambda);
void PlusNonIsotropic(Individual **progenitor, Individual **progeny, int dimension, int mi, int lambda);

#endif // SELECTION_H_INCLUDED
