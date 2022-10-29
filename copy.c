#include "init.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>


void copy_note_arr( NOTE * note_arr_source, NOTE * note_arr_dest, LENGTH length){ //copies the note array dest in the note array source

  for( LENGTH i=0; i<length; i++){

    note_arr_source[i]=note_arr_dest[i];
  }
}


void copy_scale (S_SCALE * scale_dest, S_SCALE * scale_source){ //copies the content of scale 2 in scale1

  
  init_scale(scale_dest);
  scale_dest->length= scale_source->length;

  copy_note_arr(scale_dest->scale, scale_source->scale, scale_source->length);
  
}

void copy_modes( S_MODES * modes_dest , S_MODES * modes_source){
  //copies the modes stored in modes_source to modes dest; could prolly be done with memcopy
  

  modes_dest->length= modes_source->length;
  int i;
  for(i=0; i<modes_source->length; i++){
    copy_note_arr( modes_dest->scale[i], modes_source->scale[i],modes_source->length);
  }

}
