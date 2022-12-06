#ifndef CHORDPATTERN_H_INCLUDED
#define CHORDPATTERN_H_INCLUDED


#include "types.h"

#define LONGUEUR_MAX_MOT 30

#define LONGUEUR_MAX_MOT 30

// fin = il existe un mot finissant par cette lettre
// non_fin = il n'existe pas de mot finnissant par cette lettre
typedef enum _FDM {fin,non_fin} FDM;


extern SIGNED_BOOL contains_pattern( S_SCALE scale, CHORD_DEGREES chord_degrees);


typedef struct node* PNode;

typedef struct node {
  CHORD_DEGREES degrees;
  bool chord_end;
  PNode fils;
  PNode frere_suivant;
} node;


/*
PNode creer_node(char lettre);
void inserer_lettre(PNode *racine, PNode *n_lettre, char lettre);
PNode ajouter_mot(PNode racine, char *mot);
void afficher_mots(PNode n, char mot_en_cours[], int index);
void afficher_dico(PNode racine);
void detruire_dico(PNode dico);
int rechercher_mot(PNode dico, char *mot);

PNode lire_dico(const char *nom_fichier);
*/


#endif