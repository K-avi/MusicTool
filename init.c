#include "chordgen.h"
#include "chordprint.h"
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

void init_scl_func(SCL_FUNC* func){
	func->compare=NULL; 

	func->rand=&generate_ran_scale;
	func->parse=&parse_scale;
	func->print=&print_scale;

	func->get=&get_saved_scale;
	func->inverse=&get_inverse_scale;
	func->complementary=&get_complementary_scale;
	func->nearby=&generate_nearby_scale;
	func->prime=&get_prime_scale;
	func->scl_to_intvect=&generate_intv_vect;
	func->scl_to_intstruct=&get_interval_struct;

	func->save=&save_scale;
	func->print_env=&print_scl_env;
	func->print_saved=&print_saved_scale;
	func->remove=&remove_scale;
	
}

void init_harmo_func( HARMO_FUNC* func){

	func->compare=&equals_harmo;

	func->rand=NULL;
	func->parse=NULL;
	func->print=&print_modes;

	func->get=&get_modes;
	func->fromscale=&generate_modes;

	func->save=&save_modes;
	func->print_env=&print_modes_env;
	func->print_saved=&print_saved_modes;
	func->remove=&remove_modes;
}

void init_chprog_func( CHPROG_FUNC* func){
	
	func->compare=&equals_chprog;

	func->rand=&generate_chord_prog;
	func->parse=&str_to_chord_prog;
	func->print=&print_chord_prog;

	func->get=&get_chprog;
	func->toscale=&chprog_to_scl;

	func->save=&save_chprog;
	func->print_env=&print_chprog_env;
	func->print_saved=&print_saved_prog;
	func->remove=&remove_chprog;
}

void init_dodec_func( DODEC_FUNC* func){

	func->compare=NULL;

	func->rand=&generate_serie;
	func->shuflle=&shuffle_serie;
	func->parse=&parse_serie;
	func->print=&print_serie;

	func->get=&get_saved_dodec;
	func->gen_matrix=&serie_to_12tmat;
	func->retrograde=&retrograde_serie;
	func->inverse=&inverse_serie;
	func->ret_inv=&retrograde_inverse_serie;

	func->nth_prime=&nth_prime;
	func->nth_inv=&nth_inv;
	func->nth_ret=&nth_retrograde;
	func->nth_ret_in=&nth_retrograde_inverse;

	func->save=&save_dodec;
	func->print_env=&print_dodec_env;
	func->print_saved=&print_saved_serie;
	func->remove=&remove_dodec;
}

void init_allfunc( ALL_FUNC* funcs){

	funcs->scl_funcs=malloc(sizeof(SCL_FUNC));
	funcs->harmo_funcs=malloc(sizeof(HARMO_FUNC));
	funcs->chprog_funcs=malloc(sizeof(CHPROG_FUNC));
	funcs->dodec_funcs=malloc(sizeof(DODEC_FUNC));
	
	init_scl_func(funcs->scl_funcs);
	init_harmo_func(funcs->harmo_funcs); 
	init_chprog_func(funcs->chprog_funcs); 
	init_dodec_func(funcs->dodec_funcs);
}

void free_allfunc( ALL_FUNC*funcs){

	free(funcs->scl_funcs);
	free(funcs->harmo_funcs);
	free(funcs->chprog_funcs);
	free(funcs->dodec_funcs);
	free(funcs);
}


void init_userinfo( S_USERINFO* user_data){
  //initialises and allocates memory to the different pointers in the user_data structure
 //only call at the start of MusicTool otherwise can cause memleak

  user_data->saved_modes=malloc(sizeof(S_SAVED_MODES));// printf("saved modes pointer: %p\n", user_data->saved_modes);
  user_data->saved_scales=malloc(sizeof(S_SAVED_SCALES)); //printf("saved scale pointer: %p\n", user_data->saved_scales);
  user_data->saved_progs= malloc(sizeof(S_SAVED_PROGS));
  user_data->saved_dodecs=malloc(sizeof(S_SAVED_DODEC));

  user_data->modes_num=0;
  user_data->scales_num=0;
  user_data->progs_num=0;
  user_data->dodec_num=0;

  init_saved_scale(user_data->saved_scales);
  init_saved_mode(user_data->saved_modes);
  init_saved_progs(user_data->saved_progs);
  init_saved_dodec(user_data->saved_dodecs);
}

void free_userinfo( S_USERINFO* user_info){
     free_saved_scale(user_info->saved_scales);
	 free_saved_modes(user_info->saved_modes);
	 free_saved_progs(user_info->saved_progs);
	 free_saved_dodecs(user_info->saved_dodecs);
	
	free(user_info);
}