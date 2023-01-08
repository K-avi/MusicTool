trash to keep track of unused stuff.


/*CPT get_index_of_nth( S_SCALE scale, CPT n){
    //returns the "index" of the nth bit set in a scale 
    LENGTH length= get_length_kerni(scale);
    
    CPT bits_found=0;
    short last_bit_index=-1;
    CPT decalage=0;

    while(bits_found<n){
        if( GET_NTH(scale, decalage)) { bits_found++; last_bit_index=decalage;}
        decalage++;
    }
    return last_bit_index;
}

S_SCALE generate_nth_mode(S_SCALE scale, CPT n){//returns the nth mode of a scale. 
    if(n==0 || n==1) return scale;
    else if( n> get_length_kerni(scale)) {fprintf(stdout, "n is superior to the length of the scale");return scale;} 
    return rot(scale, get_index_of_nth(scale, n)-1);
}



S_SCALE rotate_right_scale(S_SCALE scale, CPT n) //harmonises a scale on the nth mode if n is 1;
//does so by right rotating the first 11 bits of the scale by n;
{
    //if(n>get_length_kerni(scale)){ printf("\n n too long\n"); return scale;}
   // if( !(1 <<n & scale)) {printf("\n triedc to harmo on a mode that doesnt start as a note\n");return scale;} 
    
    S_SCALE mask = 0x7FF; // Mask for lower 11 bits;
    S_SCALE flags= scale & (~mask); //preserve the flags 
    
    S_SCALE ret= ROTATE_RIGHT(scale, n, 16);

    ret|= (ret & (~mask) )>>6; //likely the issue
    ret&= mask;
    
    return ret|flags ;
}
S_SCALE rotate_right_scale_yohan( S_SCALE scale, CPT n){
      return (scale>>n)  | ((scale & ((1<<n))-1)) << (10-n)  | (scale & 0xF800);
}

S_SCALE rot1(S_SCALE scale, CPT n){
    S_SCALE head = scale & 63488;
    S_SCALE body = scale & 2047; 

    S_SCALE tail = scale & (( 1 << n) -1);
    S_SCALE zer= 2048; 

    printf("scale shift is %d\n tail is\n",n);
    print_bits(tail);
    printf("body is\n");
    print_bits(body);
    printf("\n:");

    return head | ((tail << 10 | zer |body )>>n);
}
*/



 /*
  S_SAVED_SCALES *scales=malloc(sizeof(S_SAVED_SCALES));
  init_saved_scale(scales);
  SET_SAVED_SCALE(scales, 1370);
  add_scale(scales, 1371);
  print_scale(scales->scale);
  free_saved_scale(scales);

  S_SAVED_MODES * modes=malloc(sizeof(S_SAVED_MODES));
  init_saved_mode(modes);
  S_MODES eccle_modes= generate_modes(1370);
  set_modes(modes, eccle_modes);
  print_modes(modes->modes);
  free_saved_mode(modes);


  S_USERINFO * user_info=malloc(sizeof(S_USERINFO));
  init_userinfo(user_info);
  save_scale(1370, user_info);

  set_modes(user_info->saved_modes, eccle_modes);
  save_modes(eccle_modes, user_info);
 

  print_scale(user_info->saved_scales->next->scale);
  print_modes(user_info->saved_modes->next->modes);

  
  if(eccle_modes)free(eccle_modes);
  free_userinfo(user_info);*/


  //save_scale(1370, user_saved);
  //save_scale(1371, user_saved);

 // S_MODES eccle_modes= generate_modes(1370);
 // S_MODES not_eccle= generate_modes(1371);
 // S_MODES not_not_eccle= generate_modes(1372);

 /* save_modes(eccle_modes,user_saved);
  save_modes(not_eccle, user_saved);
  save_modes(not_not_eccle, user_saved);*/

  ScaleLoop();

  free_userinfo(user_saved);

  //free(eccle_modes);
  //free(not_eccle);
 // free(not_not_eccle);


/* prolly very useless lmao
LENGTH *select_random_degrees(S_SCALE scale, LENGTH scale_length, CPT num){
  
  if(num>scale_length) return NULL;
  
  LENGTH* ret= malloc(num*sizeof(LENGTH));
  CPT j=0;
  int ran=-1; 
  while( j <num){
    ran=rand()%13;
    if(ran==0) ret[j++]=1; 
    else if( (1<<ran) & scale) ret[j++]=ran;
  }
  return ret;
}*/



/*SYNTAX_ERROR parenthesis_check( FILE * f){//checks that each parenthesis opened is closed n
//that one parenthesis is opened at a time in a FILE
    if(!f) return SYNTAX_GENERIC_ERROR;
    printf("reached\n");
    u_char openpar=1; 
    u_char closedpar=0;
    char line[256];
    char *tmp;

    int cpt=0;
    while( fgets(line, 256,f)){
      //  printf("%s\n", line);
        tmp=line;
       // printf("%s\n", tmp);
       // printf("%lu\n", strlen(tmp));
       printf("%d : %s\n",  ++cpt, tmp);
       for(int i=0; i<strlen(tmp); i++){
           printf("\t %d\n", *tmp);
       }
      
        while(!END_OF_LINE_CHAR(*tmp) || *tmp!='\n'){

            printf("%c", *tmp); 
            tmp++;
            /*printf("1\n");
            while(*tmp!='(' || *tmp!=')' || !END_OF_LINE_CHAR(*tmp) || *tmp!='\n'){
                printf("%c",*tmp);
                tmp++;
            }
            printf("2\n");
            if(END_OF_LINE_CHAR(*tmp) || *tmp!='\n') break;

            else{
                if(*tmp=='(') {
                    if(!openpar) return SYNTAX_UNMATCHED_OPENED_PAR;
                    openpar=0; 
                    closedpar=1;
                }else if(*tmp ==')'){
                     printf("in" );
                    if(!closedpar) return SYNTAX_UNMATCHED_CLOSED_PAR; 
                    openpar=1; 
                    closedpar=0;
                }

                
            }
        //}
        
    }

    //if( (!openpar) || closedpar) return SYNTAX_GENERIC_ERROR;
    return SYNTAX_OK;
}*/
/*bool envcheck( char * str , bool *begin, bool*end ){ //not yet 

    char * tmp= str; 

    while(*tmp==' ' || *tmp=='\t') tmp++; 

    if(END_OF_LINE_CHAR(*tmp) || *tmp=='\n') return SYNTAX_OK; //\n isnt neutral cuz reading from file

    else if(!strncmp(tmp, "env",3)){
        tmp+=3;

        while(*tmp==' ' || *tmp=='\t') {
            tmp++;
        }
        if(strncmp(tmp, "scale", 5)){
            if(!)
            tmp+=5;
            while(*tmp=='\t' || *tmp==' ') tmp++;
            if( ! (END_OF_LINE_CHAR(*tmp) || *tmp==' ' )) return SYNTAX_INVALID_CHAR;

        }else if(strncmp(tmp, "harmo", 5)){

        }else if(strncmp(tmp, "chprog", 6)){

        }else return SYNTAX_GENERIC_ERROR;
    }
    return SYNTAX_INVALID_ARG;
}*/