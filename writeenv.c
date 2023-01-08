#include "writeenv.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "chordprint.h"
#include "harmo.h"
#include "user_info.h"
#include "scalegen.h"


#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif



void print_env(S_USERINFO* user_info){
    if(!user_info) return;

    printf("env scale (\n");

    S_SAVED_SCALES * tmp= user_info->saved_scales;

   
    if(tmp){
        while(tmp){
            printf("%d",tmp->scale);
            if(tmp->scale){
             print_scale(tmp->scale); 
            }
            tmp=tmp->next;
        }
    }
    printf(")\n");

    S_SAVED_MODES * tmp1= user_info->saved_modes;
    
  
    printf("env harmo (\n");
    if(tmp1){
        while(tmp1){
            if(tmp1->modes){
                print_scale(tmp1->modes[0]); 
            }
            tmp1=tmp1->next;
        }
    }
    printf(")\n");

    S_SAVED_PROGS * tmp2= user_info->saved_progs;
    if(!tmp2) return;
    tmp2=tmp2->next;
     printf("env chprog (\n");
    if(tmp2){
        while(tmp2){
            if(tmp2->ch_prog){
                print_chord_prog(tmp2->ch_prog); 
            }
            tmp2=tmp2->next;
        }
    }
    printf(")\n");

}


bool fprint_env(FILE *f, S_USERINFO* user_info){
    
    if(!user_info) return 0;
    if(f==NULL) return 0;

    fprintf(f,"env scale (\n");

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
    fprintf(f,")\n");

    S_SAVED_PROGS * tmp2= user_info->saved_progs;
     fprintf(f,"env chprog (\n");
    if(tmp2){
        while(tmp2){
            if(tmp2->ch_prog){
                fprint_chord_prog(f,tmp2->ch_prog); 
            }
            tmp2=tmp2->next;
        }
    }
    fprintf(f,")\n");
    return 1;
}

bool write_env(char* filename , S_USERINFO* user_info){
    if(!user_info) return 0; 
    if(!filename) return 0;

    ushort k=0; 
    while(filename[k]==' ' && filename[k]!=10 && filename[k]!='\0'){ k++;}

    if(filename[k]=='\n' || filename[k]=='\0'){
      printf("please pass a filename as argument\n");
      return 0;
    }

    char* name_start= &filename[k];
    

    int i= strcspn(name_start, "\n"), j=strlen(name_start);
    
    char* clean_filename;
    if(i!=j){
        clean_filename = malloc(( j) * sizeof(char));
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
            fprint_env(f, user_info);
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
        fprint_env(f, user_info);
        fclose(f);
    }
    free(clean_filename);
    printf("environment written succesfully!\n");
    return 1;
}

