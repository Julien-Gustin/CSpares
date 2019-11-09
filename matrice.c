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

  char ligne[MAX_LIGNES+1];
  unsigned int nbrLignes = 0;

  while(fgets(ligne, MAX_LIGNES, fp) != NULL) nbrLignes++; // comptes le nombres de lignes (O(n))
  rewind(fp); // remet le curseur au début du fichier

  unsigned int *matricules = malloc(sizeof(unsigned int)*nbrLignes); //matrice contenant tout les matricules du fichier meme ceux répétés
  if(matricules == NULL)
    return; //ERREUR ALLOC

  char (*cours)[MAX] = malloc(sizeof(char[MAX])*nbrLignes); //matrice contenant tout les cours correspondant aux étudiants
  if(cours == NULL)
    return; //ERREUR ALLOC

  matrice->X = malloc(sizeof(unsigned int)*nbrLignes);

  for(size_t i = 0; i < nbrLignes; i++){ // O(n), copie colle le fichier en mémoire
    if(fscanf(fp, "%u", &matricules[i]) != 1) // matricules[i] contient le matricule d'un étudiant ( peut etre répétés)
      return; //exit

    fseek(fp, 1, SEEK_CUR); // permet d'ignorer la ',' mise apres le matricule

    if(fgets(cours[i], MAX, fp) == NULL)
      return;

    if(fgets(ligne, MAX_LIGNES, fp) == NULL) // passe la ligne ( pour ne pas compté le quadrimestre)
      return;

    matrice->X[i] = 1;

  }

    matrice->matricules = matricules;
    matrice->cours = cours;
    matrice->nbrLignes = nbrLignes;
}

MATRICE fichier_en_matrice(char* input){
  FILE *fp = fopen(input, "r");
  size_t etudiantDif = 1; // 1 car on commence me comptage à 1
  size_t coursDif = 1;
  size_t j = 0;

  MATRICE matrice; // matrice creuse sous formes de structures de données

  fichier_en_memoire(fp, &matrice); // O(2n)

  sort_string(matrice.matricules, matrice.cours, matrice.nbrLignes); //trie la matrice ( chaque cours correpond bien à son étudiants ) 2n*Log(n)

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // O(n), compte le nombres de cours différents
    if(strcmp(matrice.cours[i-1], matrice.cours[i]) != 0)
      coursDif++;

    }

  matrice.coursDif = malloc(sizeof(char[MAX])* coursDif); // crée un tableau de char contenant tout les cours différents, trié par ordre alphabétique
  matrice.I = malloc(sizeof(unsigned int) * matrice.nbrLignes); // tableau qui contient les lignes tels que A.I = (1, 2, 1) ou 1 chaques nombres correponds à un cours dans le tableau matrice.coursDif

  strcpy(matrice.coursDif[0], matrice.cours[0]); // prcq la boucle commence à 1
  matrice.I[0] = 0;

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // O(n)
    if(strcmp(matrice.cours[i-1], matrice.cours[i]) != 0){ // si cette condition est lévé cela veut dire que nous avons deux cours différents qui se suivent et vu qu'ils sont trié par ordre alphabétique nous pouvons concidérer que cours[i] est un cours pas encore écrits dans coursDif
      j++;
      strcpy(matrice.coursDif[j], matrice.cours[i]);
      }
    matrice.I[i] = j;

    }

  j = 0;

  sort(matrice.matricules, matrice.I, matrice.nbrLignes); //trie la matrice ( chaque cours correpond bien à son étudiants ) 2n*Log(n)

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // trouve le nombres d'étudiants différents, O(n)
    if(matrice.matricules[i-1] != matrice.matricules[i])
      etudiantDif++;

  }

  matrice.P = malloc(sizeof(unsigned int) *etudiantDif); //A FAIRE :return erreur malloc
  matrice.P[0] = 0;

  for(size_t i = 1; i < matrice.nbrLignes; i++){ // remplis matrice.P tel que chaque nouvelle case de ce tableau est une colonne ( donc un étudiant différents ) et le nombres stoqués dans la case est le numéro de l'élément O(n)
    if(matrice.matricules[i-1] != matrice.matricules[i]){
      j++;
      matrice.P[j] = i; //nombres d'éléments dans la colonne 'i'
    }
  }

  fclose(fp);
  return matrice;
}
/*
MATRICE transposee_matrice(MATRICE matrice){

  MATRICE matriceT = matrice;

  return matriceT;
}*/
