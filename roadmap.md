
function to init saved array;

then

function to clear a scale/ add a scale;


then do all of the parsing lmao

also do the front end -> like generate n save a stuff itll be a pain












stuff to add:


- possibility to save stuff n generate a scale n then save it to harmonise it
    on the implementation of saved mode:
            when u generate something it's automatically saved in a placeholder until u generate something else; if u type a command like 'savescale'; it should be saved in a struct n saved at an index
- possibility to acces said stuff w a command like generate_from_saved
-parse which saved stuff u want to use
-be able to clear saved stuff either all of it or a specific scale/mode



then continue to chord mode maybe?



then add the possibility to write down what u generate

16/09:

debugger init scale/ mode; faire fonctions d'accès o mode (le passer en argument pr autre chose etc)

ensuite faire le frontend de ca en ecrivant les fonction de parse

devoir pouvoir print chaque gamme etc

refaire gestion de sauvegarde avc realloc: faire une structure sauvegarde avc un pointeur de gamme et de truc harmonisé initialisé à 20 slots
avoir un compteur plein et si compt=20 faire un realloc de 10 slots 
