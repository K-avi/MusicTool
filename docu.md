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
