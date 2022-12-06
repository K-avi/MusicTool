#include "user_info.h"
#include "bitop.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "chordgen.h"
#include "chordprog.h"
#include <stdlib.h>
#include <stdio.h>

void add_scale(S_SAVED_SCALES * saved_scales, S_SCALE scale){

	if(!saved_scales) return;
	S_SAVED_SCALES *tmp=saved_scales; 
	
	if(tmp->next){
		while (tmp->next){
			tmp=tmp->next;
		}
	}
	S_SAVED_SCALES *tmp1=malloc(sizeof(S_SAVED_SCALES));
	tmp1->next=NULL;
	tmp1->scale=scale; 
	tmp->next=tmp1;
}

void print_saved_scale( S_USERINFO * user_data, LENGTH index){
	if(index> user_data->scales_num){ printf("index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return;}
	CPT i=0; 
	S_SAVED_SCALES *tmp = user_data->saved_scales;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return; }
	print_scale(tmp->scale);
}
///////////////////////MODES/////////////////////////

void set_modes( S_SAVED_MODES * saved_modes, S_MODES modes){
	if(!(saved_modes && modes) ){ printf("\nplaceholder\n");return;}
	if(saved_modes->modes)free(saved_modes->modes);
	saved_modes->modes=generate_modes(modes[0]);
}

void add_mode(S_SAVED_MODES * saved_modes, S_MODES modes){
	if(!(saved_modes && modes) ) { printf("placeholder");return;}
	S_SAVED_MODES *tmp=saved_modes; 
	while (tmp->next){
		tmp=tmp->next;
	}
	S_SAVED_MODES *tmp1=malloc(sizeof(S_SAVED_SCALES));
	tmp1->next=NULL;
	S_MODES tmp1_modes=generate_modes(modes[0]);
	tmp1->modes=tmp1_modes; 
	tmp->next=tmp1;
}


void print_saved_modes( S_USERINFO * user_data, LENGTH index){
	if(index> user_data->modes_num){ printf("index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return;}
	CPT i=0; 
	S_SAVED_MODES *tmp = user_data->saved_modes;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return; }
	print_modes(tmp->modes);
}

S_SCALE get_scale_of_modes( S_USERINFO * user_data, CPT modes_num, CPT scale_num){
	//retrieves the scale situated at scale num (nth scale) of the modes saved at modes num (nth mode)
	if(!user_data){ printf("eror: user_data is null\n"); return ERROR_FLAG;}
	
	else if(modes_num>user_data->modes_num) {
		printf("error: index of modes to retrieve scale from is higher than number of modes saved; please enter a valid index.\n");
		return ERROR_FLAG;
	}
	CPT cpt=0;
	S_SAVED_MODES *tmp=user_data->saved_modes;
	while(cpt<modes_num && tmp){
		cpt++;
		tmp=tmp->next;
	}
	if(!tmp){ 
		printf("placeholder error 2 in get_scale_of_modes\n"); 
		return ERROR_FLAG;
	}
	if(scale_num>get_length(tmp->modes[0])){
		printf("error: placeholder placeholder\n");
		return ERROR_FLAG;
	}else return tmp->modes[scale_num];
}// NOT TESTED !!!!!!!!!!!!!!!!!

////////////////USER INFO ///////////////////

void save_scale( S_SCALE scale, S_USERINFO * user_info){
  //used to save a scale in the user data structure returns an error if the slots to save scales are all fille
  user_info->scales_num++;
  add_scale(user_info->saved_scales, scale);
}

void save_modes(S_MODES modes, S_USERINFO *user_info){//used to save a mode in the data structure
	//used to save a scale in the user data structure returns an error if the slots to save scales are all 
	user_info->modes_num++;
	add_mode(user_info->saved_modes, modes);
}

void remove_scale(  S_USERINFO * user_info, CPT index ){ //removes scale at index passed as argument if it exists
	
	
	if( index > user_info->scales_num){ printf("index passed is higher than the number of scales contained; can't clear this scale\n"); return;}
	S_SAVED_SCALES * tmp= user_info->saved_scales, *tmp1;
	CPT cpt=0;
	while(cpt< (index-1) && tmp){
		tmp=tmp->next;
		cpt++;
	}
	if(!tmp) { printf(" indexation problem; something went wrong\n"); return;}
	if(tmp->next){
		if(tmp->next->next){
			
			tmp1=tmp->next;
			print_scale(tmp1->scale);
			tmp->next=tmp->next->next;
			free(tmp1);
		}else {
			
			tmp1=tmp->next;
			print_scale(tmp1->scale);
			tmp->next=NULL;
			print_scale(tmp->scale);
			free(tmp1);
		}
	}
	user_info->scales_num--;
}

void remove_modes(  S_USERINFO * user_info, CPT index ){ //removes modes at index passed as argument if it exists
	
	if( index > user_info->modes_num){ printf("index passed is higher than the number of scales contained; can't clear this scale\n"); return;}
	S_SAVED_MODES* tmp= user_info->saved_modes, *tmp1;
	CPT cpt=0;
	while(cpt< (index-1) && tmp){
		tmp=tmp->next;
		cpt++;
	}
	if(!tmp) { printf(" indexation problem; something went wrong\n"); return;}
	if(tmp->next){
		if(tmp->next->next){
			tmp1=tmp->next;
			tmp->next=tmp->next->next;
			free(tmp1->modes);
			free(tmp1);
		}else {
			tmp1=tmp->next;
			tmp->next=NULL;
			free(tmp1->modes);
			free(tmp1);
		}
	}
	user_info->modes_num--;
}



////////////////////// CHPROG ///////////////////

void add_chprog(S_SAVED_PROGS* saved_chprog, S_CHORD_PROG *chprog){
	
	if(!saved_chprog) return;
	S_SAVED_PROGS *tmp=saved_chprog; 
	
	if(tmp->next){
		while (tmp->next){
			tmp=tmp->next;
		}
	}
	S_SAVED_PROGS *tmp1=malloc(sizeof(S_SAVED_PROGS));
	tmp1->next=NULL;
	tmp1->ch_prog=chprogdup(chprog);

	tmp->next=tmp1;

}//not tested


void free_saved_progs( S_SAVED_PROGS * saved_chprog){//frees all the saved chord progression 

	if(!saved_chprog) return;
	S_SAVED_PROGS* tmp= NULL;
	while(saved_chprog){
		tmp=saved_chprog;
		free_chord_prog(saved_chprog->ch_prog);
		saved_chprog=saved_chprog->next;
		free(tmp);
	}
}//not tested 


void print_saved_chprog( S_USERINFO * user_data, LENGTH index){//not done
	if(index> user_data->scales_num){ printf("index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return;}
	CPT i=0; 
	S_SAVED_SCALES *tmp = user_data->saved_scales;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of scales currently stored please enter a valid index; number of scale is : %d\n", user_data->scales_num); return; }
	print_scale(tmp->scale);
}
