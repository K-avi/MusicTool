#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


bool QUIT_INFO; //failsafe;  to be set to true when starting the program; will prevent the program from running if set to false; might not use

void init_scale( S_SCALE * scale ){ //initializes the length of a scale to 1; sets it's first note to the fundamental and fills it with the value 13 as placeholder


    int i;
    for(i=1; i<12; i++){

        scale->scale[i]= 13;

    }

    scale->length=1;
    scale->scale[0]=0;
}

void partial_init_scale( S_SCALE*scale){ //initialises the length of the scale to 0; fills it with the value 13 as a placeholder


    int i;
    for(i=0; i<12; i++){
        scale->scale[i]= 13;

    }
    scale->length=0;

}

void init_modes(S_MODES * modes){ //initialises the length of the structure to 1; set the first note of every scale to 0 and fills the rest with the value 13 as placeholder

    int i, j;

    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
                modes->scale[i][j]=(j==0)? 0: 13;
        }
    }
    modes->length=1;
}

void partial_init_modes( S_MODES * modes){ ////initialises the length of the structure to 0; fills it with the value 13 as a placeholder

    int i, j;

    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
            modes->scale[i][j]=13;
        }
    }
    modes->length=0;
}


void clear_saved_scale(S_SAVED_SCALES * user_data){
	free(user_data);
}

void init_saved_scale(S_SAVED_SCALES* user_data, LENGTH  scale_tot){
	
	free(user_data);
	user_data=malloc(sizeof(S_SAVED_SCALES));
	user_data->scales=malloc(scale_tot*sizeof(S_SCALE));
	user_data->scale_tot= scale_tot;
	user_data->scale_num= 0;
	
	int i;
	for(i=0; i<scale_tot; ++i){
		
		init_scale(user_data->scales++);
	}
	
}

void clear_saved_mode(S_SAVED_MODES * user_data){
	free(user_data);
}

void init_saved_mode(S_SAVED_MODES* user_data, LENGTH  modes_tot){
	
	free(user_data);
	user_data=malloc(sizeof(S_SAVED_MODES));
	user_data->modes=malloc(modes_tot*sizeof(S_MODES));
	user_data->mode_tot= modes_tot;
	user_data->mode_num= 0;
	
	int i;
	for(i=0; i<modes_tot; ++i){
		
		init_modes(user_data->modes++);
	}
	
}

void save_scale( S_SCALE* user_data, S_SAVED_SCALES* saved_scales){ //used to save a scale in the user data structure returns an error if the slots to save scales are all filled

	if (saved_scales->scale_tot ==saved_scales->scale_tot){
		
		printf("maximal number of scale reached");
		return;

	}
	
	else if(saved_scales->scale_tot<saved_scales->scale_num){
		
		printf("error: the number of scales saved is higher than the memory allocated to save them. Please clear the save structure");
		return;
		
	}
	
	else{
		
		saved_scales->scales[saved_scales->scale_num++]=user_data;
	}

}

void save_mode(S_MODES * user_data, S_SAVED_MODES *saved_modes){//used to save a mode in the data structure 
	

}








