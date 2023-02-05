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
    
    writing stuff to midi files maybe ? 

MusicTool 1.3: 


rewrite structure : 

    from 8 bits to 16 bits -> stored as scale + degree

printing: 
    
    done!

generating extended chords:  
    
    YES YES YES 

parsing:

    YES YES YES 

syntaxchecking: 

    YES YES YES

saving: 

    need to repurpose chord to store extended chords 
    current chords will be renamed as "triads" 

frontend implementation: 

    done 

compile MusicTool w/o syntaxchecking: 

    not done yet 



rand will break mtool if u pass -extnum > ext_total; gotta fix it 

guarantee scl generation when -scllen is passed ( build from a random triad n add notes?)

make triad rand behave like prog rand

possibility to compile w/o syntaxchecking (gonna do later)


1.3.2 : 

Chordbook: 

not there yet 