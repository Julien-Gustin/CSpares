#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "matrice.h"

void fichier_en_memoire(FILE *fp, MATRICE *matrice){
  char ligne[MAX+1];
  unsigned int nbrLignes = 0;
  char caractere;
  size_t j;

  while(fgets(ligne, MAX, fp) != NULL) nbrLignes++; // comptes le nombres de lignes
  rewind(fp); // remet le curseur au début du fichier

  unsigned int *matricules = malloc(sizeof(int)*nbrLignes); //matrice contenant tout les matricules du fichier meme ceux répétés
  unsigned char (*cours)[MAX] = malloc(sizeof(char[MAX])*nbrLignes); //matrice contenant tout les cours correspondant aux étudiants

  for(size_t i = 0; i < nbrLignes; i++){
    fscanf(fp, "%d", &matricules[i]); // matricules[i] contient le matricule d'un étudiant

    j = 0;
    fseek(fp, 1, SEEK_CUR); // permet d'ignorer la ',' mise apres le matricule
    while((caractere = fgetc(fp)) != ','){ // nous notons le nom du cours caractere par caractere histoire de ne pas avoir la virgule
      cours[i][j] = caractere;
      j++;
    }
    fgets(ligne, MAX, fp); // passe la ligne ( pour ne pas compté le quadrimestre)
  }

    matrice->matricules = matricules;
    matrice->cours = cours;
    matrice->nbrLignes = nbrLignes;
}

MATRICE fichier_en_matrice(char* input){
  FILE *fp = fopen(input, "r");
  int test;
  char ligne[MAX+1];
  char mot[20];

  MATRICE matrice;

  fichier_en_memoire(fp, &matrice);

  for(size_t i = 0; i < matrice.nbrLignes; i++){
      printf("[%d][%s]\n", matrice.matricules[i], matrice.cours[i]);
    }



  fclose(fp);
}
