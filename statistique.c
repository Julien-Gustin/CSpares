#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "matrice.h"
#include "Sort.h"
#include "vecteur.h"
#include "statistique.h"

void etudiant_commun_cours(MATRICE matrice, MATRICE matriceT){
  MATRICE resultat = produit_matrice_creuses(&matriceT, &matrice);;

  for(size_t i = 0; i < resultat.nbrColonnes; i++){
    if(i != resultat.nbrColonnes-1){
      for(size_t j = resultat.P[i]; j < resultat.P[i+1]; j++){
        if(resultat.I[j] != i)
          printf("étudiants %u à %u cours en commun avec %u\n", matrice.fichier.matricules[matrice.P[i]], resultat.X[j], resultat.fichier.matricules[matrice.P[resultat.I[j]]]);
      }
  }
    else{
      for(size_t j = resultat.P[i]; j < resultat.nz; j++){
        if(resultat.I[j] != i)
          printf("étudiants %u à %u cours en commun avec %u\n", matrice.fichier.matricules[matrice.P[i]], resultat.X[j], resultat.fichier.matricules[matrice.P[resultat.I[j]]]);
      }
    }
  }
  destroy_matrice(&resultat);
}

void cours_commun_etudiant(MATRICE matrice, MATRICE matriceT){
  MATRICE resultat = produit_matrice_creuses(&matrice, &matriceT);;

  for(size_t i = 0; i < resultat.nbrColonnes; i++){
    if(i != resultat.nbrColonnes-1){
      for(size_t j = resultat.P[i]; j < resultat.P[i+1]; j++){
        if(resultat.I[j] != i)
          printf("le cours %s à %u eleve en commun avec le cours %s\n", matrice.fichier.coursDif[i], resultat.X[j], resultat.fichier.coursDif[resultat.I[j]]);
      }
  }
    else{
      for(size_t j = resultat.P[i]; j < resultat.nz; j++){
        if(resultat.I[j] != i) // > pour éviter doublon
          printf("le cours %s à %u eleve en commun avec le cours %s\n", matrice.fichier.coursDif[i], resultat.X[j], resultat.fichier.coursDif[resultat.I[j]]);
      }
    }
  }
  destroy_matrice(&resultat);
}

void statistique_nbrEleveCours(MATRICE* matrice) {

   double *vecteur1 = malloc(sizeof(double)* matrice->nbrColonnes);
   if(!vecteur1) {
      fprintf(stderr, "Erreur lors de l'allocation!\n");
      exit(EXIT_FAILURE);
   }

   /* Remplir le vecteur de 1 */
   for(size_t k = 0; k < matrice->nbrColonnes; ++k)
      vecteur1[k] = 1;

   double *resultat =
      matrice_vecteurs_dense( matrice, vecteur1, matrice->nbrColonnes);

   if(!resultat)
      exit(EXIT_FAILURE);

   /* Utilisons notre dictionnaire */

   printf("Nombre d'étudiants qui suivent le cours de:\n");
   for(size_t k = 0; k < matrice->nbrLignes; ++k)
      printf("%s:  %.0f\n", matrice->fichier.coursDif[k], resultat[k]);

   free(vecteur1);
   free(resultat);
}

void stat_filles_cours(MATRICE matrice){
  VECTEUR filles; // vecteur
  unsigned int nbrFilles = 0;

  // comptes le nombres filles du fichier ( nombres impair )
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
    if((matrice.fichier.matricules[matrice.P[i]] % 2) != 0){
      nbrFilles++;
    }
  }

  if(nbrFilles == 0){
    printf("Aucune fille");
    return;
  }

  filles.I = malloc(sizeof(unsigned int) *nbrFilles);
  if(filles.I == NULL)
    return;

  filles.X = malloc(nbrFilles *sizeof(unsigned int));
  if(filles.X ==  NULL)
    return;

  for(size_t i = 0; i < nbrFilles; i++)
    filles.X[i] = 1;

  filles.nbrNonZero = nbrFilles;
  filles.sommeTot = 0;
  filles.Xtmp = calloc(matrice.nbrLignes, sizeof(unsigned int));

  size_t k = 0;

  //stocke l'indice des matricules impair
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
    if((matrice.fichier.matricules[matrice.P[i]] % 2) != 0){
      filles.I[k] = i;
      k++;
    }
  }

  VECTEUR resultat = mult_matrice_vecteurs_creux(matrice, filles);

  for(size_t i = 0; i < resultat.nbrNonZero; i++) // Le printf prends du temps, pour la demo montrer sans printf
    printf("%s filles :%u\n", matrice.fichier.coursDif[resultat.I[i]], resultat.X[i]);

  destroy_vecteur(&resultat);
  destroy_vecteur(&filles);

}

void stat_cours_annee(MATRICE matrice, unsigned int annee){
  VECTEUR eleveAnnee;
  unsigned int nbrELeveAnnee = 0;
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
    if(!((matrice.fichier.matricules[matrice.P[i]]/10000) % annee)){
      nbrELeveAnnee++;
    }
  }

  if(nbrELeveAnnee == 0){
    printf("Aucun éléve de %u\n", annee);
    return;
  }

  eleveAnnee.I = malloc(sizeof(unsigned int)*nbrELeveAnnee);
  if(eleveAnnee.I == NULL)
    return;

  eleveAnnee.X = malloc(sizeof(unsigned int) *nbrELeveAnnee);
  if(eleveAnnee.X == NULL)
    return;

  for(size_t i = 0; i < nbrELeveAnnee; i++)
    eleveAnnee.X[i] = 1;

  eleveAnnee.nbrNonZero = nbrELeveAnnee;
  eleveAnnee.sommeTot = 0;
  eleveAnnee.Xtmp = calloc(matrice.nbrLignes, sizeof(unsigned int));

  size_t k = 0;
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
    if(!((matrice.fichier.matricules[matrice.P[i]]/10000) % annee)){
      eleveAnnee.I[k] = i;
      k++;
    }
  }

  VECTEUR resultat = mult_matrice_vecteurs_creux(matrice, eleveAnnee);

  for(size_t i = 0; i < resultat.nbrNonZero; i++) // Le printf prends du temps, pour la demo montrer sans printf
    printf("%s annee :%d :%u\n", matrice.fichier.coursDif[resultat.I[i]], annee, resultat.X[i]);

  destroy_vecteur(&resultat);
  destroy_vecteur(&eleveAnnee);

}
