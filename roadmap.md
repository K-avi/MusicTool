Features needed for MusicTool 1.0: 
    done! 

Features for MusicTool 1.1: 
    a library of utility functions , retrieve inverse of scale, add a note to a scale , check if a chprog can be built from a scale , retrieve scale from chprog, do vector of scale ,... 

    calling MusicTool with arguments like -read -rand -harmo,...


Features for MusicTool 1.2: 
    implementing dodecaphonic series, 12 tone matrixes n operations on them 

Features for MusicTool 1.3: 
    a way to generate "coherent" chord progs by stacking coherent patterns(like a I IV V, II V I),...
    a way to add said patterns to an environment.
    generate chords w extensions or suspended chords

Features for MusicTool 1.4: 
    writing stuff to midi files maybe ? 




IMPLEMENTING PCS OBJECTS AT SOME POINT ??????
mtool 1.1 utility functions: 


-scale functions: 

    -get inverse of scale 
    -get prime of scale 
    -get complementary scale 
    
    -get interval structure
    -generate nearby scale 
    -get scale from chprog 

-print env: 
    -print all env 
    -print all scales
    -all harmos
    -all chprogs 


status invert : 

    implemented

status complementary : 

    implemented


status prime : 

    implemented

status interval structure from scale: 

-backend done 

status PCS/scale from chprog: 

-backend done


Might implement PCS as their own thing in frontend ?????


print env function written; has to be added as a runtime command n in the syntaxchecker; 
easy to retrieve print scales/harmos/chprogs from it