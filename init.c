#include "triadgen.h"
#include "triadprint.h"
#include "globals.h"
#include "harmo.h"
#include "parsing.h"
#include "rand.h"
#include "scalegen.h"
#include "types.h"
#include "user_info.h"
#include "writeenv.h"
#include "dodecseries.h"
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

void init_saved_triads(S_SAVED_TRIAD* saved_triads){
	saved_triads->ch_prog=NULL;
	saved_triads->next=NULL;
}



void free_saved_triads( S_SAVED_TRIAD * saved_triads){
	if(!saved_triads) return;
	S_SAVED_TRIAD* tmp;
	while(saved_triads){
		tmp=saved_triads;
		if(tmp->ch_prog) free_triad_prog(tmp->ch_prog);
		saved_triads=saved_triads->next;
		free(tmp);
	}
}

void init_saved_dodec(S_SAVED_DODEC* saved_dodecs){
  //initialises a saved scale struct
  saved_dodecs->serie=0;
  saved_dodecs->next=NULL;
}

void free_saved_dodecs( S_SAVED_DODEC * saved_dodecs){
	if(!saved_dodecs) return;
	S_SAVED_DODEC* tmp;
	while(saved_dodecs){
		tmp=saved_dodecs;
		saved_dodecs=saved_dodecs->next;
		free(tmp);
	}
}

void init_userinfo( S_USERINFO* user_data){
  //initialises and allocates memory to the different pointers in the user_data structure
 //only call at the start of MusicTool otherwise can cause memleak

  user_data->saved_modes=malloc(sizeof(S_SAVED_MODES));// printf("saved modes pointer: %p\n", user_data->saved_modes);
  user_data->saved_scales=malloc(sizeof(S_SAVED_SCALES)); //printf("saved scale pointer: %p\n", user_data->saved_scales);
  user_data->saved_triads= malloc(sizeof(S_SAVED_TRIAD));
  user_data->saved_dodecs=malloc(sizeof(S_SAVED_DODEC));

  user_data->modes_num=0;
  user_data->scales_num=0;
  user_data->triads_num=0;
  user_data->dodec_num=0;

  init_saved_scale(user_data->saved_scales);
  init_saved_mode(user_data->saved_modes);
  init_saved_triads(user_data->saved_triads);
  init_saved_dodec(user_data->saved_dodecs);
}

void free_userinfo( S_USERINFO* user_info){
     free_saved_scale(user_info->saved_scales);
	 free_saved_modes(user_info->saved_modes);
	 free_saved_triads(user_info->saved_triads);
	 free_saved_dodecs(user_info->saved_dodecs);
	
	free(user_info);
}
