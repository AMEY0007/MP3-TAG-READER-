#include "main.h"
#include<stdlib.h>
extern int tag_flag, option_flag;
extern char edit_option[5];
char *tag_name;
Status file_validate( char *argv[],elements *e)
{
    e -> mp3_fptr = fopen(argv[4] , "r+");
    if(e -> mp3_fptr == NULL)
    {
	printf("MP3 file opening status was failure\n");
	return e_failure;
    }
    return e_success;
}
int get_size(elements *e)
{
    fseek( e -> mp3_fptr , 3, SEEK_CUR);
    char size_buf[1];
    fread(size_buf , 1, 1, e -> mp3_fptr);
    int size = size_buf[0];
    return size;    

}
Status search_tag(char *edit_option , elements *e)
{
    fseek(e -> mp3_fptr , 10 , SEEK_SET);
    while(tag_flag == 0)
    {
	char buffer[4];
	fread(buffer , 1, 4, e -> mp3_fptr);
	int size = get_size(e);
	fseek(e -> mp3_fptr , 3, SEEK_CUR);
	if(!strcmp(buffer , edit_option))
	{
	    fwrite(e -> new_text ,  1, size - 1 , e -> mp3_fptr);
	    tag_flag = 1 ;
	    printf("-------------------------------------------------------------------\n                    EDITED INFORMATION\n--------------------------------------------------------------------\n %s            :    %s \n------------------------------------------------------------------\n\n--------------INFORMATION CHANGED SUCCESSFULLY----------------------\n\n", tag_name , e -> new_text);
	    return e_success;
	}
	fseek( e -> mp3_fptr , size-1 , SEEK_CUR);
    }

    return e_failure;
}
Status mp3edit(char *argv[],elements *e)
{
    printf("\n---------------YOU HAVE SELECTED EDIT OPTION--------------------\n\n");
    if( !strcmp(argv[2],"-t"))
    {
	tag_name = malloc(sizeof(char)*5);
	strcpy(tag_name , "TITLE");
	strcpy(edit_option,"TIT2");
	option_flag = 1;
    }
    else if(!strcmp(argv[2] ,"-a"))
   {
	tag_name = malloc(sizeof(char)*6);
	strcpy(tag_name , "ARTIST");
	strcpy(edit_option , "TPE1");
	option_flag = 1;
    }
    else if(! strcmp(argv[2] , "-A"))
    {
	tag_name = malloc(sizeof(char)*5);
	strcpy(tag_name , "ALBUM");
       strcpy(edit_option,"TALB");
	option_flag = 1;
    }
    else if( ! strcmp(argv[2],"-y"))
    {
	tag_name = malloc(sizeof(char)*4);
	strcpy(tag_name , "YEAR");
	strcpy(edit_option,"TYER");
	option_flag = 1;
	
    }
    else if(! strcmp(argv[2] ,"-m"))
    {
	tag_name = malloc(sizeof(char)*7);
	strcpy(tag_name , "CONTENT");
       strcpy(edit_option, "TCON");
	option_flag = 1;
    }
    else if(! strcmp(argv[2],"-c"))
    {
	tag_name = malloc(sizeof(char)*7);
	strcpy(tag_name , "COMMENT");
	strcpy(edit_option,"TCOM");
	option_flag = 1;
    }
    else
    {
	error_usage();
	return e_failure;
    }
    if( option_flag == 1)
    {
	e -> new_text_size = strlen(argv[3]);
	e -> new_text = malloc(sizeof(char) * e -> new_text_size);
	strcpy(e -> new_text , argv[3]);
	if(!(file_validate(argv ,e) == e_success))
	    return e_failure;
	search_tag(edit_option , e);
    }
    else
	return e_failure;
    return e_success;
}
