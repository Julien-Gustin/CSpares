#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "matrice.h"
#include "produit.h"

int main(){

  char input[] = "cursusAnonyme.csv";
  clock_t t1, t2, t3, t4, t5, t6, t7, t8;
  float temps, temps2, temps3;

  t1 = clock();
  MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
  t2 = clock();
  MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments

  t3 = clock();
  statistique(&matrice);
  t4 = clock();

  t5 = clock();
  MATRICE d = produit_matrice_creuses(&matrice, &matriceT);
  //etudiant_commun_cours(matrice, matriceT);
  //cours_commun_etudiant(matrice, matriceT);
  t6 = clock();


  /* Partie Valeur propre */

   t7 =  clock();
   double *v = valeur_propre(&d);
   if(!v)
      return 0;
   t8 = clock();
   free(v);


   //
   // trice(&c);





   // return 0;


  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  temps2 = (float)(t4-t3)/CLOCKS_PER_SEC;
  temps3 = (float)(t6-t5)/CLOCKS_PER_SEC;
  double temps8 = (float)(t8-t7)/CLOCKS_PER_SEC;
  printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n | durée de l'exécution = %f secondes pour la troisieme fonction\n", temps, temps2, temps3);
  printf(" Durée vecteur propre %f\n", temps8);


   destroy_fichier(&matrice);
   destroy_matrice(&matrice);
   destroy_matrice(&d);
   destroy_matrice(&matriceT);

}
