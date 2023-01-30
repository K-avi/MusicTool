#include "user_info.h"
#include "bitop.h"
#include "triadprint.h"
#include "dodecseries.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "triadgen.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


//need to use generics w that tbf


CPT scale_in_saved (S_SCALE scale, S_SAVED_SCALES * saved_scales){//returns the index+1 (to avoid problems if the first saved scale is scale) if a scale is present 
//in a saved scale struct 0 otherwise

	if(!saved_scales) return 0;

	S_SAVED_SCALES*tmp= saved_scales; 
	CPT cpt=1;

	while (tmp) {
	 	if(EQUALS_SCALE(scale, tmp->scale )) return cpt;
		tmp=tmp->next;
		cpt++;
	}
	return 0;
}

void add_scale(S_SAVED_SCALES * saved_scales, S_SCALE scale){

	if(!saved_scales) return;

	if( scale_in_saved(scale, saved_scales)) return;
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

void set_modes( S_SAVED_MODES * saved_modes, S_MODES modes){//duplicates modes in saved_modes->modes ; kinda dangerous tbh
	if(!(saved_modes && modes) ){ printf("\nplaceholder\n");return;}
	if(saved_modes->modes)free(saved_modes->modes);
	saved_modes->modes=generate_modes(modes[0]);
}

void add_mode(S_SAVED_MODES * saved_modes, S_MODES modes){ //duplicates modes in a saved_modes linked list; 
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
	if(index> user_data->modes_num){ printf("index superior to number of scales currently stored please enter a valid index; number of modes is : %d\n", user_data->modes_num); return;}
	CPT i=0; 
	S_SAVED_MODES *tmp = user_data->saved_modes;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of scales currently stored please enter a valid index; number of modes is : %d\n", user_data->modes_num); return; }
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
}// maybe tested

CPT modes_in_saved (S_MODES mode, S_SAVED_MODES * saved_modes){//returns the index+1 of the mode  if a mode is present 
//in a saved modes struct 0 otherwise

	if(! (mode && saved_modes)) return 0;
	
	CPT cpt=1;

	S_SAVED_MODES*tmp= saved_modes; 

	while (tmp) {
			
	 	if( equals_harmo(mode, tmp->modes)) return cpt;
		tmp=tmp->next;
		cpt++;
	}
	return 0;
}



////////////CHPROG //////////////


S_TRIAD_PROG * duplicate_chprog( S_TRIAD_PROG * chprog){ 
	//duplicates chprog into a new chord_prog;

	if(!chprog) return NULL; 
	if(!chprog->length) return NULL;

	S_TRIAD_PROG * ret= malloc(sizeof(S_TRIAD_PROG));

	ret->length=chprog->length; 
	ret->chord_prog=malloc(chprog->length* sizeof(TRIAD)); 
	memcpy(ret->chord_prog, chprog->chord_prog, chprog->length);

	return ret;
}//not tested 

void add_chprog( S_SAVED_TRIAD * saved_progs , S_TRIAD_PROG * chprog){
	//duplicates a new instance of chprog into a saved_progs linked list
	if(! (saved_progs && chprog)) return;

	S_SAVED_TRIAD * tmp= saved_progs; 

	while (tmp->next) {
		tmp= tmp->next;
	}
	S_SAVED_TRIAD* tmp1= malloc(sizeof(S_SAVED_TRIAD));
	tmp1->next=NULL; 
	tmp1->ch_prog=  duplicate_chprog(chprog); //allocates new chprog ; 

	tmp->next=tmp1;
}//not tested 

void print_saved_prog( S_USERINFO * user_data, INDEX index){
	if(index> user_data->progs_num){ printf("index superior to number of scales currently stored please enter a valid index; number of triad progs is : %d\n", user_data->progs_num); return;}
	CPT i=0; 
	S_SAVED_TRIAD *tmp = user_data->saved_progs;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of scales currently stored please enter a valid index; number of triad progs is : %d\n", user_data->progs_num); return; }
	print_triad_prog(tmp->ch_prog);
}//not tested


CPT chprog_in_saved (S_TRIAD_PROG* chprog, S_SAVED_TRIAD * saved_progs){//returns the index +1 of chprog if a chprog is present 
//in a saved progs struct 0 otherwise

	if(! (chprog && saved_progs)) return 0;

	S_SAVED_TRIAD*tmp= saved_progs; 
	CPT cpt=1; 

	while (tmp) {
	 	if( equals_chprog(chprog, tmp->ch_prog)) return cpt;
		cpt++;
		tmp=tmp->next;
	}
	return 0;
}


/////////////////DODECAPHONIC SERIES///////////////////////////


void add_serie( S_SAVED_DODEC * saved_series , S_DODEC serie){
	//adds a serie into into a saved_serie linked list
	if(! (saved_series && serie)) return;

	S_SAVED_DODEC * tmp= saved_series; 

	while (tmp->next) {
		tmp= tmp->next;
	}
	S_SAVED_DODEC* tmp1= malloc(sizeof(S_SAVED_TRIAD));
	tmp1->next=NULL; 
	tmp1->serie=  serie; //allocates new chprog ; 

	tmp->next=tmp1;
}//not tested 

void print_saved_serie( S_USERINFO * user_data, INDEX index){
	if(index> user_data->dodec_num){ printf("index superior to number of dodec series currently stored please enter a valid index; number of series is is : %d\n", user_data->dodec_num); return;}
	CPT i=0; 
	S_SAVED_DODEC *tmp = user_data->saved_dodecs;
	while(i<index && tmp){
		if(tmp->next)tmp=tmp->next;
		i++;
	}
	if(!tmp){printf("2ND CHECK index superior to number of series currently stored please enter a valid index; number of series is : %d\n", user_data->progs_num); return; }
	print_serie(tmp->serie);
}//not tested


CPT serie_in_saved (S_DODEC serie, S_SAVED_DODEC * saved_dodecs){//returns the index +1 of chprog if a chprog is present 
//in a saved progs struct 0 otherwise

	if(! (serie && saved_dodecs)) return 0;

	S_SAVED_DODEC*tmp= saved_dodecs; 
	CPT cpt=1; 

	while (tmp) {
	 	if( serie == saved_dodecs->serie) return cpt;
		cpt++;
		tmp=tmp->next;
	}
	return 0;
}
////////////////USER INFO ///////////////////

void save_scale( S_SCALE scale, S_USERINFO * user_info){
  //used to save a scale in the user data structure returns an error if the slots to save scales are all fille
  INDEX index= scale_in_saved(scale, user_info->saved_scales);
  if(index) { printf("scale already in struct at index %d ; no scale saved\n", index-1); return;}
  user_info->scales_num++;
  add_scale(user_info->saved_scales, scale);
  printf("scale saved at index %d\n", user_info->scales_num);
}
void save_modes(S_MODES modes, S_USERINFO *user_info){//used to save a mode in the data structure
	//used to save a scale in the user data structure returns an error if the slots to save scales are all 
	INDEX index= modes_in_saved(modes, user_info->saved_modes);
	
	if(index) { printf("modes already in struct at index %d ; no modes saved\n", index-1); return;}
	user_info->modes_num++;
	add_mode(user_info->saved_modes, modes);
	printf("modes saved at index %d\n", user_info->modes_num);
}

void save_chprog(S_TRIAD_PROG* chprog, S_USERINFO * user_info){//used to save a chprog in the data struct
	INDEX index= chprog_in_saved(chprog, user_info->saved_progs);
  	if(index) { printf("triad prog already in struct at index %d ; no triad prog saved\n", index-1); return;}
	user_info->progs_num++;
	add_chprog(user_info->saved_progs, chprog);
	printf("chprog saved at index %d\n", user_info->progs_num);
}

void save_dodec( S_DODEC serie, S_USERINFO * user_info){
  //used to save a scale in the user data structure returns an error if the slots to save scales are all fille
  INDEX index= serie_in_saved(serie, user_info->saved_dodecs);
  if(index) { printf("serie already in struct at index %d ; no serie saved\n", index-1); return;}
  user_info->dodec_num++;
  add_serie(user_info->saved_dodecs, serie);
  printf("dodec saved at index %d\n", user_info->dodec_num);
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

void remove_chprog(  S_USERINFO * user_info, CPT index ){ //removes chprog at index passed as argument if it exists
	
	if( index > user_info->progs_num){ printf("index passed is higher than the number of scales contained; can't clear this scale\n"); return;}
	S_SAVED_TRIAD* tmp= user_info->saved_progs, *tmp1;
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
			free_triad_prog(tmp1->ch_prog);
			free(tmp1);
		}else {
			tmp1=tmp->next;
			tmp->next=NULL;
			free_triad_prog(tmp1->ch_prog);
			free(tmp1);
		}
	}
	user_info->progs_num--;
}


void remove_dodec(  S_USERINFO * user_info, CPT index ){ //removes scale at index passed as argument if it exists
	
	
	if( index > user_info->dodec_num){ printf("index passed is higher than the number of series contained; can't remove dodec\n"); return;}
	S_SAVED_DODEC * tmp= user_info->saved_dodecs, *tmp1;
	CPT cpt=0;
	while(cpt< (index-1) && tmp){
		tmp=tmp->next;
		cpt++;
	}
	if(!tmp) { printf(" indexation problem; something went wrong\n"); return;}
	if(tmp->next){
		if(tmp->next->next){
			
			tmp1=tmp->next;
			//print_serie(tmp1->serie);
			tmp->next=tmp->next->next;
			free(tmp1);
		}else {
			
			tmp1=tmp->next;
			//print_serie(tmp1->serie);
			tmp->next=NULL;
			//print_serie(tmp->serie);
			free(tmp1);
			printf("serie removed succesfully\n");
		}
	}
	user_info->dodec_num--;
}

S_SCALE get_saved_scale( S_USERINFO * user_data, INDEX index){//retrieves the scale contained at "index"
//n ERROR_FLAG otherwise.

	if(user_data->scales_num<index) return ERROR_FLAG; 

	S_SAVED_SCALES *tmp = user_data->saved_scales; 
	u_char i=0;
	while (tmp && (i<index)) {
		tmp=tmp->next;
		i++;
	}
	if(!tmp) return ERROR_FLAG; 
	return tmp->scale;
}


S_MODES get_modes( S_USERINFO *user_data, INDEX index){//retrieves the mode contained at index n NULL otherwise

	if(!user_data) return NULL;
	if(!user_data->saved_modes) return NULL;
	if(user_data->modes_num<index) return NULL;


	S_SAVED_MODES*tmp = user_data->saved_modes; 
	u_char i=0;
	while (tmp && (i<index)) {
		tmp=tmp->next;
		i++;
	}
	if(!tmp) return NULL; 
	return tmp->modes;
}

S_TRIAD_PROG* get_chprog( S_USERINFO *user_data, INDEX index){//retrieves the chprog contained at index n NULL otherwise

	if(!user_data) return NULL;
	if(!user_data->saved_progs) return NULL;
	if(user_data->progs_num<index) return NULL;


	S_SAVED_TRIAD *tmp = user_data->saved_progs; 
	u_char i=0;
	while (tmp && (i<index)) {
		tmp=tmp->next;
		i++;
	}
	if(!tmp) return NULL; 
	return tmp->ch_prog;
}


S_DODEC get_saved_dodec( S_USERINFO * user_data, INDEX index){//retrieves the dodec serie contained at "index"
//n DODEC_ERRFLAG otherwise.

	if(user_data->dodec_num<index) return DODEC_ERRFLAG; 

	S_SAVED_DODEC *tmp = user_data->saved_dodecs; 
	u_char i=0;
	while (tmp && (i<index)) {
		tmp=tmp->next;
		i++;
	}
	if(!tmp) return DODEC_ERRFLAG; 
	return tmp->serie;
}

