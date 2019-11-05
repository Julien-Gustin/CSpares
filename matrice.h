#ifndef __MATRICES__
#define __MATRICES__

#define ALLOC 100
#define MAX 70

struct matrice_t{
  unsigned int *P;
  unsigned int *I;

};

typedef struct matrice_t MATRICE;

MATRICE fichier_en_matrice(char* input);

#endif
