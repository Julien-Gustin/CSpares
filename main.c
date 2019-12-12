#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "statistique.h"
#include "matrice.h"
#include "vecteur.h"


static inline void purge(void)
{
   char c;
   while((c=getchar()) != '\n' && c != EOF)
   {}
}


int main(){

  //TODO, complexité de chacune des fonctions

  char input[] = "cursusAnonyme.csv";
  clock_t t1 = 0, t2 = 0;
  int choix = 0;
  char s = 0;
  do {

   if(system("clear") == -1)
      return 1;
   printf("Entrez le numéro de la questions : [1, 2, 4, 6, 7, 9, 10]\n");
   if(scanf("%d", &choix) != 1) return 0;
   purge();
   switch (choix) {
   case 1:
   {
      t1 = clock(); // fonction 1
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
      t2 = clock();
      printf("Temps d'exécution de la fonction %d est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      break;
   }
   case 2:
   {
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes

      t1 = clock(); // fonction 2
      MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
      t2 = clock();
      printf("Temps d'exécution de la fonction %d est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      destroy_matrice(&matriceT);
      break;
   }
   case 4:
   {
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes

      t1 = clock(); //fonction 4 TODO
      statistique_nbrEleveCours(&matrice);
      t2 = clock();
      printf("Temps d'exécution de la fonction %d est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      break;
   }
   case 6:
   {
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes

      t1 = clock(); // fonction 6a qui utilise la 5
      stat_filles_cours(matrice); // filles, essayer sans le printf
      t2 = clock();
      printf("Temps d'exécution de la fonction %dA est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      t1 = clock(); // fonction 6b qui utilise la 5
      stat_cours_annee(matrice, 2008); // année, essayer sans le printf
      t2 = clock();
      printf("Temps d'exécution de la fonction %dB est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);


      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      break;
   }
   case 7:
   {
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
      MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments

      t1 = clock(); // fonction 7
      MATRICE test = produit_matrice_creuses(&matrice, &matriceT);
      t2 = clock();
      printf("Temps d'exécution de la fonction %d est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      destroy_matrice(&test);
      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      destroy_matrice(&matriceT);
      break;
   }
   case 9:
   {
      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
      MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
      t1 = clock(); // fonction 9a
      cours_commun_etudiant(matrice, matriceT); //essayer sans printf
      t2 = clock();
      printf("Temps d'exécution de la fonction %dA est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      t1 = clock(); // fonction 9b
      etudiant_commun_cours(matrice, matriceT); // essayer sans printf
      t2 = clock();
      printf("Temps d'exécution de la fonction %dB est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      destroy_matrice(&matriceT);
      break;
   }
   case 10:
   {

      MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
      MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
      MATRICE test = produit_matrice_creuses(&matrice, &matriceT);

      printf("Matrice x Matrice Transposée\n\n");


      t1 = clock(); // fonction 10 qui utilise 8
      VECTEUR *v = valeur_propre(&test);
      t2 = clock();
      printf("Temps d'exécution de la fonction %dA est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);
      if(!v) {
         destroy_matrice(&test);
         destroy_fichier(&matrice);
         destroy_matrice(&matrice);
         destroy_matrice(&matriceT);
         return 0;

      }
      free(v->I);
      free(v->X);
      free(v);

      printf("Matrice x Matrice Transposée\n\n");
      MATRICE test1 = produit_matrice_creuses(&matriceT, &matrice);
      t1 = clock(); // fonction 10 qui utilise 8
      VECTEUR *v1= valeur_propre(&test1);
      t2 = clock();
      printf("Temps d'exécution de la fonction %dB est %lf s\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      if(!v1) {
         free(v->I);
         free(v->X);
         free(v);
         destroy_matrice(&test);
         destroy_matrice(&test1);
         destroy_fichier(&matrice);
         destroy_matrice(&matrice);
         destroy_matrice(&matriceT);
         return 0;
      }

      free(v1->I);
      free(v1->X);
      free(v1);
      destroy_matrice(&test1);
      destroy_matrice(&test);
      destroy_fichier(&matrice);
      destroy_matrice(&matrice);
      destroy_matrice(&matriceT);
      break;

   }
   default:
   printf("Mauvais choix\n");
}

   printf("Tapez 's' pour arrêté le programme ou n'importe quelle caractère pour continuer\n");
   if(scanf(" %c", &s) != 1) return 0;
   purge();
} while ( s != 's');

return 0;
}

//
//
//   t1 = clock(); // fonction 1
//   MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
//   t2 = clock();
//
//   t3 = clock(); // fonction 2
//   MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
//   t4 = clock();
//
//
//   t7 = clock(); //fonction 4 TODO
//   statistique_nbrEleveCours(&matrice);
//   t8 = clock();
//
//
//   t9 = clock(); // fonction 6a qui utilise la 5
//   stat_filles_cours(matrice); // filles, essayer sans le printf
//   t10 = clock();
//
//   t11 = clock(); // fonction 6b qui utilise la 5
//   stat_cours_annee(matrice, 2008); // année, essayer sans le printf
//   t12 = clock();
//
//   t13 = clock(); // fonction 7
//   MATRICE test = produit_matrice_creuses(&matrice, &matriceT);
//   t14 = clock();
//
//   // t15 = clock(); // fonction 8 TODO
//   // MATRICE test = produit_matrice_creuses(matrice, matriceT);
//   // t16 = clock();
//
//   t17 = clock(); // fonction 9a
//   cours_commun_etudiant(matrice, matriceT); //essayer sans printf
//   t18 = clock();
//
//
//
//   t19 = clock(); // fonction 9b
//   etudiant_commun_cours(matrice, matriceT); // essayer sans printf
//   t20 = clock();
//
//   printf("Matrice x Matrice Transposée\n\n");
//   t21 = clock(); // fonction 10 qui utilise 8
//   VECTEUR *v = valeur_propre(&test);
//   t22 = clock();
//   if(!v)
//    return 0;
//   free(v->I);
//   free(v->X);
//   free(v);
//
//   printf("Matrice x Matrice Transposée\n\n");
//   MATRICE test1 = produit_matrice_creuses(&matriceT, &matrice);
//   t23 = clock(); // fonction 10 qui utilise 8
//   VECTEUR *v1= valeur_propre(&test1);
//   t24 = clock();
//   if(!v1)
//    return 0;
//   free(v1->I);
//   free(v1->X);
//   free(v1);
//   destroy_matrice(&test1);
//
//   /* ---------------------------------------------------------------------- */
//
//   printf(" | durée de l'exécution = %f secondes pour la première fonction\n",
//       (float)(t2-t1)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la deuxième fonction\n",
//       (float)(t4-t3)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la quatrième fonction\n", (float)(t8-t7)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la sixièmeA fonction\n", (float)(t10-t9)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la sixièmeB fonction\n", (float)(t12-t11)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la septième fonction\n", (float)(t14-t13)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la huitièmeA fonction\n", (float)(t22-t21)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la huitièmeB fonction\n", (float)(t24-t23)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la neuvièmeA fonction\n", (float)(t18-t17)/CLOCKS_PER_SEC);
//   printf(" | durée de l'exécution = %f secondes pour la neuvièmeB fonction\n", (float)(t20-t19)/CLOCKS_PER_SEC);
//
//   destroy_fichier(&matrice);
//   destroy_matrice(&matrice);
//   destroy_matrice(&matriceT);
//   destroy_matrice(&test);
//
// }
