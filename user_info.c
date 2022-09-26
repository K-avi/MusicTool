#include "user_info.h"
#include "types.h"
#include "init.h"
#include <stdlib.h>



void save_scale( S_SCALE * scale, S_SAVED* user_data){  //saves a scale



}


void clear_saved_data(S_SAVED* user_data){ //  frees the saved data

    free(user_data);

}

void resets_saved_element(S_SAVED * user_data, LENGTH struct_num, LENGTH element_of_struct){ //resets an element of a user saved struct; the index of the structure is passed as argument along with 0 or 1 to indicate wether it's the scale or the modes contained at this index that needs to be reset


    if (element_of_struct ==0){
           // init_scale(user_data[struct_num]->scale); //maybe use partial init idk

    }else if(element_of_struct==1){

      // init_modes(user_data[struct_num]->scale);
    }
}


