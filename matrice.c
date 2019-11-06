#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"


MATRICE fichier_en_matrice(char* input){
   FILE *fp = fopen(input, "r");

   char ligne[MAX+1];
   char matricule[MAX];
   char cours[MAX];

   int nbrEtudiant = 0;
   int l = 0;
   int multiple = 2; // pour realloc

   char **ToutLesMatricules = malloc(sizeof(char *)*ALLOC); // Matrice contenant ALLOC chaine de caractere de taille MAX, sert à contenir les matricules des étudiants
      if (ToutLesMatricules == NULL){
        printf("Probleme d'allocation\n");
        exit(EXIT_FAILURE);
      }

   for(int k = 0; k < ALLOC; k++){
     ToutLesMatricules[k] = malloc(sizeof(char)*MAX); //Chaine de caractere contenant les matricules des étudiants, d'une taille maximum de MAX ( 70 )
     if (ToutLesMatricules[k] == NULL){
       printf("Probleme d'allocation\n");
       free(ToutLesMatricules);
       exit(EXIT_FAILURE);
     }
   }

   MATRICE matrice;

   while(fgets(ligne, MAX, fp) != NULL){
     int i = 0;
     int k = 0;
     int j = 0;

     l = 0;


     if(ligne[0] != '\n'){ //on passe les lignes vides
        for(; ligne[i]!= ','; i++) //prends tout les caracteres avant la première virgule et le stocke dans matricule
          matricule[i] = ligne[i];

        matricule[i] = '\0';
        i++; //car ligne[i] = ','

        for(j = 0; ligne[i] != ','; i++){
          cours[j] = ligne[i]; //prends tout les caracteres avant la première virgule et le stocke dans cours
          j++;
        }

        cours[j] = '\0';

    }

      //  printf("%s %s %d\n", matricule, cours, nbrEtudiant);

        while((l < nbrEtudiant) && strcmp(ToutLesMatricules[l], matricule) != 0 )l++; // si l == nbrEtudiant ça veut dire que c'est un nouvel étudiant

        if(l == nbrEtudiant){
            if((nbrEtudiant % ALLOC) == 0 && nbrEtudiant != 0){ //Pour chaque multiple de ALLOC on realloc de 100 à chaque fois
              ToutLesMatricules = realloc(ToutLesMatricules, sizeof(char *)*ALLOC * multiple); //verif realloc

              for(int k = ALLOC*(multiple-1); k < ALLOC*multiple; k++)
                ToutLesMatricules[k] = malloc(sizeof(char)*MAX); //verif malloc

              multiple++;
            }

            strcpy(ToutLesMatricules[l], matricule);
            nbrEtudiant++;
      }
   }

   for(int j = 0; j < nbrEtudiant; j++){
     printf("[%s]", ToutLesMatricules[j]);
   }

   fclose(fp);
   for(int j = 0; j < ALLOC*(multiple-1); j++)
     free(ToutLesMatricules[j]);

   free(ToutLesMatricules);

}
