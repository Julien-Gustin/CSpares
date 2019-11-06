#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "matrice.h"
#include "Sort.h"

/* ------------------------------------------------------------------------- *
 * Stockes tout les matricules, cours et le nombres de lignes du fichier en mémoire
 *
 * PARAMETRES
 * fp           Fichier contenant les matricules,cours,quadrimestre
 * matrice      est une structure de données contenant les matricules, cours etc
 * ------------------------------------------------------------------------- */
static void fichier_en_memoire(FILE *fp, MATRICE *matrice);

static void fichier_en_memoire(FILE *fp, MATRICE *matrice){
  char ligne[MAX+1];
  unsigned int nbrLignes = 0;
  char caractere;
  size_t j;

  while(fgets(ligne, MAX, fp) != NULL) nbrLignes++; // comptes le nombres de lignes
  rewind(fp); // remet le curseur au début du fichier

  unsigned int *matricules = malloc(sizeof(int)*nbrLignes); //matrice contenant tout les matricules du fichier meme ceux répétés
  if(matricules == NULL)
    return; //ERREUR ALLOC

  char (*cours)[MAX] = malloc(sizeof(char[MAX])*nbrLignes); //matrice contenant tout les cours correspondant aux étudiants
  if(cours == NULL)
    return; //ERREUR ALLOC

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
  size_t etudiantDif = 1; // 1 car on commence me comptage à 1
  size_t j = 0;

  MATRICE matrice;

  fichier_en_memoire(fp, &matrice);

  sort(matrice.matricules, matrice.cours, matrice.nbrLignes); //trie la matrice ( chaque cours correpond bien à son étudiants )

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // trouve le nombres d'étudiants différents
    if(matrice.matricules[i-1] != matrice.matricules[i])
      etudiantDif++;

  }

  matrice.P = malloc(sizeof(unsigned int) *etudiantDif); //A FAIRE :return erreur malloc
  matrice.P[0] = 0;

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // trouve le nombres d'étudiants différents
    if(matrice.matricules[i-1] != matrice.matricules[i]){
      j++;
      matrice.P[j] = i; //nombres d'éléments dans la colonne 'i'
    }
  }

  fclose(fp);
  return matrice;
}
