#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chordgen.h"
#include "harmo.h"
#include "globals.h"
#include "scalegen.h"
#include "types.h"
#include "misc.h"
#include "chordprog.h"
#include "harmo.h"
#include "chordpattern.h"

//////////////////// chord prog pattern identification: 




SIGNED_BOOL contains_pattern( S_SCALE scale, CHORD_DEGREES chord_degrees){//returns 1 if a scale contains triads at the degrees relev degrees n zero otherwise.

 SIGNED_BOOL ret=-1;

 for(CPT i=0; i<12; i++){
    if (ret==0) break;
    if ( (1<<i)& chord_degrees){
      if(i==0) ret= (triads_at_fund(scale)) ? 1 : 0 ; 
      
      else if( scale & (1<< (i-1)))  ret= (triads_at_fund(rot(scale, i))) ? 1 : 0 ; //no clue what this statement does
      
      else ret=0;
    } 
 }
  if(ret==-1) return 0;
  return  ret;
} //not sufficiently tested


PNode create_node( CHORD_DEGREES degrees){//corrected; not tested
  PNode pn=(PNode)malloc(sizeof(node));
  if (pn==NULL) {
    printf("Impossible d'allouer un node\n");
    return NULL;
  }
 
  pn->degrees=degrees;
  pn->chord_end=false;
  pn->frere_suivant=NULL;
  pn->fils=NULL;
  return pn;
}

void inserer_lettre(PNode *racine, PNode *n_lettre, CHORD_DEGREES degrees) {// not corrected "well"
//prolly need to redo 
  PNode prec=NULL;
  PNode n=*racine;
  if (n==NULL) {
    *racine=create_node(degrees);
    *n_lettre=*racine;
    return;
  }

  while(n!=NULL) {
    if (n->degrees == degrees) {
      *n_lettre=n;
      return;
    }
    if (n->degrees>degrees) { //no idea how that behaves tbh
      // on doit inserer avant n
      if (prec==NULL) {
        // insertion en tete
        prec=create_node(degrees);
        prec->frere_suivant=n;
        *racine=prec;
        *n_lettre=*racine;
      }
      else {
        *n_lettre=create_node(degrees);
        prec->frere_suivant=*n_lettre;
        (*n_lettre)->frere_suivant=n;
      }
      return;
    }
    prec=n;
    n = n->frere_suivant;
  }
  *n_lettre=create_node(degrees);
  prec->frere_suivant=*n_lettre;
}

PNode ajouter_mot(PNode racine, char *mot) {//wont work; need to redo
  PNode n=NULL;
  if (strlen(mot)==0) {
    return NULL;
  }
  inserer_lettre(&racine,&n,mot[0]);
  if (strlen(mot)==1) {
    n->chord_end=true;
  }
  else {
    n->fils=ajouter_mot(n->fils,mot+1);
  }
  return racine;
}

int taille(PNode racine) { //ok to keep
  if (racine==NULL) {
    return 0;
  }
  else {
    return 1+taille(racine->frere_suivant);
  }
}

void afficher_mots(PNode n, char mot_en_cours[], int index) { // needs to be redone


  if(!n) return;

 

  mot_en_cours[index]= n->degrees;

   if(!( n->chord_end) ) {
    mot_en_cours[index+1]='\0';
    printf("%s\n", mot_en_cours);
  }

  afficher_mots(n->fils, mot_en_cours, index+1);

  afficher_mots(n->frere_suivant, mot_en_cours, index);
}//non teste

void print_book(PNode root) {

  if(!root) return;

  char mot_en_cours[50]="";
  unsigned index=0;
  afficher_mots(root, mot_en_cours, index);
 
}

void free_book(PNode tree) { //can be kept
  if (!tree) return;

  free_book(tree->fils);
  free_book(tree->frere_suivant);
  free(tree);
}

PNode chercher_lettre(PNode n, CHORD_DEGREES degrees) {// needs to be redone
  if (n==NULL) {
    return NULL;
  }
  if (n->degrees==degrees) {
    return n;
  }
  if (n->degrees>degrees) {
    return NULL;
  }
  return chercher_lettre(n->frere_suivant,degrees);
}

int rechercher_mot(PNode dico, char *mot) {// needs to be redone
  PNode n=chercher_lettre(dico,mot[0]);
  if (n==NULL) {
    return 0;
  }
  if (strlen(mot)==1) {
    return n->chord_end == fin;
  }
  return rechercher_mot(n->fils,mot+1);
}


bool is_nth( S_CHORD_PROG  *chprog, CHORD_DEGREES chdegrees, INDEX i){//returns true if the chord at index i in chprog contains chdegrees; false otherwise
  if(!chprog) return false;

  if(! chprog->degrees[i]) return false;

  return (chprog->degrees[i]& chdegrees);
} //should work if i'm not dumb af; not tested though

bool search_prog( S_CHORD_PROG* chprog, PNode tree){//true if chord prog in tree; false otherwise
  return 0;
}
/*

PNode lire_dico(const char *nom_fichier) {

  FILE * f =fopen(nom_fichier, "r");
  char ligne[100];

  if (f==NULL){
      printf("Erreur lors de l'ouverture du fichier %s\n",nom_fichier);
      return NULL;
  }

  PNode n= NULL;

  while( fgets(ligne, 100, f)){
    ligne[strlen(ligne)-1]='\0';
    n=ajouter_mot(n, ligne);
  }

  fclose(f);
  return n;

}
*/