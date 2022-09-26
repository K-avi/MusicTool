#include "user_info.h"
#include "types.h"
#include "init.h"
#include <stdlib.h>
#include <stdio.h>


// WARNING: NOT TESTED !!!!


void init_saved_scale(S_SAVED_SCALES* user_data, LENGTH  scale_tot){

  //reduntant w one of the functions in user_info.c

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

void init_saved_mode(S_SAVED_MODES* user_data, LENGTH  modes_tot){
    //dont remember what this does
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




S_SCALE* realloc_scales( S_USERINFO* user_data){
  //adds 10 slots for scales in memory when the scale array is full
  if( user_data->saved_scales->scale_tot+=10 >=100){
    printf("limit of savable scales reached. Please clear the scales\n" );
    return user_data->saved_scales->scales;
  }
  user_data->saved_scales->scale_tot+=10;
  return realloc(user_data->saved_scales->scales, (10*sizeof(S_SCALE)+ user_data->saved_scales->scale_tot*sizeof(S_SCALE)));


}


void clear_saved_data(S_USERINFO* user_data){ //  frees the saved data
    free(user_data->saved_modes->modes);
    free(user_data->saved_scales->scales);
    free(user_data->saved_modes);
    free(user_data->saved_scales);
    free(user_data);

}

void resets_saved_element(S_USERINFO * user_data, LENGTH struct_num, LENGTH element_of_struct){ //resets an element of a user saved struct; the index of the structure is passed as argument along with 0 or 1 to indicate wether it's the scale or the modes contained at this index that needs to be reset


    if (element_of_struct ==0){
           // init_scale(user_data[struct_num]->scale); //maybe use partial init idk

    }else if(element_of_struct==1){

      // init_modes(user_data[struct_num]->scale);
    }
}



void clear_saved_mode(S_SAVED_MODES * user_data){
  //not done yet
	free(user_data);
}



void save_scale( S_SCALE* user_data, S_USERINFO * user_info){
  //used to save a scale in the user data structure returns an error if the slots to save scales are all filled
  //to redo partially ; not tested

	if (user_info->saved_scales->scale_num ==user_info->saved_scales->scale_tot){

		user_info->saved_scales->scales=realloc_scales(user_info);
	}

	else if(user_info->saved_scales->scale_tot<user_info->saved_scales->scale_num){

		printf("error: the number of scales saved is higher than the memory allocated to save them. Please clear the save structure");
		return;

	}

	else{
    //highly doubt this works
		user_info->saved_scales->scales[user_info->saved_scales->scale_num++]= *user_data;
	}

}

void save_mode(S_MODES * user_data, S_SAVED_MODES *saved_modes){//used to save a mode in the data structure


}


void init_userinfo( S_USERINFO* user_data){
  //initialises and allocates memory to the different pointers in the user_data structure
  user_data->saved_modes=malloc(sizeof(S_SAVED_MODES));
  user_data->saved_scales=malloc(sizeof(S_SAVED_SCALES));

  init_saved_scale(user_data->saved_scales, 20);
  init_saved_mode(user_data->saved_modes, 20);
}
