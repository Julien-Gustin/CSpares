#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "statistique.h"
#include "matrice.h"
#include "vecteur.h"

int main(){

  //TODO, complexité de chacune des fonctions

  char input[] = "cursusAnonyme.csv";
  clock_t t1, t2, t3, t4, t9, t10, t11, t12, t13, t14, t17, t18, t19, t20;
  // clock_t t15 t5, t6, t7, t8, t16;

  t1 = clock(); // fonction 1
  MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
  t2 = clock();

  t3 = clock(); // fonction 2
  MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
  t4 = clock();

  // t5 = clock(); //fonction 3 TODO
  // t6 = clock();

  // t7 = clock(); //fonction 4 TODO
  // t8 = clock();

  t9 = clock(); // fonction 6a qui utilise la 5
  stat_filles_cours(matrice); // filles, essayer sans le printf
  t10 = clock();

  t11 = clock(); // fonction 6b qui utilise la 5
  stat_cours_annee(matrice, 2008); // année, essayer sans le printf
  t12 = clock();

  t13 = clock(); // fonction 7
  MATRICE test = produit_matrice_creuses(&matrice, &matriceT);
  t14 = clock();

  // t15 = clock(); // fonction 8 TODO
  // MATRICE test = produit_matrice_creuses(matrice, matriceT);
  // t16 = clock();

  t17 = clock(); // fonction 9a
  cours_commun_etudiant(matrice, matriceT); //essayer sans printf
  t18 = clock();

  t19 = clock(); // fonction 9b
  etudiant_commun_cours(matrice, matriceT); // essayer sans printf
  t20 = clock();

  // t21 = clock(); // fonction 20 TODO
  // t22 = clock();

  //
  // t3 = clock();
  // stat_filles_cours(matrice);
  // t4 = clock();
  //
  // t5 = clock();
  // MATRICE d = produit_matrice_creuses(&matrice, &matriceT);
  // //etudiant_commun_cours(matrice, matriceT);
  // //cours_commun_etudiant(matrice, matriceT);
  // t6 = clock();
  //
  //
  // /* Partie Valeur propre */
  //
  //  t7 =  clock();
  //  double *v = valeur_propre(&d);
  //  if(!v)
  //     return 0;
  //  t8 = clock();
  //  free(v);
  //
  //
  //  //
  //  // trice(&c);
  //
  //
  //
  //
  //
  //  // return 0;
  //
  //
  // temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  // temps2 = (float)(t4-t3)/CLOCKS_PER_SEC;
  // temps3 = (float)(t6-t5)/CLOCKS_PER_SEC;
  // double temps8 = (float)(t8-t7)/CLOCKS_PER_SEC;
  // printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n | durée de l'exécution = %f secondes pour la troisieme fonction\n", temps, temps2, temps3);
  // printf(" Durée vecteur propre %f\n", temps8);
  //
  //
  //  destroy_fichier(&matrice);
  //  destroy_matrice(&matrice);
  //  destroy_matrice(&d);
  //  destroy_matrice(&matriceT);

  printf(" | durée de l'exécution = %f secondes pour la première fonction\n", (float)(t2-t1)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la deuxième fonction\n", (float)(t4-t3)/CLOCKS_PER_SEC);
  // printf(" | durée de l'exécution = %f secondes pour la troisieme fonction\n", (float)(t6-t5)/CLOCKS_PER_SEC);
  // printf(" | durée de l'exécution = %f secondes pour la quatrième fonction\n", (float)(t8-t7)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la sixièmeA fonction\n", (float)(t10-t9)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la sixièmeB fonction\n", (float)(t12-t11)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la septième fonction\n", (float)(t14-t13)/CLOCKS_PER_SEC);
  // printf(" | durée de l'exécution = %f secondes pour la huitième fonction\n", (float)(t16-t15)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la neuvièmeA fonction\n", (float)(t18-t17)/CLOCKS_PER_SEC);
  printf(" | durée de l'exécution = %f secondes pour la neuvièmeB fonction\n", (float)(t20-t19)/CLOCKS_PER_SEC);

  destroy_fichier(&matrice);
  destroy_matrice(&matrice);
  destroy_matrice(&matriceT);
  destroy_matrice(&test);

}
