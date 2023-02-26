Current version of MusicTool: 1.3.2 ; 

NB: I'm taking a break from the MusicTool project to do other stuff ATM. 
    However I will come back to it eventually. The roadmap from version 
    1.4 onwards is to give a general idea of the features I'd like to add 
    to the projects but I won't necessarily do it in this order.

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

    1.3.3: fix progbook by making it some kind of hash table. Make S_SAVED_... dynamic arrays 
           instead of linked lists.

Features for MusicTool 1.4 : 

    generating midi files from scales / progs / series / dodecaphonic matrixes

Features for MusicTool 1.5 :

    1.5.1 : the PCS type / degree prog type
    1.5.2 : chord substitution in chord progs 


Features for MusicTool 1.6 : 

    1.6.1 : Neo Riemannian functions on PCS / triad progs
    1.6.2 : support of standart english notations (C, D, E,...) for notes and chord (maybe also 
            european notation  Do, Re , Mi,...)

