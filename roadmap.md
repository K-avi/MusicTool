Ce qui est a faire ds le scale mode:

refaire API pr qu'elle soit mieux ( un seul mode avc tte les fonctions)

/////chord mode:

sst generation de triades a partir d'une gamme.

sst generation accords avc n extensions a partir d'une gamme

generation d'accords:
-> simple (random)
-> par blocs de triades preconcus (II ; V ; I etc)
-> complexe (peut etre que je le ferais ps mais l'idée
c'est qu'il comprenne certains principes de transpositions d'accord et une version
simplifiée de l'harmonie tonale; concept de Ton, S-D, Dom...)

apres chord mode :

possibilite d'ecrire resultats sur fichier .txt (les rendre interpretables pour faire systeme de sauvegarde???)

possibilite d'ecrire resultats sur fichiers .midi (ps interpretables apres pcq trop dangereux)




generation d'accords par pattern : 


"base de donnees" avc progression d'accords préconçues: 

ex: 

IV V I //cadence parfaite
II V I //jazse
V I //imparfaite
IV I //pelagiale qqch comme ça la
I bVII bVI V //cadence anda
VI IV V I  //ukulele bby
VI I  //eheh
VI III IV V I //eheheh
V bII I //eheheheh
I bIII IV //bluesy boi


GENERATION PAR PATTERN : 

-doit faire fonction de comparaison 
    
    -> bool is_nth( CHORD_PROG chprog, CHORD_DEGREES chdeg, INDEX n)
        -> droite si non 
        ->gauche si oui 
            ->incremente le compteur

-doit faire fonction de recherche 
    -> PNode/bool search_prog( CHORD_PROG chprog, PNode tree)
        ->return true if in tree; 

        -> se base sur is nth; si j'arrive a n==chprog->length alors je contiens sinn non
        -> si je contiens pas avant je renvoie false

-doit faire fonction d'ajout
    -> void add_chprog( CHORD_PROG chprog , CHORD_DEGREES chdeg)
        -> parcours jusqu'à ce que chprog ne corresp ps à chdeg 
        -> ajoute les nodes 


-doit faire fonction de generation aleatoire 
    -> CHORD_PROG* get_randchprog( LENGTH length, PNode tree)
    ->cree une suite d'accord en parcourant un arbre 
    ->bonchance