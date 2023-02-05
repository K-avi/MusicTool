#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "triadgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"
#include "misc.h"
#include "parsing.h"
#include "chordgen.h"
#include "chordprint.h"
#include <stdarg.h>
#include <string.h>





TRIADS_IN_SCALE select_rand_triads(TRIADS_IN_SCALE triads){//selects a random triads in a TRIADS_IN_SCALE struct
  
  if(!triads) return 0;
  if( triads==1 || triads== 2 || triads== 4 || triads==8 || triads==16 || triads== 32) {return  triads;} // case if only one triad

  LENGTH length=count_bits(triads);

  int select=rand()%length+1;
  
  CPT cpt=0, incr=0, ret=0;
  while(cpt < select ){
    if( 1 & (triads>>incr)) {  ret=incr; cpt++;}
    incr++;
  }
  return (1<<ret);
}//not tested 

PITCH_CLASS_SET select_rand_degree( PITCH_CLASS_SET deg){//selects ONE random degree in a PITCH_CLASS_SET short

  if(!deg) return 0;
  LENGTH length= count_bits(deg);
  if(length==1) return deg; 

  unsigned rand_deg= (rand()%(length))+1;
  
  return (1<<nth_bit_pos(deg, rand_deg));
}//tested




S_TRIAD_PROG* generate_chord_prog(S_SCALE scale, LENGTH length){ //generates a random chord prog of length length 


    print_scale(scale);
    if (!scale || !length) return NULL;
    PITCH_CLASS_SET deg_w_chord= get_degrees(scale);
    //_bits(deg_w_chord);
    

    if(!deg_w_chord ) return NULL;

    S_TRIAD_PROG* ret= malloc(sizeof(S_TRIAD_PROG));
    ret->length= length;
    ret->chord_prog= malloc(length* sizeof(TRIAD));

    if(count_bits(deg_w_chord)==1){ //case if u can only generate 1 chord from a scale 
      
      
      INDEX index= nth_bit_pos(deg_w_chord ,1); //retrieves the index of the relevent degree
      S_SCALE relev_mode= rot(scale, index);//retrieves the mode of said degree
    
      TRIADS_IN_SCALE triads= triads_at_fund(relev_mode);
      if(count_bits(triads)==1){
        for(CPT i=0; i<length; i++){

          TRIADS_IN_SCALE triad_selected= select_rand_triads(triads);//selects a random triad on the degree 
          ret->chord_prog[i]= generate_chord(triad_selected, deg_w_chord);
        }
      }else{

        TRIADS_IN_SCALE curtriads= select_rand_triads(triads);
        TRIADS_IN_SCALE prevtriads= curtriads;

        for(CPT i=0; i<length; i++){

          curtriads= select_rand_triads(triads);//selects a random triad on the degree 

          while(curtriads==prevtriads){
              
              curtriads=select_rand_triads(triads);
            }
            prevtriads=curtriads;

          ret->chord_prog[i]= generate_chord(curtriads, deg_w_chord);
        }
      }
      
    }else{//u can generate two or more chords

        PITCH_CLASS_SET curdeg= select_rand_degree(deg_w_chord);
        S_SCALE curmode = rot(scale , nth_bit_pos(curdeg, 1));//bad bc I calculate index multiple times
        //i should change the design so that i get an index that I use to get the triads n stuff
        TRIADS_IN_SCALE curtriads= triads_at_fund(curmode);
        TRIADS_IN_SCALE seltriads= select_rand_triads(curtriads);

        PITCH_CLASS_SET prevdeg=curdeg;

        for(CPT i=0; i<length; i++){

            
           //print_bits(deg_w_chord);
            curdeg=select_rand_degree(deg_w_chord);
            while(curdeg==prevdeg){
              
              curdeg=select_rand_degree(deg_w_chord);
            }
            prevdeg=curdeg;

            //printf("%b", curdeg);
            curmode=rot(scale , nth_bit_pos(curdeg, 1));

           // print_scale(curmode);
            curtriads=triads_at_fund(curmode);
            seltriads= select_rand_triads(curtriads);
           // print_bits(curtriads);
            
            ret->chord_prog[i]= generate_chord(seltriads, curdeg);     
        }

    }
    return ret;
}


CHORD ext_gen_chord  (CHORD chord, CPT extension_num, CPT extension_total, TRIADS_IN_SCALE triad){
    //erases randoms extensions from chord in order to keep extension_num extensions. 
    //returns chord if extension_total < extension_num 
    //triad is used to pop out n in the triad from chord 

    //various validity checks
    if(!chord ) return 0; 
    if(extension_total>9 ) return 0;
    if(extension_num > extension_total) return 0;

    //extension_total is also the lentgth of the scale in chord (how many bits set n so on)
    if(extension_total==0) return chord;
    S_EXTENSIONS chord_extension= chord>>4; 

    chord_extension= pop_triad(chord_extension, triad_in_scl_to_triad_bits(triad));
    unsigned char rand_index= nth_bit_pos( chord_extension, rand()%extension_total+1);

    for(CPT i=0; i<extension_total-extension_num; i++){
        chord_extension= POP_BIT( chord_extension, rand_index);
        rand_index= nth_bit_pos( chord_extension, rand()%(extension_total-i)+1);

    }
    CHORD ret=  chord & 0xF;
    chord_extension=pop_triad(chord_extension, triad_in_scl_to_triad_bits( triad));
    ret|= chord_extension<<4;
    return ret; 

}//problem cuz it can kill the triad which is real bad
//this function is: awful 



S_CHPROG* generate_ext_chprog( char * args){
   /*
   should be able to take arguments 
  -length=n | rand
  -scllen=n | rand 
  -scale={...} | rand 
  -extnum=1...n | rand ; should be made more complete after that (like min ext max ext etcs)
   */
  if(!args){/*generation without arguments is gonna be goofy; I don't 
  want it to rely on a specific scale. It's gonna change scale at each chord because I said so*/

      LENGTH proglength= rand()%10+1; //proglength between 1 and 10 

      S_SCALE scl= 0;//scl of min length 6 to make sure a chord can be generated
      CPT extension_num=0; 
      
      CHORD curchord= 0; //chord to pop extensions from 

      PITCH_CLASS_SET relevant_deg= 0; //gets deg of scl 
      PITCH_CLASS_SET selected_deg= 0;
      DEGREES selected_deg_converted= 0;

      S_SCALE curmode = 0;
      TRIADS_IN_SCALE curtriads= 0;
      TRIADS_IN_SCALE seltriads= 0;
  
      S_CHPROG *ret=  malloc( sizeof(S_CHPROG));
      ret->chprog= malloc(proglength* sizeof( CHORD));
      ret->length=proglength;

      for(CPT i=0; i<proglength; i++){
          
        scl=generate_ran_scale( 8);
        extension_num=count_bits(scl)-2;

        relevant_deg=get_degrees(scl); 
        selected_deg= select_rand_degree(relevant_deg);
        selected_deg_converted= get_deg_from_chdeg(selected_deg);
        
        curmode= rot( scl, nth_bit_pos(selected_deg, 1));

        curtriads=triads_at_fund(curmode); 
        seltriads=select_rand_triads(curtriads);

        curchord=selected_deg_converted | (curmode <<4);
      
        if(extension_num){
          curchord= ext_gen_chord(curchord, rand()%extension_num, extension_num, seltriads);
        }else { 
          curchord= ext_gen_chord(curchord, 0, 0, seltriads);
        }

        ret->chprog[i] = curchord;
      }
      return ret;
      
  }else{ 
      

      CPT i=0 ;
      char* tmp=args;
      LENGTH proglength=0, scllen=0;
      char extension_num=-1;
      char extension_max=-1;
     
      S_SCALE scl=0;

      while (!END_OF_LINE_CHAR(*tmp)) {//retrieves the arguments for generation. 
        
        if(!strncmp(tmp, "-length=",8)){
            tmp+=8;
            if(isdigit(*(tmp))){
              proglength=atoi(tmp); 
            }
        }else if(!strncmp(tmp, "-scllen=", 8)){
            tmp+=8;
            if(isdigit(*(tmp))){
              scllen=atoi(tmp); 
            }
        }else if(!strncmp(tmp, "-extnum=", 8)){  
            tmp+=8;
            if(isdigit(*(tmp))){
              extension_num= atoi(tmp);
            }
          
        }else if(!strncmp(tmp, "-extmax=", 8)){  
        //  printf("-extmax spotted\n");
            tmp+=8;
            if(isdigit(*(tmp))){
              extension_max= atoi(tmp);
            }
          
          //printf("%d\n", extension_max);
        
       }else if(!strncmp(tmp, "-scl=", 5)){  
            tmp+=5;    
            scl=parse_scale(tmp);
        }else{//default behavior for invalid args is to ignore them; might be bad dunno
            tmp++;
        }
      }


      if(scl && scllen) scllen=0; /*scl and scllen are mutually exclusive; scl is more important I think.
      this behavior might change idk yet*/

      if(extension_max!=-1 && extension_num!=-1){//exension_num is privileged over extension_max bc I said so
        extension_max=-1;
      }
      

      if(scllen){ //sets scl if scllen is set 
        if(scllen<7){

          if(scllen<3){ return NULL;}
          TRIADS_IN_SCALE triad= select_rand_triads(0x3F); //selects a random triad;
         
          scl= triad_in_scl_to_chord(triad);    
        
          for(CPT i =0; i<(scllen-3); i++){
            add_rand_note(&scl);
          }
        }else if (scllen<12){
          scl=generate_ran_scale(scllen);
        }else{ 
          scl=0x7FF;
        }
      }else if(!scl){ //sets scale if not the case
        scl=generate_ran_scale(rand()%4+7);
      }

      if(!proglength){
        proglength=rand()%10+1;
      }

      CPT extension_total= count_bits(scl)-2;
      extension_total= extension_total<0 ? 0 : extension_total; //prevents it from being negative
      CHORD curchord= 0 ,prevchord=0;  //chord to pop extensions from 

      PITCH_CLASS_SET relevant_deg= get_degrees(scl); //gets deg of scl 
      if(!relevant_deg) return NULL; //case if scale doesnt contain any chords

      PITCH_CLASS_SET selected_deg= 0;
      DEGREES selected_deg_converted= 0;

      S_SCALE curmode = 0;
      TRIADS_IN_SCALE curtriads= 0;
      TRIADS_IN_SCALE seltriads= 0;
       
  
      S_CHPROG *ret=  malloc( sizeof(S_CHPROG));
      ret->chprog= malloc(proglength* sizeof( CHORD));
      ret->length=proglength;
  
      if( (count_bits(relevant_deg)==1 && extension_total==0) ){ //case when 1 chord only can be generated
         selected_deg=select_rand_degree(relevant_deg);
         curmode= rot( scl, nth_bit_pos(selected_deg, 1));
         curtriads=triads_at_fund(curmode); 
      
         seltriads=select_rand_triads(curtriads);
         curchord=selected_deg_converted | (curmode <<4);
         for(CPT i=0; i<proglength; i++){
            ret->chprog[i] = curchord;
         }
      }else{ //1 or more chord can be generated 
      
          for(CPT i=0; i<proglength; i++){

            selected_deg= select_rand_degree(relevant_deg);
            selected_deg_converted= get_deg_from_chdeg(selected_deg);
            
            curmode= rot( scl, nth_bit_pos(selected_deg, 1));
            curtriads=triads_at_fund(curmode); 
      
            seltriads=select_rand_triads(curtriads);
            curchord=selected_deg_converted | (curmode <<4);

            if(extension_total ){

              if(extension_num!=-1){
                
                if(!extension_num){
              
                  curchord= ext_gen_chord(curchord,0 , extension_total, seltriads);
                  if(prevchord==curchord){
                    while(prevchord==curchord){
                        curchord= ext_gen_chord(curchord,0 , extension_total, seltriads);
                    }
                  }
                }else{
                  extension_num= extension_num>extension_total ? extension_total: extension_num;  
                  curchord= ext_gen_chord(curchord, extension_num, extension_total, seltriads);
                 // print_ext_chord(curchord);
                  if( prevchord==curchord ){
                    while(prevchord==curchord){
                      //printf("uhoh\n");
                       selected_deg= select_rand_degree(relevant_deg);
                       selected_deg_converted= get_deg_from_chdeg(selected_deg);
                        
                       curmode= rot( scl, nth_bit_pos(selected_deg, 1));
                       curtriads=triads_at_fund(curmode); 
                  
                       seltriads=select_rand_triads(curtriads);
                       curchord=selected_deg_converted | (curmode <<4);
                       curchord= ext_gen_chord(curchord, extension_num, extension_total, seltriads);
                    }
                  }
                }
              }else if (extension_max!=-1){
                if(!extension_max){
                
                  curchord= ext_gen_chord(curchord,0 , extension_total, seltriads);
                  if(prevchord==curchord){
                    while(prevchord==curchord){
                        selected_deg= select_rand_degree(relevant_deg);
                       selected_deg_converted= get_deg_from_chdeg(selected_deg);
                        
                       curmode= rot( scl, nth_bit_pos(selected_deg, 1));
                       curtriads=triads_at_fund(curmode); 
                  
                       seltriads=select_rand_triads(curtriads);
                       curchord=selected_deg_converted | (curmode <<4);
                        curchord= ext_gen_chord(curchord,0 , extension_total, seltriads);
                    }
                  }
                }else{
                  extension_max= extension_max>extension_total ? extension_total: extension_max;  
                  curchord= ext_gen_chord(curchord, (rand() % (extension_max + 1)) , extension_total, seltriads);
                  if(prevchord==curchord){
                    while(prevchord==curchord){
                      selected_deg= select_rand_degree(relevant_deg);
                       selected_deg_converted= get_deg_from_chdeg(selected_deg);
                        
                       curmode= rot( scl, nth_bit_pos(selected_deg, 1));
                       curtriads=triads_at_fund(curmode); 
                  
                       seltriads=select_rand_triads(curtriads);
                       curchord=selected_deg_converted | (curmode <<4);
                      curchord= ext_gen_chord(curchord, (rand()% (extension_max+1)), extension_total, seltriads);
                      }
                    }
                } 
              }else {
                
                curchord= ext_gen_chord(curchord, (rand()% (extension_total+1)), extension_total, seltriads);
                if(prevchord==curchord){
                  while(prevchord==curchord){
                     selected_deg= select_rand_degree(relevant_deg);
                       selected_deg_converted= get_deg_from_chdeg(selected_deg);
                        
                       curmode= rot( scl, nth_bit_pos(selected_deg, 1));
                       curtriads=triads_at_fund(curmode); 
                  
                       seltriads=select_rand_triads(curtriads);
                       curchord=selected_deg_converted | (curmode <<4);
                      curchord= ext_gen_chord(curchord, (rand()% (extension_total+1)), extension_total, seltriads);
                  }
                }
              }
            }else{
       
              curchord= ext_gen_chord(curchord, 0, 0, seltriads);
              if(prevchord==curchord){
                while(prevchord==curchord){
                  selected_deg= select_rand_degree(relevant_deg);
                       selected_deg_converted= get_deg_from_chdeg(selected_deg);
                        
                       curmode= rot( scl, nth_bit_pos(selected_deg, 1));
                       curtriads=triads_at_fund(curmode); 
                  
                       seltriads=select_rand_triads(curtriads);
                       curchord=selected_deg_converted | (curmode <<4);
                    curchord= ext_gen_chord(curchord, 0, 0, seltriads);
                }
              }
            }
          

            ret->chprog[i] = curchord;
            prevchord=curchord;
          }
      }
      return ret;
  }
  return NULL;
}//needs to prevent it from generating the same chord twice bc it's kinda dumb