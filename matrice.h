#ifndef __MATRICES__
#define __MATRICES__

#define MAX 9
#define MAX_LIGNES 80

struct matrice_t{
  unsigned int *P; // Etudiants ( colonne )
  unsigned int *I; //
  unsigned int *X;
  char (*cours)[MAX];
  char (*coursDif)[MAX];
  unsigned int *matricules;
  size_t nbrLignes;
};

typedef struct matrice_t MATRICE;

MATRICE fichier_en_matrice(char* input); // O(4n) + O(2n(log(n))

//MATRICE transposee_matrice(MATRICE matrice);

#endif
