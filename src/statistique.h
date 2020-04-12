#ifndef __STAT__
#define __STAT__

#include "matrice.h"
/* ------------------------------------------------------------------------- *
 * (9a) Affiche les etudiants en commun d'un cours
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * matriceT         matrice creuse ligne = étudiants, colonnes = cours
 * ------------------------------------------------------------------------- */
void etudiant_commun_cours(MATRICE matrice, MATRICE matriceT);

/* ------------------------------------------------------------------------- *
 * (9a) Affiche les cours en commun d'un étudiant
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * matriceT         matrice creuse ligne = étudiants, colonnes = cours
 * ------------------------------------------------------------------------- */
void cours_commun_etudiant(MATRICE matrice, MATRICE matriceT);


//TODO DOCUMENTATION
void statistique_nbrEleveCours(MATRICE* matrice); // (4)

/* ------------------------------------------------------------------------- *
 * (6b) Affiche le nombres d'eleve de l'annee donnée pour chaque cours
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * annee            annee des etudiants
 * ------------------------------------------------------------------------- */
void stat_cours_annee(MATRICE matrice, unsigned int annee);

/* ------------------------------------------------------------------------- *
 * (6a) Affiche le nombres de filles de chaques cours
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * ------------------------------------------------------------------------- */
void stat_filles_cours(MATRICE matrice);

#endif
