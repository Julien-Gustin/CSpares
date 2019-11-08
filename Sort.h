/* ========================================================================= *
 * Sort
 * ========================================================================= */

#ifndef _SORT_H_
#define _SORT_H_

#include <stddef.h>
#include "matrice.h"


/* ------------------------------------------------------------------------- *
 * Trie un tableau d'entier.
 *
 * PARAMETRES
 * array        Le tableau à trier
 * length       Nombres d'éléments du tableau
 * ------------------------------------------------------------------------- */
void sort(unsigned int* array, char (*cours)[MAX], size_t length);

/* ------------------------------------------------------------------------- *
 * Trie un tableau d'entier.
 *
 * PARAMETRES
 * array        Le tableau à trier
 * length       Nombres d'éléments du tableau
 * ------------------------------------------------------------------------- */
void sort_string(unsigned int* array, char (*cours)[MAX], size_t length);


#endif // !_SORT_H_
