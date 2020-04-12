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
  char tmp = 0;
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
      printf("Temps d'exécution de la fonction %dA est %lf s\n \nappuyez sur n'importe quel caractère pour exécuter la fonction 6b", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      if(scanf("%c", &tmp) != 1) return 0;

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
      printf("Temps d'exécution de la fonction %dA est %lf s\n \nappuyez sur n'importe quel caractère pour exécuter la fonction 9b\n", choix,
         (float)(t2-t1)/CLOCKS_PER_SEC);

      if(scanf("%c", &tmp) != 1) return 0;

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

      t1 = clock(); // fonction 10 qui utilise 8
      VECTEUR *v = valeur_propre(&test);
      t2 = clock();
      printf("Temps d'exécution de la fonction %dA est %lf s\n \nappuyez sur n'importe quel caractère pour exécuter la fonction 10b\n", choix,
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

      if(scanf("%c", &tmp) != 1) return 0;

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
