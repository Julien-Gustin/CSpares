#ifndef __MATRICES__
#define __MATRICES__

#define ALLOC 500
#define MAX 70

struct matrice_t{
  unsigned int *P; // Etudiants ( colonne )
  unsigned int *I; // Lignes

};

typedef struct matrice_t MATRICE;

MATRICE fichier_en_matrice(char* input);

#endif
