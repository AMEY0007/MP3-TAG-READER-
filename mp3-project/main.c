#include<stdio.h>
#include "main.h"
int tag_count , tag_flag , option_flag;
char edit_option[5];
void error_usage()
{
    printf("\n------------------------------------------------------------\n\nERROR: ./a.out : INVALID ARGUMENTS\nUSAGE : \nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c new_text mp3filename\nTo get help pass like: ./a.out --help\n\n--------------------------------------------------------\n");
}
 void help_msg()
 {
     printf("\n----------------------HELP MENU-----------------------\n\n1. -v -> to view mp3 file contents\n2. -e -> to edit mp3 file contents\n\t\t2.1. -t -> to edit song title\n\t\t2.2. -a -> to edit artist name\n\t\t2.3. -A -> to edit album name\n\t\t2.4. -y -> to edit year\n\t\t2.5. -m -> to edit content\n\t\t2.6. -c -> to edit comment\n\n---------------------------------------------------------\n");
 }
int main(int argc , char *argv[])
{
    elements e;
    if(argc == 1)
    {
	error_usage();
    }
    else if(argc == 2)
    {
	if(!strcmp(argv[1], "--help"))
	{
	    help_msg();
	}
	else
	{
	    error_usage();
	}
    }
    else if(argc == 3)
    {
	if(!strcmp(argv[1],"-v"))
	{
	    if(!(mp3read(argv , &e) == e_success))
	    {
		error_usage();
	    }
	}
	else
	    error_usage();
    }
    else if(argc > 4)
    {
 	if( !(strcmp(argv[1],"-e")))
 	{
 	    if(!(mp3edit(argv , &e) == e_success))
 	    {
		printf("main");
 		error_usage();
 	    }
 	} 
    }
    else
	error_usage();	
   // return -1;
}
