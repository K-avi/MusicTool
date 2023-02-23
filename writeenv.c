#include "writeenv.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "triadprint.h"
#include "dodecseries.h"
#include "harmo.h"
#include "types.h"
#include "user_info.h"
#include "scalegen.h"
#include "chordprint.h"
#include "progbook.h"

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


void print_scl_env( S_USERINFO* uinfo){
   // if (!saved_scales) return; 

    printf("env scale (\n");
    S_SAVED_SCALES * tmp= uinfo->saved_scales->next;
   
    CPT i=1;
    while(tmp){
            printf("\n%d :",i++);
            if(tmp->scale){
             print_scale(tmp->scale); 
            }
            tmp=tmp->next;
        }
    
    printf(")\n");
}

void print_modes_env( S_USERINFO*uinfo){

    //if (!saved_modes) return; 
    printf("env scale (\n");
    S_SAVED_MODES * tmp= uinfo->saved_modes->next;

    CPT i=1;
    while(tmp){
        printf("\n%d :",i++);
        if(tmp->modes){
         print_modes(tmp->modes); 
        }
            tmp=tmp->next;
    }
    printf(")\n");
}

void print_triad_env (S_USERINFO*uinfo){
   // if(!saved_triads ) return; 

    S_SAVED_TRIAD * tmp= uinfo->saved_triads;
    if(!tmp) return;
    CPT i=1;
    tmp=tmp->next;
     printf("env triads (\n");
    if(tmp){
        while(tmp){
            printf("\n%d",i++);
            if(tmp->ch_prog){
                print_triad_prog(tmp->ch_prog); 
            }
            tmp=tmp->next;
        }
    }
    printf(")\n");
}

void print_chprog_env (S_USERINFO*uinfo){
   // if(!saved_triads ) return; 

    S_SAVED_PROG * tmp= uinfo->saved_prog;
    if(!tmp) return;
    CPT i=1;
    tmp=tmp->next;
     printf("env prog (\n");
    if(tmp){
        while(tmp){
            printf("\n%d",i++);
            if(tmp->chprog){
                print_chprog(tmp->chprog); 
            }
            tmp=tmp->next;
        }
    }
    printf(")\n");
}

void print_dodec_env (S_USERINFO*uinfo){
   // if(!saved_triads) return; 

    S_SAVED_DODEC * tmp= uinfo->saved_dodecs;
    if(!tmp) return;
    CPT i=1;
    tmp=tmp->next;
     printf("env dodec (\n");
    if(tmp){
        while(tmp){
            printf("\n%d",i++);
            if(tmp->serie){
                print_serie(tmp->serie); 
            }
            tmp=tmp->next;
        }
    }
    printf(")\n");
}

void print_book_env( PROGBOOK * pbook){
    if(!pbook) return;

   
    if( (!pbook->book) || (pbook->nbentries> pbook->maxentries)) return;
    printf("env book (\n");
    print_progbook(pbook);

    printf(")\n");
}

void fprint_book_env( FILE * f, PROGBOOK* pbook){

    if(!pbook) return;
    if( (!pbook->book) || (pbook->nbentries> pbook->maxentries)) return;
    fprintf(f,"env book (\n");
    if( (!pbook->book) || (pbook->nbentries> pbook->maxentries)) return;
    
    fprintf(f,"env book (\n");
    fprint_progbook(f,pbook);

    printf(")\n");
}

void print_env(S_USERINFO* user_info, PROGBOOK* pbook){
    if(!user_info) return;

    print_scl_env(user_info);
    print_modes_env(user_info); 
    print_triad_env(user_info);
    print_dodec_env(user_info);
    print_book_env(pbook);
}


bool fprint_env(FILE *f, S_USERINFO* user_info, PROGBOOK* pbook){
    
    if(!user_info) return 0;
    if(f==NULL) return 0;
    
    fprintf(f,"\nenv scale (\n");

    S_SAVED_SCALES * tmp= user_info->saved_scales;
    
    if(tmp){
        while(tmp){
            if(tmp->scale){
                fprint_scale(f,tmp->scale); 
            }
            tmp=tmp->next;
        }
    }
    fprintf(f,")\n");

    S_SAVED_MODES * tmp1= user_info->saved_modes;
     fprintf(f,"env harmo (\n");
    if(tmp1){
        while(tmp1){
            if(tmp1->modes){
                fprint_scale(f,tmp1->modes[0]); 
            }
            tmp1=tmp1->next;
        }
    }

    S_SAVED_TRIAD * tmp2= user_info->saved_triads;
     fprintf(f,")\nenv triad (\n");
    if(tmp2){
        while(tmp2){
            if(tmp2->ch_prog){
                fprint_triad_prog(f,tmp2->ch_prog); 
            }
            tmp2=tmp2->next;
        }
    }

    fprintf(f,")\nenv dodec (\n");

    S_SAVED_DODEC * tmp3= user_info->saved_dodecs;
    if(tmp3){
        while(tmp3){
            if(tmp3->serie){
                fprint_serie(f,tmp3->serie); 
            }
            tmp3=tmp3->next;
        }
    }


    S_SAVED_PROG * tmp4= user_info->saved_prog;
     fprintf(f,")\nenv prog (\n");
    if(tmp4){
        while(tmp4){
            if(tmp4->chprog){
                //printf("len is: %d\n", tmp4->chprog->length);
                fprint_chord_prog(f,tmp4->chprog); 
            }
            tmp4=tmp4->next;
        }
    }

    BOOKENTRY * tmp5= pbook->book;
     fprintf(f,")\nenv book (\n");
    if(tmp5){
      for(CPT cpt=0; cpt< pbook->nbentries; cpt++){
            fprint_book_entry(f,tmp5[cpt]);
      } 
    }

    
    fprintf(f,")\n");
    return 1;
}

bool write_env(char* filename , S_USERINFO* user_info, PROGBOOK* pbook){
    if(!user_info) return 0; 
    if(!filename) return 0;

    unsigned short k=0; 
    while(filename[k]==' ' && filename[k]!=10 && filename[k]!='\0'){ k++;}

    if(filename[k]=='\n' || filename[k]=='\0'){
      printf("please pass a filename as argument\n");
      return 0;
    }

    char* name_start= &filename[k];
    

    int i= strcspn(name_start, "\n"), j=strlen(name_start);
    
    char* clean_filename;
    if(i!=j){
        clean_filename = (char*) malloc(( j) * sizeof(char));
        memcpy(clean_filename, name_start,  j);
        clean_filename[i]='\0'; 

    }else {  clean_filename= strdup(name_start);}

    if(!access(clean_filename, F_OK)){
        FILE* f = fopen(clean_filename, "a+"); 
        char line[256] ;
        fgets(line, 256,f);
        if(strncmp(line, "MusicTool:environment", 18)){//checks that this is an environment file! 
            fclose(f) ;
            free(clean_filename);
            printf("error invalid file please pass a non existing file or a MusicTool:environment file as argument");
            return 0;
        }else{
            fprint_env(f, user_info, pbook);
            fclose(f);
        }

    }else{
        FILE* f= fopen(clean_filename, "w");
        if(!f){
            free(clean_filename);
            printf("error failed to create file; please try again\n");
            return 0;
        }
        fprintf(f,"MusicTool:environment\n");
        fprint_env(f, user_info, pbook);
        fclose(f);
    }
    free(clean_filename);
    printf("environment written succesfully!\n");
    return 1;
}

