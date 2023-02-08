Features needed for MusicTool 1.0: 
    
    the scale, chprog, and harmo types. 
    Being able to read command files. 
    doing some basic operations on scale/ harmo 
    saving / printing / removing scales, harmo n 
    chprogs
    writing /reading environments
    a command line interpreter
    a syntaxchecker/ parser

Features of MusicTool 1.1: 
   
    a library of utility functions , retrieve inverse of scale, add a note to a scale , check if a chprog can be built from a scale , retrieve scale from chprog, do vector of scale ,... 

    calling MusicTool like a shell command with arguments like -read -rand -harmo,...


Features of MusicTool 1.2: 
    
    implementing dodecaphonic series, 12 tone matrixes n operations on them 
    making the parsing look better

Features for MusicTool 1.3: 
    
    1.3.1: implementing suspended chords in the triad type (formerly chprog type)
           implementing a prog type (chord prog with extensions)
           being able to compile MusicTool/smtool w/o syntaxchecking (for the sake of it)
    1.3.2: a way to generate "coherent" chord progs by stacking coherent patterns(like a I IV V, II V I),...
    a way to add said patterns to an environment.

Features for MusicTool 1.4: 
    
    PCS type? 
    writing stuff to midi files maybe ? 



1.3.2 : 

Chordbook: 

How to implement chordbook? 

-> candidates: 

-Linked List where each element is a block: 

    pros: none
    cons: trash 

-BST where LEFT node is next degree n right node is other choices for current degree: 

    pros: really fucking compact 
    cons: confusing + awful to search 

-Table of degree + next ???
    
    pros: really fucking compact ; possibility to do bitwise shit maybe ?
    cons: not sure how to do it YET

big problem of non-trivial rep is: if I make representation compact HOW can I minimise 
number of checks to retrieve a prog of length N????

really tricky tbh 

maybe do it in multiple steps 

-retrieve deg przt 

-filter from beeg tree /array 


MAKE THE STRUCT REPEAT ITSELF IF ITS A TREE 

1 alloc FOR EACH NODE BUT BUT BUT MULTIPLE NODES POINTING TO THIS ONE !!!!!!!!!!!
