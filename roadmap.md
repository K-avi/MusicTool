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

Possible features for future MusicTool releases: 
    
    PCS type
    Chord substitution
    writing progs / scales as midi files
    Neo Riemannian related stuff (generation/operations)
    support of standart english notation for notes/chords (A, B, C,...)


1.3.2 : 

Progbook: 

How to implement the prog book? 

after thinking abt it for a while n discussing it with one of my teachers I've decided to implement 
the progbook structure as a dynamic array.

I've considered using an ABR or some form of hashed array but I can make the array compact AF w each entry (chord prog) of the prog book 
being stored on 64 bits.

The main reason to choose this implementation is that in a good scenario, only one malloc will be needed for the WHOLE book. Which is huge. 

An ABR is theoretically the best solution but due to the representation of the book being really fucking compact the space needed to store 2 pointers @ each node + the need for it to call malloc often makes it less good (I think) 

A hash table could be a good compromise in term of space/ease of use but it also would need a couple mallocs. 

I might reconsider the implementation at some point though

progbook could be a hashed into an table w each PCS being a key of the table n then every prog that has this pcs is stored at that index ....
it would involve using more realloc though. 



structures documentation : 

explain how everythin is stored/ what each structure is ,...
could benefit from it myself tbh 


PROGBOOK implementation : 

structure: 

    done 

basic operation : 

    -add : done 
    -check : done 
    -remove : not gonna do it lol 
    -realloc: done (I think)

    -retrieve indexes where u can generate stuff given a PCS 

chord/triad prog generation : 

    -generate skeleton of the prog first by generating a degree prog. 
    -then add triad / (triad + extensions) to it when generating a prog 

frontend: 

    -load book 
    -write current book 
    -fuse books ? 
    -add entry 

handling "removing" could be achieved w a command to ignore certain entries but idk about that tbh 


Generation of a prog given the blocks that a scale contains: 


I guess I need to know which length I can generate. 

-> ushort encoced in 1-hot (cool)

-> then pick a random length %length I wanna achieve 

-> then add a prog of this length in the chord I'll return 

-> substract the length I wanna achieve w the one I did. 

-> repeat untill I've finished


-> awful; painfull; annoying 


Gonna test 2 implems for progbook. First one is juste a regular array where I put progs 

Other one is kinda like a Hash Table; where each index is associated Pitch Class Set 
n an array every prog that needs this Pitch Class set is stored in the array of said degree . 
Might be a better rep idk . 

The structure would be smtg like: 

typedef struct {
    BOOKENTRIES * entries ; 
    PITCH_CLASS_SET key; 
    CPT nb_entries, max_entries;
}ARRAY_ENTRIES 

typedef struct{ 
    ARRAY_ENTRIES* indexes;
    CPT nb_entries, max_entries; 
}BOOK_TABLE


Also I'm prolly gonna generate a table where entries r sorted by length in an array to generate random stuff cuz it makes my life wayyyyyy easier.


STATUS OF SMTOOL 1.3.2:

done for progbook: 

    -make the generation of arrays better ( customize the dynamic allocation so that they don't take a lot of space)   done 

    -make the generation function take edge cases (can only generate 1 prog ) into account

    -do the functions that turn a degreee prog into a triad / chprog

    -make the progbook file clean (MACROS + split into 2/3 files) never!!!! (kinda)

    -customise generation (nb extensions etc)

     -implement syntaxchecking 

    -implement the parsing 



IF I HAVE THE TIME AND WILL; REDO THE IMPLEMENTATION TO MAKE IT ACTUALLY DECENT: 

create a table of tables indexed by proglength  

in each table save bookentries in a table indexed by PCS 





pending for progbook: 


    

    -implement in the frontend 

        -generate 
        -add 
        -save book 
        -load book 
        -print book
        


parsing -> done 


syntaxchecking -> done 

env / read dont need to be updated 

book print -> done tested 
book add -> done tested

triad coherand -> done  
prog coherand -> done  


CMD LINE / FRONTEND : 

parsing/io -> 

book print  done tested
book add    done  tested

read book works
write book done ; tested




triad coherand -length=N -scl={...} -scllen=N   -> done ; works.

prog coherand -extnum=N -extmax=N -scl={....} -scllen=N -> done ; works. 

syntaxcheking problem w degree progs  fixed.

fix triad coherand . DONE 


test smtool coherand -> done 

smtool wont support book read / print

 update example files . -> done

cast mallocs to look nicer :)  ; fix some flaws/issues (usage of memcpy() , strlen() n so on)

documentation update : far from finished
