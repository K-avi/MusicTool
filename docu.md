g 

on cherche a harmoniser une gamme representee dans un ushort. 

Une gamme contient nécessairement un degré 0 ; donc celui ci n'est pas stockée. 
Une gamme peut contenir les notes 1 à 11. 

pour savoir les notes stockées dans une gamme, on set les bit correspondant à chaque note présente. 

Une note est representée par son n-1 ieme bit 
exemple: 

la 2nde mineure (1 * 1/2 tons au dessus de la note zéro) correspond au 0e bit; 
la 2nde majeure (2 * 1/2 tons au dessus de la note zéro) correspond au 1er bit;
.......

 les modes sont les rotations d'une gamme de x pas; ssi x est une note de la gamme
 
 par exemple, prennons la gamme majeure: 
 
 {0 2 4 5 7 9 11}; par convention son premier mode est elle même. 
 
 son second mode sera celle-ci décallée d'un "pas" vers la gauche 
 
 {2 4 5 7 9 11 0} (on decale vers la gauche) 
 {0 2 3 5 7 9 10} (on effectue l'opération (x -n)%12 avec x les notes de la gamme et n la nouvelle fondamentale et on obtient la nouvelle gamme

exemple : 

soit la representation binaire de la gamme majeure 

00000 101 0101 1010 

le mode dorien ("decale" de 2) sera: 

00000 011 0101 0110

le mode phrygien (" decale" de 4): 

00000 010 1101  0101

le mode lydien ("decale" de 5): 

00000 101 0110  1010

le mode mixolydien ("decale" de 7): 

00000 011 0101 1010

le mode eolien ("decale" de 9): 
00000 010 1101 0110

le mode phrygien ("decale" de 11): 
00000 010 1011 0101

-----------------------------------------


NOTATION DES DEGRES :

Les "degrés" présents dans une gamme correspondent à une notation utilisant des chiffres romains des notes présents dans une gamme. L'intêret de la notation par degrés contre la notation par note est qu'ils sont généraux. Par exemple, je peux affirmer de toute gamme majeure qu'elle contient les degrés "I II III IV V VI VII". Je peux ensuite faire correspondre ces degrés à des notes (C D E F G A B) pour do majeur, (A B C# D E F# G#) pour la majeur,.....

La notation des degrés d'une gamme est potentiellement bordélique si l'on s'éloigne des gammes standards ; 
exemple {0 3 5 6 9 10 11} contient les degrés :

I , #II, #III, #IV, ##V, #VI, VII 

Pour simplifier la notation, on ignorera les equivalents enharmoniques. Ainsi #II sera TOUJOURS noté bIII même si III est présent dans la gamme etc.. les degrés possibles sont donc: 

I, bII, II, bIII, III, IV, bV, V, bVI, VI, bVII, VII ; 

Pour differencier les triades a chaque degré, on utilisera la notation suivant I signifie degré 1 majeur, Im degré 1 mineur, I+ degré 1 augmenté, I° degré 1 diminué 

(cette notation n'est pas universelle, mais je l'ai pas inventée elle existe; cf https://ianring.com/musictheory/ )

-------------------------------------


TRIADES: 

Une triade est un accord composé de 3 notes.
 
Il existe 4 types (principaux on pourrait en rajouter 2 mais osef) de triades. 

les triades majeures, mineures, augmentées et diminuées. 
la triade majeure contient les notes { 0, 4, 7} (fondamentale, tierce majeure, quinte);
-//- mineure -//- {0 , 3 ,7} (fondamentale, tierce mineure, quinte); 
-//- augmentée {0 , 4, 8} (fondamentale, tierce majeure, quinte augmentée); 
-//- diminuée {0 ,3, 6} (fondamentale, tierce mineure, quinté diminuée); 

Dans une gamme, on peut construire des accords à chaque degré de la gamme (on devra donc faire les opérations  -n%12 si on est au nième degré.)

Exemple sur la gamme majeure: 

1er mode: {0 2 4 5 7 9 11} -> contient l'accord majeur
2e mode {(0-2%12) (2-2)%12.........}= {0 2 3 5 7 9 10} -> contient l'accord mineur 
etc
la gamme majeur contient les triades suivantes au degrés suivant: 

I majeur ,II mineur ,III mineur ,IV majeur ,V majeur ,VI mineur ,VII diminué 
ou plus simplement: 
I, IIm, IIIm, IV, V, VIm, VII° 

il existe d'autres notations pour certains types d'accords avec extensions (Isus4; I7; Imaj7; I6,11;...) ce n'est pas le sujet pour le moment.

