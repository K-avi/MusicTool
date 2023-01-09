DOCU: EN 

summary: 

I: Introduction

II: what objecs can MusicTool represent?  
  1: abstract scales 
  2: abstract harmo 
  3: abstract chprog 

III: how to use MusicTool from command line ?
  1: the scale command 
  2: the harmo command 
  3: the chprog command
  4: the read / write commands
  5: additionnal commands/syntax elements

IV: writing MusicTool files: 
  1: writing command files
  2: writing environment files



I: 
    MusicTool is a simple command line and file interpreter coded in C.
    Like it's name suggests it's main purpose is to be a tool for Music operations such as scale generation,
    chord prog generations and analyzing various properties of musical sets and objects.

II.1: what are the MusicTool scales? 
    to represented musical scales, MusicTool uses sets of numbers%12. 
    Each number present in the set represents a note present in the scale, with the number indicating how many semitones separate the fundamental note of the scale from the note.
    for example , the major scale would be represented as { 0 2 4 5 7 9 11 }. 
    If we take C as the fundamental note of the major scale, it would be C D E F G A B

    How are scales encoded ? 
    Scales are stored on 11 bits as unsigned short integers. It is assumed that every scale contains a fundamental note, 
    each other note present in the scale is stored as a bit set to 1. If the first bit of the u_short is set it means that the scale 
    contains a minor second, if the second is set a major second, ...
    
    This representation is different from the standart pitch class set representation , if you want to learn more on 
    abstract set and pitch class set you can visit this website : https://ianring.com/musictheory/scales/

II.2: what are MusicTool harmonised scales?
    
    If you need to learn about the notion of a mode in Music Theory please visit : https://en.wikipedia.org/wiki/Mode_(music) 
    harmonised scale are a list of abstract scale. And are stored as such. 
    I assumed that it was more to store the whole harmonised scale once it is generated 
    rather than storing it as it's fundamental mode and generating it each time it is called for an operation. 
    Harmonised scale being a list of u_shorts of length between 2 and 11 they don't take much space. I might change this implementation 
    if I realise it's more interresting to store them as their fundamental mode and generate them if need be (to print them for example)

II.3: what are MusicTool chprog ? 
    
    A chprog is a list of abstract triads using the degree notation of chords. An abstract triad consists on the root degree of the
    triad relative to a tonic chord and the type of the triad. 
    Due to it being easier to store , the triads are noted as such : 
    major triad: [DEGREE]
    minor triad: [DEGREE]m
    diminished triad: [DEGREE]-
    augmented triad: [DEGREE]+ 
    I didn't use ° to represent the diminished chord bc it's an UTF-8 character and I didn't feel like working with them.
    
    chprogs are noted between brackets. 
    For example: the chprog [ IVm, V, Im] represents the chord progression from a minor triad located at the fourth degree of a scale
    to a  major one located at the fifth to another major one located on the tonic. 
    if we take the C harmonic minor scale, the progression [ IVm , V, I]  would be Fm, G, Cm






DOCU: FR 
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

Pour differencier les triades a chaque degré, on utilisera la notation suivant I signifie degré 1 majeur, Im degré 1 mineur, I+ degré 1 augmenté, I- degré 1 diminué 

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
I, IIm, IIIm, IV, V, VIm, VII- 

il existe d'autres notations pour certains types d'accords avec extensions (Isus4; I7; Imaj7; I6,11;...) ce n'est pas le sujet pour le moment.

--------------------

La structure Chordbook : 

elle contient la liste de suite d'accords connus que MusicTool peut reconnaitre. 
Parmis celles-ci on trouve le 

II V I;
IV V I;
etc. 
Pour rendre la structure + compacte et la génération d'accords plus flexible, on supposera que toutes les triades peuvent être utilisées pour remplir une pattern d'accord. Ex: 

II V I 
II+ Vm I-
etc
