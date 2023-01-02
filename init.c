#include "chordgen.h"
#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



void init_saved_scale(S_SAVED_SCALES* saved_scales){
  //initialises a saved scale struct
  saved_scales->scale=0;
  saved_scales->next=NULL;
}

void free_saved_scale( S_SAVED_SCALES * saved_scales){
	if(!saved_scales) return;
	S_SAVED_SCALES* tmp;
	while(saved_scales){
		tmp=saved_scales;
		saved_scales=saved_scales->next;
		free(tmp);
	}
}


void init_saved_mode(S_SAVED_MODES* saved_modes){
	saved_modes->modes=NULL;
	saved_modes->next=NULL;
}



void free_saved_modes( S_SAVED_MODES * saved_modes){
	if(!saved_modes) return;
	S_SAVED_MODES* tmp;
	while(saved_modes){
		tmp=saved_modes;
		if(tmp->modes) free(tmp->modes);
		saved_modes=saved_modes->next;
		free(tmp);
	}
}

void init_saved_progs(S_SAVED_PROGS* saved_progs){
	saved_progs->ch_prog=NULL;
	saved_progs->next=NULL;
}



void free_saved_progs( S_SAVED_PROGS * saved_progs){
	if(!saved_progs) return;
	S_SAVED_PROGS* tmp;
	while(saved_progs){
		tmp=saved_progs;
		if(tmp->ch_prog) free_chord_prog(tmp->ch_prog);
		saved_progs=saved_progs->next;
		free(tmp);
	}
}

void init_userinfo( S_USERINFO* user_data){
  //initialises and allocates memory to the different pointers in the user_data structure
 //only call at the start of MusicTool otherwise can cause memleak
  
  //check causes unitialised value error in valgrind
 /* if(user_data==NULL) user_data=malloc(sizeof(S_USERINFO)) ;//printf("user_data pointer: %p\n", user_data);}
  if(user_data->saved_modes) free(user_data->saved_modes);
  if(user_data->saved_scales) free(user_data->saved_scales);*/

  user_data->saved_modes=malloc(sizeof(S_SAVED_MODES));// printf("saved modes pointer: %p\n", user_data->saved_modes);
  user_data->saved_scales=malloc(sizeof(S_SAVED_SCALES)); //printf("saved scale pointer: %p\n", user_data->saved_scales);
  user_data->saved_progs= malloc(sizeof(S_SAVED_PROGS));

  user_data->modes_num=0;
  user_data->scales_num=0;
  user_data->progs_num=0;

  init_saved_scale(user_data->saved_scales);
  init_saved_mode(user_data->saved_modes);
  init_saved_progs(user_data->saved_progs);
}

void free_userinfo( S_USERINFO* user_info){
     free_saved_scale(user_info->saved_scales);
	 free_saved_modes(user_info->saved_modes);
	 free_saved_progs(user_info->saved_progs);
	
	free(user_info);
}