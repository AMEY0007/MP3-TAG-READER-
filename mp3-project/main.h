#include<stdio.h>
#include<string.h>
/*
int tag_count;
int tag_flag;
int option_flag;
char edit_option[5];
*/
typedef enum status
{
    e_failure,
    e_success
} Status;
typedef struct elements
{
    FILE *mp3_fptr;
    char *new_text;  
   int new_text_size;

}elements;
//to display the error and usage message
void error_usage();
//to display the help message
void help_msg();
//read the info about mp3 file
Status mp3read(char *argv[] , elements *e);
//to check the file status
Status fileopen(char *argv[] , elements *e);
Status check_filed_id(elements *e);
Status check_version(elements *e);
//edit the info aboyt mp3 file
Status mp3edit(char *argv[] , elements *e);
