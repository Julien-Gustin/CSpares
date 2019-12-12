#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "matrice.h"
#include "Sort.h"
#include "vecteur.h"

/* ------------------------------------------------------------------------- *
 * Stockes tout les matricules, cours et le nombres de lignes du fichier en mémoire
 *
 * PARAMETRES
 * fp           Fichier contenant les matricules,cours,quadrimestre
 * matrice      est une structure de données contenant les matricules, cours etc
 * ------------------------------------------------------------------------- */
static void fichier_en_memoire(FILE *fp, MATRICE *matrice);

void destroy_matrice(MATRICE *matrice){
  free(matrice->P);
  free(matrice->I);
  free(matrice->X);
}

void destroy_fichier(MATRICE *matrice){
  free(matrice->fichier.cours);
  free(matrice->fichier.coursDif);
  free(matrice->fichier.matricules);
}

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
  if(matrice->X == NULL)
    return; //ERREUR ALLOC

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

    matrice->fichier.matricules = matricules;
    matrice->fichier.cours = cours;
    matrice->nz = nbrLignes;
}

MATRICE fichier_en_matrice(char* input){
  FILE *fp = fopen(input, "r");
  size_t etudiantDif = 1; // 1 car on commence me comptage à 1
  size_t coursDif = 1;
  size_t j = 0;

  MATRICE matrice; // matrice creuse sous formes de structures de données

  fichier_en_memoire(fp, &matrice); // O(2n), n = nbr Lignes du fichier, nz

  sort_string(matrice.fichier.matricules, matrice.fichier.cours, matrice.nz); //trie la matrice ( chaque cours correpond bien à son étudiants ) 2n*Log(n)

  for(size_t i = 1; i < matrice.nz; i++){ // O(n), compte le nombres de cours différents
    if(strcmp(matrice.fichier.cours[i-1], matrice.fichier.cours[i]) != 0)
      coursDif++;

    }

  matrice.fichier.coursDif = malloc(sizeof(char[MAX])* coursDif); // crée un tableau de char contenant tout les cours différents, trié par ordre alphabétique
  if(matrice.fichier.coursDif == NULL)
    return matrice;

  matrice.I = malloc(sizeof(unsigned int) * matrice.nz); // tableau qui contient les lignes tels que A.I = (1, 2, 1) ou 1 chaques nombres correponds à un cours dans le tableau matrice.coursDif
  if(matrice.I == NULL)
    return matrice;

  strcpy(matrice.fichier.coursDif[0], matrice.fichier.cours[0]); // prcq la boucle commence à 1
  matrice.I[0] = 0;

  for(size_t i = 1; i < matrice.nz; i++){ // O(n)
    if(strcmp(matrice.fichier.cours[i-1], matrice.fichier.cours[i]) != 0){ // si cette condition est lévé cela veut dire que nous avons deux cours différents qui se suivent et vu qu'ils sont trié par ordre alphabétique nous pouvons concidérer que cours[i] est un cours pas encore écrits dans coursDif
      j++;
      strcpy(matrice.fichier.coursDif[j], matrice.fichier.cours[i]);
      }
    matrice.I[i] = j;

    }

  j = 0;

  sort(matrice.fichier.matricules, matrice.I, matrice.nz); //trie la matrice ( chaque cours correpond bien à son étudiants ) 2n*Log(n)

  for(size_t i = 1; i < matrice.nz; i++){ // trouve le nombres d'étudiants différents, O(n)
    if(matrice.fichier.matricules[i-1] != matrice.fichier.matricules[i])
      etudiantDif++;

  }

  matrice.P = malloc(sizeof(unsigned int) *etudiantDif); //A FAIRE :return erreur malloc
  if(matrice.P == NULL)
    return matrice;

  matrice.P[0] = 0;

  for(size_t i = 1; i < matrice.nz; i++){ // remplis matrice.P tel que chaque nouvelle case de ce tableau est une colonne ( donc un étudiant différents ) et le nombres stoqués dans la case est le numéro de l'élément O(n)
    if(matrice.fichier.matricules[i-1] != matrice.fichier.matricules[i]){
      j++;
      matrice.P[j] = i; //nombres d'éléments dans la colonne 'i'
    }
  }

  matrice.nbrColonnes = etudiantDif;
  matrice.nbrLignes = coursDif;
  fclose(fp);
  return matrice;
}

MATRICE transposee_matrice(MATRICE matrice){
  MATRICE matriceT;
  unsigned int *rowcount = calloc(matrice.nz, sizeof(unsigned int)); // nombres d'éléments dans chaque colonnes, chaque case correspond a un colonne

  matriceT.nz = matrice.nz; // meme nombres d'éléments
  matriceT.fichier = matrice.fichier; // meme données du fichier
  matriceT.X = malloc(sizeof(unsigned int)*matrice.nz); // A changer avec comme A.I
  if(matriceT.X == NULL)
    return matriceT;

  matriceT.I = malloc(sizeof(unsigned int)*matriceT.nz);
  if(matriceT.I == NULL)
    return matriceT;

 /* == rowcount == */
  for(size_t k = 0; k < matrice.nz; k++) //calcul le rowcount, O(n)
    rowcount[matrice.I[k]]++;
 /* == fin rowcount == */

 /* == matrice.P == */
  matriceT.P = malloc(sizeof(unsigned int) *matrice.nz);
  if(matriceT.P == NULL)
    return matriceT;

  matriceT.P[0] = 0 ;

  for(size_t i = 1; i < matrice.nz; i++) // complete A_t.P, tel que: P[i] = la valeur de la case précédentes ( P[i-1]) + la valeur de rowcount à l'indice précédent aussi rowcount[i-1] // O(n)
    matriceT.P[i] = matriceT.P[i-1] + rowcount[i-1];
 /* == fin matrice.P == */

 free(rowcount);

 /* == matrice.I == */
 unsigned int *vecteur = malloc(sizeof(unsigned int)*matrice.nz);
if(vecteur == NULL)
  return matriceT;

 for(size_t i  = 0; i < matriceT.nz; i++) // O(n)
  vecteur[i] = matriceT.P[i];

 for(size_t i = 0; i < matrice.nbrColonnes-1; i++){ // remplis matrice.I // O(n) pour les deux for
   for(size_t j = matrice.P[i]; j < matrice.P[i+1]; j++){
     matriceT.I[vecteur[matrice.I[j]]] = i;
     matriceT.X[vecteur[matrice.I[j]]] = matrice.X[j];
     vecteur[matrice.I[j]]++;
  }
}

  for(size_t j = matrice.P[matrice.nbrColonnes-1]; j < matrice.nz; j++){
    matriceT.I[vecteur[matrice.I[j]]] = matrice.nbrColonnes-1;
    matriceT.X[vecteur[matrice.I[j]]] = matrice.X[j];
    vecteur[matrice.I[j]]++;
  }
 /* == fin matrice.I == */

  matriceT.nbrLignes = matrice.nbrColonnes; //on inverse le nombres de lignes et colonnes car transposée
  matriceT.nbrColonnes = matrice.nbrLignes;

  free(vecteur);
  return matriceT;
}

MATRICE produit_matrice_creuses(MATRICE *a, MATRICE *b){
  VECTEUR vecteur;
  VECTEUR resultat;
  MATRICE c;
  c.fichier = a->fichier;
  // c tel que a x b, a comme ligne les lignes de a et les colonnes de b
  c.nbrLignes = a->nbrLignes;
  c.nbrColonnes = b->nbrColonnes;


  c.I = malloc(sizeof(unsigned int)*a->nbrLignes*b->nbrColonnes); //longueur max de C.I
  c.X = malloc(sizeof(unsigned int)*a->nbrLignes*b->nbrColonnes); //longueur max de C.X
  c.P = malloc(sizeof(unsigned int)*b->nbrColonnes);

  c.P[0] = 0;
  vecteur.I = malloc(sizeof(unsigned int)* b->nbrLignes); // C aura le meme nombres de lignes que A
  vecteur.X = malloc(b->nbrLignes*sizeof(unsigned int));

  vecteur.Xtmp = calloc(a->nbrLignes, sizeof(unsigned int));

  for(size_t i = 0; i < b->nbrColonnes; i++){ // O(2n) + O(c * 3n)
    if(i != b->nbrColonnes-1) // jusque derniere colonnes car apres la derniere colonne il y a nz
      vecteur.nbrNonZero = b->P[i+1] - b->P[i]; // le nombre de non zero d'une colonne est la différence de la premiere moins la secondes

    else
      vecteur.nbrNonZero = b->nz - b->P[i];

    for(size_t j = 0; j < vecteur.nbrNonZero; j++){ //vecteur contient les lignes et les éléments de la colonne correspondante
      vecteur.I[j] = b->I[b->P[i] + j];
      vecteur.X[j] = b->X[b->P[i] + j];
    }

  resultat = mult_matrice_vecteurs_creux(*a, vecteur); // multiplocation matrice, vecteur //O(n) +O(l), le pire des cas n'arrive jamais

  if(i != b->nbrColonnes-1) // on complete c colonne par colonne à l'aide des résultats de "resultat"
    c.P[i+1] = c.P[i] + resultat.nbrNonZero;

  else
    c.nz = c.P[i] + resultat.nbrNonZero;

  for(size_t j = 0; j < resultat.nbrNonZero; j++){ // O(n)
    c.I[c.P[i] + j] = resultat.I[j];
    c.X[c.P[i] + j] = resultat.X[j];
  }

  free(resultat.I);
  free(resultat.X);

  }

    free(vecteur.X);
    free(vecteur.I);
    free(vecteur.Xtmp);
return c;
}
