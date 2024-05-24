#include "main.h"
#include<stdlib.h>
extern int tag_count, tag_flag;
Status validate_file(char *file)
{
    char *ptr = strchr(file , '.'); 
    if(ptr != NULL)
    {
	if(!strcmp(ptr,".mp3"))
	{
	    return e_success;
	}
    }
    return e_failure;
}


Status fileopen(char *argv[] , elements *e)
{
    e -> mp3_fptr = fopen(argv[2] ,"r");
    if( e -> mp3_fptr == NULL)
    {
	return e_failure;
    }
    return e_success;
}



Status check_fileid(elements *e)
{
    char buffer[3];
    fread(buffer , 1 ,3 , e -> mp3_fptr);
    return e_success;

}

Status check_version(elements *e)
{
    char buffer[2];
    fread(buffer , 1 ,2 , e -> mp3_fptr);
    return e_success;
}

Status print_tag(char *tag)
{
    if(!strcmp(tag,"TPE1"))
    {
	printf("ARTIST		:        ");
	tag_count+1;
	tag_flag=1;
    }
    else if(!strcmp(tag,"TIT2"))
    {
	printf("TITLE		:	 ");
	tag_count+1;
	tag_flag=1;
    }
    else if(!strcmp(tag, "TALB"))
    {
	printf("ALBUM		:	 ");
	tag_count+1;
	tag_flag=1;
    }
    else if(!strcmp(tag,"TYER"))
    {
	printf("YEAR		:	 ");
	tag_count+1;
	tag_flag=1;
    }
    else if(!strcmp(tag, "TCON" ))
    {
	printf("CONTENT		:	 ");
	tag_count+1;
	tag_flag=1;

	
    }
    else if(!strcmp(tag, "CCOM"))
    {
	printf("COMMENT 	:	 ");    
	tag_count++;
	tag_flag = 1;
    }
    else
    {
	tag_flag = 0;
    }
}


Status get_tag_size(elements *e)
{
    fseek(e -> mp3_fptr , 3 , SEEK_CUR);
    char size_buf[1];
    fread(size_buf, 1, 1, e -> mp3_fptr);
    int size = size_buf[0];
    fseek(e -> mp3_fptr , 3, SEEK_CUR);
    char *buffer2 = malloc(1 * size);
    fread(buffer2 , 1, size-1, e -> mp3_fptr);
    if(tag_flag == 1)
    {
    	printf("%s\n", buffer2);
	tag_flag = 0;
    }   

}


Status get_tag(elements *e)
{
    char buffer[4];
    fread(buffer , sizeof(char) , 4 , e -> mp3_fptr);
    print_tag(buffer);
    get_tag_size(e);
    return e_success;

}



Status mp3read(char *argv[] , elements *e)
{
    if(validate_file(argv[2]) == e_success)
    {
	printf("\n----------------------------------SELECTED VIEW DETAILS-------------------\n\n");
    }
    else
    {
	printf("ERROR : Please pass the valid Mp3 file \n");
	return e_failure;
    }
   if(!(fileopen(argv,e) == e_success))
   {
       printf("ERROR : Mp3 file openig was failure\n");
       return e_failure;
   }
   if(!(check_fileid(e) == e_success))
      return e_failure;
   if(!(check_version(e) == e_success))
    {
	printf("ERROR : Mp3 file  is not a ID3v2 version \n");
 	return e_failure;
    }
   printf("-----------------------------------------------------------------------\n----------------MP3 TAG REDAER AND EDITOR FOR ID3v2------------------------\n---------------------------------------------------------------------------\n");
   fseek(e -> mp3_fptr , 10 , SEEK_SET);
   while( tag_count<=5)
   {
       get_tag(e);      
   }
   printf("-------------------------------------------------------------------------------\n");
    return e_success;
}
