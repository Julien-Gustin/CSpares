#ifndef __PRODUIT__
#define __PRODUIT__

#include "matrice.h"

/* Renvoie un pointeur sur le resultats */
/* Ne pas oublier de free le vecteur ensuite */
int *matrice_vecteurs_dense(MATRICE *s, int *v, const size_t N);



#endif
