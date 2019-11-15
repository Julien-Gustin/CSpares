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

/* ------------------------------------------------------------------------- *
 * Fait une recercheche dichotomique pour trouver l'indice du tableau correspondant à la valeur recherchée
 *
 * PARAMETRES
 * tab          tableau d'entier positif triée
 * debut        debut intervalle de recherche
 * tailleTab    fin intervalle de recherche
 * valeur       est la valeur à retrouvée
 * ------------------------------------------------------------------------- */
static unsigned int recherche_indice_dichotomique(unsigned int *tab, unsigned int debut, unsigned int tailleTab, unsigned int valeur);

/* ------------------------------------------------------------------------- *
 * Affiche le nombres de filles de chaques cours
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * ------------------------------------------------------------------------- */
static void stat_filles_cours(MATRICE matrice);

/* ------------------------------------------------------------------------- *
 * Affiche le nombres d'eleve de l'annee donnée pour chaque cours
 *
 * PARAMETRES
 * matrice          matrice creuse ligne = cours, colonnes = étudiants
 * annee            annee des etudiants
 * ------------------------------------------------------------------------- */
static void stat_cours_annee(MATRICE matrice, unsigned int annee);

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

void destroy_vecteur(VECTEUR *vecteur){
  free(vecteur->I);
  free(vecteur->X);
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

  matrice->X = malloc(sizeof(int)*nbrLignes);
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

static unsigned int recherche_indice_dichotomique(unsigned int *tab, unsigned int debut, unsigned int tailleTab, unsigned int valeur){
  while (debut <= tailleTab) { // O(logn)
      int curseur = debut + (tailleTab - debut) / 2;

      // Si la valeur du tableau ou pointe le curseur corresponds bien à la valeur
      if (tab[curseur] == valeur)
          return curseur;

      // Si la valeur est trop grande, on ignore la moitier gauche restante du tab
      if (tab[curseur] < valeur)
          debut = curseur + 1;

      // si la valeur est trop grande on igore la moitier droite du tab
      else
          tailleTab = curseur - 1;
  }

  return -1; // element pas présent
}


MATRICE fichier_en_matrice(char* input){
  FILE *fp = fopen(input, "r");
  size_t etudiantDif = 1; // 1 car on commence me comptage à 1
  size_t coursDif = 1;
  size_t j = 0;

  MATRICE matrice; // matrice creuse sous formes de structures de données

  fichier_en_memoire(fp, &matrice); // O(2n)

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
  for(size_t k = 0; k < matrice.nz; k++) //calcul le rowcount
    rowcount[matrice.I[k]]++;
 /* == fin rowcount == */

 /* == matrice.P == */
  matriceT.P = malloc(sizeof(unsigned int) *matrice.nz);
  if(matriceT.P == NULL)
    return matriceT;

  matriceT.P[0] = 0 ;

  for(size_t i = 1; i < matrice.nz; i++) // complete A_t.P, tel que: P[i] = la valeur de la case précédentes ( P[i-1]) + la valeur de rowcount à l'indice précédent aussi rowcount[i-1]
    matriceT.P[i] = matriceT.P[i-1] + rowcount[i-1];
 /* == fin matrice.P == */

 free(rowcount);

 /* == matrice.I == */
 unsigned int *vecteur = malloc(sizeof(unsigned int)*matrice.nz);
if(vecteur == NULL)
  return matriceT;

 for(size_t i  = 0; i < matriceT.nz; i++)
  vecteur[i] = matriceT.P[i];

 for(size_t i = 0; i < matrice.nbrColonnes-1; i++){
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

VECTEUR mult_matrice_vecteurs_creux(MATRICE matrice, VECTEUR vecteur){
  // élément non nuls de B = nbrNonZero
  VECTEUR z;
  size_t k = 0;
  unsigned int nombreLignes = 0;
  unsigned int lignesDif = 1;

  //O(n) , n  = nombres de lignes
  for(size_t i = 0; i < vecteur.nbrNonZero; i++){ //Comptes le nombres de lignes ( en tout ) union vecteur et colonne correspondant aux vecteurs
    if(vecteur.I[i] < matrice.nbrColonnes-1){
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.P[vecteur.I[i]+1];j++)
        nombreLignes++; // pour matrice
    }
    else{
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.nz;j++)
        nombreLignes++; // pour matrice
    }
  }

  unsigned int *tab = malloc(sizeof(unsigned int) *nombreLignes); //tableau contenant toutes les ligne matrice U vecteur
  if(tab == NULL)
    return vecteur;

  // O(n)
  for(size_t i = 0; i < vecteur.nbrNonZero; i++){ //Comptes le nombres de lignes ( en tout ) union vecteur et colonne correspondant aux vecteurs

    if(vecteur.I[i] < matrice.nbrColonnes-1){
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.P[vecteur.I[i]+1];j++){
        tab[k] = matrice.I[j];
        k++; // pour matrice
      }
    }
    else{
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.nz;j++){ // dernier élément de matrice.P ne correponds pas à nz
        tab[k] = matrice.I[j];
        k++;
      }
    }
  }

  quickSort(tab, nombreLignes); // trie le tab  O(nlogn)

  //O(n)
  for(size_t i = 1; i < nombreLignes; i++){ // compte le nombres de lignes différentes
    if(tab[i-1] != tab[i])
      lignesDif++;
  }

  z.nbrNonZero = lignesDif;
  z.sommeTot = 0;

  /* Création z.I contenant les lignes non-zero du vecteur et z.X contenant le contenu de ces lignes */
  z.I = malloc(sizeof(unsigned int)*lignesDif);
  if(z.I == NULL)
    return z;

  z.X = calloc(lignesDif, sizeof(unsigned int));
  if(z.X == NULL)
    return z;

  z.I[0] = tab[0];
  k = 0;

  // O(n)
  for(size_t i = 1; i < nombreLignes; i++){ //remplis z.I de lignes différentes
    if(tab[i-1] != tab[i]){
      k++;
      z.I[k] = tab[i];
    }
  }

  //O(n)* O(nlogn)
  for(size_t i = 0; i < vecteur.nbrNonZero; i++){ // trouve les composantes de z.X
        //  printf("%d : %d, %d\n", i, vecteur.I[i], matrice.nbrColonnes-1);
    if(vecteur.I[i] < matrice.nbrColonnes-1 ){ // nous ne sommes pas à la derniere colonnes de matrice.P
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.P[vecteur.I[i]+1];j++){
        z.X[recherche_indice_dichotomique(z.I, 0, z.nbrNonZero, matrice.I[j])] += matrice.X[j] * vecteur.X[i];
        z.sommeTot += matrice.X[j] * vecteur.X[i];
      }
    }
    else{ // nous sommes à la dernière colonnes de matrice.P donc on va jusque nz
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.nz;j++){
        z.X[recherche_indice_dichotomique(z.I, 0, z.nbrNonZero, matrice.I[j])] += matrice.X[j] * vecteur.X[i];
        z.sommeTot += matrice.X[j] * vecteur.X[i];
      }
    }
  }

free(tab);
return z;

}

static void stat_filles_cours(MATRICE matrice){
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

  size_t k = 0;

  //stocke l'indice des matricules impair
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
    if((matrice.fichier.matricules[matrice.P[i]] % 2) != 0){
      filles.I[k] = i;
      k++;
    }
  }

  VECTEUR resultat = mult_matrice_vecteurs_creux(matrice, filles);

  for(size_t i = 0; i < resultat.nbrNonZero; i++)
    printf("%s filles :%d\n", matrice.fichier.coursDif[resultat.I[i]], resultat.X[i]);

  destroy_vecteur(&resultat);
  destroy_vecteur(&filles);

}

static void stat_cours_annee(MATRICE matrice, unsigned int annee){
  VECTEUR eleveAnnee;
  unsigned int nbrELeveAnnee = 0;
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
  //  printf("%u\n", matrice.fichier.matricules[matrice.P[i]] / 10000);
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

  size_t k = 0;
  for(size_t i = 0; i < matrice.nbrColonnes; i++){
  //  printf("%u\n", matrice.fichier.matricules[matrice.P[i]] / 10000);
    if(!((matrice.fichier.matricules[matrice.P[i]]/10000) % annee)){
      eleveAnnee.I[k] = i;
      k++;
    }
  }

  VECTEUR resultat = mult_matrice_vecteurs_creux(matrice, eleveAnnee);

  for(size_t i = 0; i < resultat.nbrNonZero; i++)
    printf("%s annee :%d :%d\n", matrice.fichier.coursDif[resultat.I[i]], annee, resultat.X[i]);

  destroy_vecteur(&resultat);
  destroy_vecteur(&eleveAnnee);

}

void statistique(MATRICE matrice){
  stat_filles_cours(matrice);
  stat_cours_annee(matrice, 2008);

}
