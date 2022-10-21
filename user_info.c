#include "user_info.h"
#include "types.h"
#include "init.h"
#include "scalegen.h"
#include "copy.h"
#include <stdlib.h>
#include <stdio.h>


void init_saved_scale(S_SAVED_SCALES* user_data, LENGTH  scale_tot){
  //initialises a saved scale struct

	free(user_data);
	user_data=malloc(sizeof(S_SAVED_SCALES));
	user_data->scales=malloc(12*scale_tot*sizeof(S_SCALE));
	user_data->scale_tot= scale_tot;
	user_data->scale_num= 0;

	int i;
	for(i=0; i<scale_tot; i++){
		user_data->scales[i]=malloc(sizeof(S_SCALE));
		init_scale(user_data->scales[i]);
	}

}


S_SCALE** realloc_scales( S_USERINFO* user_data){ // NOT TESTED 	!!!!!!!
  //adds 10 slots for scales in memory when the scale array is full; returns a pointer to the new emplacement of the scale
  if( user_data->saved_scales->scale_tot+=10 >=100){
    printf("limit of savable scales reached. Please clear the scales\n" );
    return user_data->saved_scales->scales;
  }
  user_data->saved_scales->scale_tot+=10;
	
  return realloc(user_data->saved_scales->scales, (10*sizeof(S_SCALE)+ user_data->saved_scales->scale_tot*sizeof(S_SCALE)));


}


void save_scale( S_SCALE* user_data, S_USERINFO * user_info){
  //used to save a scale in the user data structure returns an error if the slots to save scales are all fille

	if (user_info->saved_scales->scale_num ==user_info->saved_scales->scale_tot){
		printf("scale struct fyll; scales reallocated");
		user_info->saved_scales->scales=realloc_scales(user_info);
	}

	else if(user_info->saved_scales->scale_tot<user_info->saved_scales->scale_num){

		printf("error: the number of scales saved is higher than the memory allocated to save them. Please clear the save structure");
		return;

	}

	else{

		copy_scale(user_info->saved_scales->scales[user_info->saved_scales->scale_num++], user_data);
	}

}


void print_saved_scale( S_USERINFO * user_data, LENGTH index){// could be a macro tbh
	//doesnt check for bad allocation !!!!!!!!
	print_scale(user_data->saved_scales->scales[index]);
}

void clear_saved_scale( S_SAVED_SCALES * user_data){
	for( int i=0; i< user_data->scale_tot; i++){
			free(user_data->scales[i]);
	}
	free(user_data->scales);
	free(user_data);
}
/*************************************MODE SECTION****************************/


void realloc_saved_mode (S_SAVED_MODES * user_data){

}





void save_mode(S_MODES * user_data, S_USERINFO *user_info){//used to save a mode in the data structure
	//used to save a scale in the user data structure returns an error if the slots to save scales are all filled

	if (user_info->saved_modes->mode_num ==user_info->saved_modes->mode_tot){
//obsolete; to redo
		//user_info->saved_modes->modes=realloc_modes(user_info);
	}

	else if(user_info->saved_scales->scale_tot<user_info->saved_scales->scale_num){

		printf("error: the number of scales saved is higher than the memory allocated to save them. Please clear the save structure");
		return;

	}

	else{
	 copy_modes(user_info->saved_modes->modes[user_info->saved_modes->mode_num++], user_data);
	}

}

void clear_saved_mode(S_SAVED_MODES * user_data){
	for( int i=0; i< user_data->mode_tot; i++){
			free(user_data->modes[i]);
	}
	//free(user_data->modes);
	//free(user_data);
}

void init_saved_mode(S_SAVED_MODES* user_data, LENGTH  modes_tot){
    //similar to init saved scales but with modes structure; to redo entierly; modify mode struct !!!!!!!
	//initialises a saved scale struct
	//creates memory leaks

		free(user_data);
		user_data=malloc(sizeof(S_SAVED_MODES));
		user_data->modes=malloc(modes_tot*sizeof(S_MODES)); //might generate segfaults
		user_data->mode_tot= modes_tot;
		user_data->mode_num= 0;

		int i;
		for(i=0; i<modes_tot; i++){
			user_data->modes[i]=malloc(sizeof(S_MODES));


			init_modes(user_data->modes[i]);
		}


}

/**************************GENERAL SECTION**********************************/


void resets_saved_element(S_USERINFO * user_data, LENGTH struct_num, LENGTH element_of_struct){ //resets an element of a user saved struct; the index of the structure is passed as argument along with 0 or 1 to indicate wether it's the scale or the modes contained at this index that needs to be reset


    if (element_of_struct ==0){
           // init_scale(user_data[struct_num]->scale); //maybe use partial init idk

    }else if(element_of_struct==1){

      // init_modes(user_data[struct_num]->scale);
    }
}


void init_userinfo( S_USERINFO* user_data){
  //initialises and allocates memory to the different pointers in the user_data structure
  user_data->saved_modes=malloc(sizeof(S_SAVED_MODES));
  user_data->saved_scales=malloc(sizeof(S_SAVED_SCALES));

  init_saved_scale(user_data->saved_scales, 20);
  init_saved_mode(user_data->saved_modes, 20);
}

void clear_userinfo( S_USERINFO* user_data){
	clear_saved_scale(user_data->saved_scales);
	clear_saved_mode(user_data->saved_modes);
}
