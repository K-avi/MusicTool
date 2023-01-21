Features needed for MusicTool 1.0: 
    done! 

Features for MusicTool 1.1: 
   
    a library of utility functions , retrieve inverse of scale, add a note to a scale , check if a chprog can be built from a scale , retrieve scale from chprog, do vector of scale ,... 

    calling MusicTool like a shell command with arguments like -read -rand -harmo,...


Features for MusicTool 1.2: 
    
    implementing dodecaphonic series, 12 tone matrixes n operations on them 
    maybe implementing PCS? 
    making the parsing look better

Features for MusicTool 1.3: 
    
    a way to generate "coherent" chord progs by stacking coherent patterns(like a I IV V, II V I),...
    a way to add said patterns to an environment.
    generate chords w extensions or suspended chords

Features for MusicTool 1.4: 
    
    writing stuff to midi files maybe ? 


----------------------------------------


mtool 1.2: 

Implementation of 12 tone series: 

backend :

random generation : 
    -done (twice)
    
parsing: 
    -done 

calculating 12 tone matrixes: 
    -yee

basic functions: 
    -R: yes
    -I: yes
    -P: yes
    -RI: yes
    -TOMATRIX: yes

u_info: 
    -struct: y
    -save: y
    -remove: y

STATE OF PARSELOOP: 

made shorter thanks to (some) generics (yay) reducing the amount of boilerplates
unfortunately , the experiment to make eveything (or almost everything) as generic 
as possible was a failure. 
However, some generic functions were kept some of them being good (generic_scl_scl )
some of them being questionnable design choices (generic_rand)


s_dodec is almost done in parseloop (yay) 
has to be implemented in syntaxchecker (nay)
////////////////////////

MusicTool front: done

smtool front: done

syntaxchecking : not begun
