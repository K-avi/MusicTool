#include "coherand.h"
#include "chordgen.h"
#include "harmo.h"
#include "misc.h"
#include "parsing.h"
#include "rand.h"
#include "scalegen.h"
#include "triadgen.h"
#include "triadprint.h"
#include "progbook.h"
#include "bitop.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

PART : transformations from book to prog / prog to prog n so on

*/

PITCH_CLASS_SET chprog_degs_to_pcs_relev_deg(S_CHPROG *prog){
    /*
    returns the PCS containing the degrees of a chord. This isn't the same as 
    returning the pcs containing the PCS containing every note of the prog. 
    What this does is that it only includes the degrees w/o caring about which triad
    /extensions the chord has.
    */
    if(!prog) return 0;
    if(!prog->chprog) return 0;
    PITCH_CLASS_SET ret=0;
    for (CPT i=0; i<prog->length; i++){
        ret|= 1<<(prog->chprog[i]& 0xF); //retrieves degree n turns it into a PCS element.
    }
    return ret;
}//usefull when checking if a prog is in the saved book; not tested  


PITCH_CLASS_SET triad_degs_to_pcs_relev_deg(S_TRIAD_PROG *prog){
    /*
    returns the PCS containing the degrees of a chord. This isn't the same as 
    returning the pcs containing the PCS containing every note of the prog. 
    What this does is that it only includes the degrees w/o caring about which triad
    /extensions the chord has.
    */
    if(!prog) return 0;
    if(!prog->chord_prog) return 0;
    PITCH_CLASS_SET ret=0;
    for (CPT i=0; i<prog->length; i++){
        ret|= 1<<(prog->chord_prog[i]& 0xF); //retrieves degree n turns it into a PCS element.
    }
    return ret;
}//usefull when checking if a prog is in the saved book; not tested  


S_DEGREE_PROG* build_deg_prog_from_deg_array( BOOK_LENGTH_TABLE * table, LENGTH proglength ){
    /*
    builds a degree prog of the length passed as argument usinf the relevant indexes in a progbook. 

    The fact that any prog of length n CAN be generated with this is assumed?? 
    returns NULL if error/ problem 
    */

    if(!(table&& proglength)) return NULL;
    if(!(table->book_arrays && table->nbentries)) return NULL;
  

    S_DEGREE_PROG* ret_prog=NULL;
    

    PITCH_CLASS_SET length_availables=0;  //which deg can I generate ? 
    CPT nb_length_availables=0;

    for(CPT i=0; i<12; i++){
        if( table->book_arrays[i]){ 
            length_availables|=(1<<i);
            nb_length_availables++;
        }
    }

    /*
    should be really carefull of the generation loop cuz I don't want to fuck things up. 
    I think I'll make it so if there is no 1 degree that u can generate u just exit 
    */
    if(!( length_availables & 1) ) return NULL; //makes SURE that u can generate a prog of length 1 to be able to generate
    //a prog from any entry

    ret_prog= (S_DEGREE_PROG*) malloc(sizeof(S_DEGREE_PROG));
    ret_prog->degree_prog= (unsigned char* ) calloc(proglength, sizeof(unsigned char));

    ret_prog->length=proglength;

    LENGTH curlength=0, sumlength=0;
    BOOKENTRY cur_sel=0, prev_sel=0; 
    INDEX ret_index=0; //to keep track of ret's indexes 

    curlength= nth_bit_pos(length_availables, (rand()%nb_length_availables)+1);
    if(length_availables==1 && table->book_arrays[0]->nbentries==1){

        cur_sel= table->book_arrays[0]->book[0];
        cur_sel= ( (cur_sel >> 16) & 0xF) -1;
        while(curlength<proglength){
            
            ret_prog->degree_prog[ret_index++]= cur_sel;
            curlength++;
        }
    
        
    }else while(curlength<proglength){

        if(ret_index > ret_prog->length-1) break;

        curlength= nth_bit_pos(length_availables, ((rand()%nb_length_availables)+1)%proglength);

        if(sumlength+proglength> ret_prog->length) continue;

        cur_sel=table->book_arrays[curlength]->book[rand()%table->book_arrays[curlength]->nbentries]; //ugly af
        
        
        if(ret_index){ //makes sure that stuff doesnt repeat. 
            if( (ret_prog->degree_prog[ret_index-1] & 0xF )== ( ((cur_sel >>16 )& 0xF)-1)) continue;
        }

        for(CPT i=0; i<curlength+1 ; i++){
            if(ret_index > ret_prog->length-1) break;
            ret_prog->degree_prog[ret_index]= (((cur_sel) >> (16+(4*i)) ) & 0xF) -1; //stores each degree in ret_prog
            ++ret_index;
        }   

        proglength-=curlength;
        sumlength+=curlength;
    }
    return ret_prog; 
}

void print_degree_prog( S_DEGREE_PROG* degprog){

    if(!degprog) return;
    if(!degprog->degree_prog) return;
    printf("[ ");
    for(CPT i=0; i<degprog->length; i++){
        printf("%s ", bits_deg_to_str(degprog->degree_prog[i]));
    }
    printf(" ]\n");
}


S_TRIAD_PROG * degree_prog_to_triad_prog( S_DEGREE_PROG * prog, S_SCALE scale){
    /*
    turns a generic degree prog into a triad prog. Selects a random triad from scale at each deg of relev 
    degs.
    */
    if(! (prog && scale )) return  NULL;
    if( (!prog->degree_prog) || (!scale) || (!prog->length) ) return NULL;


    S_TRIAD_PROG * ret = (S_TRIAD_PROG *) malloc(sizeof(S_TRIAD_PROG));
    ret->chord_prog = (unsigned char *) malloc(prog->length* sizeof(unsigned char) );
    ret->length=prog->length;

    TRIADS_IN_SCALE all_triads=0;

    S_SCALE curmode=0;

    
    for (CPT i=0; i<prog->length; i++){

        ret->chord_prog[i]= prog->degree_prog[i];
        
        curmode= rot(scale , prog->degree_prog[i]);
        all_triads=triads_at_fund(curmode);

        ret->chord_prog[i]|= triad_in_scl_to_triad_bits( select_rand_triads(all_triads))<<4;
        
    }

    return ret;
}


S_CHPROG * degree_prog_to_chprog( S_DEGREE_PROG * prog, S_SCALE scale){
    /*
    turns a generic degree prog into a chord prog. Selects a random triad from scale at each deg of relev 
    degs.
    */
    if(! (prog && scale )) return  NULL;
    if( (!prog->degree_prog) || (!scale) || (!prog->length) ) return NULL;


    S_CHPROG * ret = (S_CHPROG*) malloc(sizeof(S_CHPROG));
    ret->chprog = (CHORD*) malloc(prog->length* sizeof(CHORD) );
    ret->length=prog->length;


    S_SCALE curmode=0;

    //print_scale(scale);

    for (CPT i=0; i<prog->length; i++){
        
        ret->chprog[i]= prog->degree_prog[i];
        
        curmode= rot(scale , prog->degree_prog[i]);
        //printf("i is %d, progdeg is %d \n", i, prog->degree_prog[i]);
        print_scale(curmode);

        ret->chprog[i]|=  (curmode )<<4;
    }

    return ret;
}//tested; works; doesnt pop extensions though

CHORD pop_extensions (CHORD chord , CPT num_ext ){
    /*
    pop num ext extensions from chord. or as many it can if num_ext > number of extensions in chord
    */
    DEGREES_BITS deg_chord= chord & 0xF;
    S_EXTENSIONS ch_ext=  (chord  & (~0xF)) >>4;

   // printf("ch_ext is :\n");
   // print_scale(ch_ext);

    TRIADS_BITS popped_triad = triad_in_scl_to_triad_bits(select_triad(ch_ext<<4));
    //printf("popped is %d\n", popped_triad);
    ch_ext =  pop_triad (ch_ext, popped_triad);

   /*printf("ch_ext after pop is :\n");
    print_scale(ch_ext);*/

    LENGTH l= count_bits(ch_ext);

    CPT num_to_pop= (l - num_ext >= 0) ? num_ext : l ;

    CHORD ret= deg_chord;
    
    for (CPT i=0; i<num_to_pop ; ++i ){
       // if(l==0) break;
        ch_ext = POP_BIT( ch_ext,  nth_bit_pos(ch_ext , (rand()%l)+1 )   );

       // print_scale(ch_ext);
        l--;
    }

    ch_ext = pop_triad( ch_ext, popped_triad);
   
    ret |= ch_ext<<4;
    return ret; 
}

void pop_prog_extensions( S_CHPROG* chprog, CPT num_ext){
    /*
    pops precisely num_ext extensions at each degree of 
    chprog.
    */
    if( ! chprog) return; 
    if( !chprog->chprog) return;

    for (CPT i=0 ; i<chprog->length; i++){
        chprog->chprog[i]= pop_extensions(chprog->chprog[i], num_ext);
    }
}

void pop_prog_extensions_rand( S_CHPROG* chprog){
    /*
    pops a random num of extensions at each degree of chprog passed as arg.
    */
    if( ! chprog) return; 
    if( !chprog->chprog) return;

    for (CPT i=0 ; i<chprog->length; i++){
        chprog->chprog[i]= pop_extensions(chprog->chprog[i], rand()%count_bits(chprog->chprog[i]>>4)-2);
    }
}


void set_options( char * str, unsigned char mode , char* extnum, char* extmax, S_SCALE *scl, LENGTH *length , LENGTH * scllen){
/*
sets the options passed as arguments to options in a string. 
implementation is : awful but I just want to get 1.3.2 done. 
I'll make it ok at some point n I apologize for the shitty code.
mode 'p' is for prog n allows acces to extnum, extmax
*/  
    if( ! (str && extnum && extmax && scl && length && scllen)) return ;

    char *tmp=NULL; 

    tmp=strstr(str, "-scl=");

    if(tmp){
        *scl=parse_scale(tmp);
    }else{
        tmp=strstr(str, "-scllen=");
        if(tmp){
            tmp+=9;
            *scllen=atoi(tmp);
        }
    }

    tmp=strstr(str, "-length=");

    if(tmp){
        *length=atoi(tmp+9);
    }

    if(mode=='p'){
        tmp= strstr(str, "-extnum=");
        if(tmp){
            *extnum= atoi(tmp+9);
        }else{
            tmp=strstr(str, "-extmax=");
            if(tmp){
                *extmax= atoi(tmp+9);
            }
        }
    }
}


S_CHPROG* coherand_prog(PROGBOOK* pbook , S_SCALE scl, char extmax, char extnum, LENGTH length, LENGTH scllen){
    if(!pbook ) return NULL;

    LENGTH gen_scllen= scl ? 0 : scllen ? scllen : rand()%3 +7;
    S_SCALE gen_scl= scl ? scl : generate_ran_scale(gen_scllen);

    LENGTH gen_length= length ? length : rand()%10+1;

    S_CHPROG* ret= NULL;
    BOOK_LENGTH_TABLE * table = progbook_constrained_to_book_length(pbook, get_degrees(gen_scl));
    S_DEGREE_PROG * prog= build_deg_prog_from_deg_array(table , gen_length);

    free_book_table(table); 

    ret= degree_prog_to_chprog(prog , gen_scl);

    free_degree_prog(prog);

    if(extnum){

        pop_prog_extensions(ret, extnum);        
    }else if(extmax){
        
        pop_prog_extensions(ret , rand()%extmax);

    }else{
        pop_prog_extensions_rand(ret);

    }   
   
    return ret; 
}

S_TRIAD_PROG* coherand_tri(PROGBOOK* pbook , S_SCALE scl, LENGTH length, LENGTH scllen){
    if(!pbook) return NULL;
    

    LENGTH gen_scllen= scl ? 0 : scllen ? scllen : rand()%3 +7;
   
    S_SCALE gen_scl= scl ? scl : generate_ran_scale(gen_scllen);

    LENGTH gen_length= length ? length : rand()%10+1;

    S_TRIAD_PROG* ret= NULL;
    
     printf("in coherand triad genscl is %d, gen scllen is %d gen length is %d\n", gen_scl, gen_scllen, gen_length);
    BOOK_LENGTH_TABLE * table = progbook_constrained_to_book_length(pbook, get_degrees(gen_scl));
    S_DEGREE_PROG * prog= build_deg_prog_from_deg_array(table , gen_length);
    

    printf("prog is:\n");
    print_degree_prog(prog);

    free_book_table(table); 

    ret= degree_prog_to_triad_prog(prog , gen_scl);

    free_degree_prog(prog);

    return ret; 
}