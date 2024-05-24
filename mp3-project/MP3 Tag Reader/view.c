/* Name: Atharva kothawade */

#include<stdio.h>
#include<string.h>
#include"types.h"
#include"view.h"
Status read_and_validate_encode_args(char *argv[],ViewInfo *V_info)
{
    if (strstr(argv[2],".mp3") != NULL)
    {
	printf("SUCCESS: File is MP3\n");
	V_info->source_mp3_filenme = argv[2];
	return v_success;
    }
    else
    {	
	printf("ERROR: File is not MP3(sample.mp3)\n");
	return v_failure;
    }
}

Status open_view_file(ViewInfo *V_info)
{
    V_info->fptr_source_mp3 = fopen(V_info->source_mp3_filenme,"r");

    if (V_info->fptr_source_mp3 == NULL)
    {
	perror("fopen");
	fprintf(stderr,"file %s open is failed\n",V_info->source_mp3_filenme);
	return v_failure;
    }
    return v_success;
}

Status check_view_ID3(ViewInfo *V_info)
{
    char buffer[4];
    fread(buffer,1,3,V_info->fptr_source_mp3);
    if (strcmp(buffer,"ID3") == 0)
    {
	printf("--> Signature is %s\n",buffer);
	return v_success;
    }
    else
	return v_failure;
}

Status check_view_version(ViewInfo *V_info)
{
    int version;
    fread(&version,1,2,V_info->fptr_source_mp3);
    printf("--> Version is %d\n",version);
    if(version == 3)
	return v_success;
    else
	return v_failure;
}

Status check_view(ViewInfo *V_info)
{
    fseek(V_info->fptr_source_mp3,10,SEEK_SET);
    char TIT2[5];
    fread(TIT2,4,1,V_info->fptr_source_mp3);
    TIT2[4] ='\0';

    if(strcmp(TIT2,"TIT2") == 0)
    {
	printf("SUCCESS: Tag read TIT2\n");
	printf("--> Tag = %s\n",TIT2);
    }
    else
    {
	printf("FAILURE: Tag read TIT2\n");
	return v_failure;
    }

    int tag_size;
    fread(&tag_size,4,1,V_info->fptr_source_mp3);
    //Size of tag in hexadesimal form 
    //printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

    tag_size = reverse_view_msb_to_lsb(tag_size);

    printf("--> Tag %s size is %d\n",TIT2,tag_size);

    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
    fread(V_info->tag_TIT2,tag_size-1,1,V_info->fptr_source_mp3);
    printf("--> TITLE : %s\n",V_info->tag_TIT2);

    char TPE1[5];
    fread(TPE1,4,1,V_info->fptr_source_mp3);
    TPE1[4]='\0';

    while(1)
    {
	if(strcmp(TPE1,"TPE1") == 0)
	{
	    printf("SUCCESS: Tag read TPE1\n");
	    printf("--> Tag is %s\n",TPE1);
	    fread(&tag_size,4,1,V_info->fptr_source_mp3);
	    //printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

	    tag_size = reverse_view_msb_to_lsb(tag_size);

	    printf("--> Tag %s size is %d\n",TPE1,tag_size);

	    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
	    fread(V_info->tag_TPE1,tag_size-1,1,V_info->fptr_source_mp3);
	    printf("--> ARTIST : %s\n",V_info->tag_TPE1);
	    break;
	}
	else
	{
	    fread(TPE1,4,1,V_info->fptr_source_mp3);
	    TPE1[4]='\0';
	}
    }

    char TALB[5];
    fread(TALB,4,1,V_info->fptr_source_mp3);
    TALB[4]='\0';

    while(1)
    {
	if(strcmp(TALB,"TALB") == 0)
	{
	    printf("SUCCESS: Tag read TALB\n");
	    printf("--> Tag is %s\n",TALB);
	    fread(&tag_size,4,1,V_info->fptr_source_mp3);
	    //printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

	    tag_size = reverse_view_msb_to_lsb(tag_size);

	    printf("--> Tag %s size is %d\n",TALB,tag_size);

	    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
	    fread(V_info->tag_TALB,tag_size-1,1,V_info->fptr_source_mp3);
	    printf("--> ALBUM : %s\n",V_info->tag_TALB);
	    break;
	}
	else
	{
	    fread(TALB,4,1,V_info->fptr_source_mp3);
	    TALB[4]='\0';
	}
    }

    char TYER[5];
    fread(TYER,4,1,V_info->fptr_source_mp3);
    TYER[4]='\0';

    while(1)
    {
	if(strcmp(TYER,"TYER") == 0)
	{
	    printf("SUCCESS: Tag read TYER\n");
	    printf("--> Tag is %s\n",TYER);
	    fread(&tag_size,4,1,V_info->fptr_source_mp3);
	    printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

	    tag_size = reverse_view_msb_to_lsb(tag_size);

	    printf("--> Tag %s size is %d\n",TYER,tag_size);

	    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
	    fread(V_info->tag_TYER,tag_size-1,1,V_info->fptr_source_mp3);
	    printf("--> YEAR : %s\n",V_info->tag_TYER);
	    break;
	}
	else
	{
	    fread(TYER,4,1,V_info->fptr_source_mp3);
	    TYER[4]='\0';
	}
    }

    char TCON[5];
    fread(TCON,4,1,V_info->fptr_source_mp3);
    TCON[4]='\0';

    while(1)
    {
	if(strcmp(TCON,"TCON") == 0)
	{
	    printf("SUCCESS: Tag read TCON\n");
	    printf("--> Tag is %s\n",TCON);
	    fread(&tag_size,4,1,V_info->fptr_source_mp3);
	    //printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

	    tag_size = reverse_view_msb_to_lsb(tag_size);

	    printf("--> Tag %s size is %d\n",TCON,tag_size);

	    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
	    fread(V_info->tag_TCON,tag_size-1,1,V_info->fptr_source_mp3);
	    printf("--> ARTIST : %s\n",V_info->tag_TCON);
	    break;
	}
	else
	{
	    fread(TCON,4,1,V_info->fptr_source_mp3);
	    TCON[4]='\0';
	}
    }

    char COMM[5];
    fread(COMM,4,1,V_info->fptr_source_mp3);
    COMM[4]='\0';

    while (1)
    {
	if (strcmp(COMM,"COMM") == 0)
	{
	    printf("SUCCESS: Tag read COMM\n");
	    printf("--> Tag is %s\n",COMM);
	    fread(&tag_size,4,1,V_info->fptr_source_mp3);
	    //printf("--> Tag size (Hexa decimal) is %X\n",tag_size);

	    tag_size = reverse_view_msb_to_lsb(tag_size);

	    printf("--> Tag %s size is %d\n",COMM,tag_size);

	    fseek(V_info->fptr_source_mp3,3,SEEK_CUR);
	    fread(V_info->tag_COMM,tag_size-1,1,V_info->fptr_source_mp3);
	    printf("--> COMPOSER : %s\n",V_info->tag_COMM);
	    break;
	}
	else
	{
	    fread(COMM,4,1,V_info->fptr_source_mp3);
	    COMM[4]='\0';
	}
    }
    return v_success;
}

int reverse_view_msb_to_lsb(int num)
{
    char *ptr =(char *)&num;
    char temp;
    int size=4;

    for(int i=0;i<2;i++)
    {
	temp=*(char *)(ptr+i);
	*(char *)(ptr+i)=*(char *)(ptr+size-i-1);
	*(char *)(ptr+size-i-1)=temp;
    }
    return num;
}

Status do_view(ViewInfo *V_info)
{
    if (open_view_file(V_info) == v_success)
    {
	printf("SUCCESS: Open view file\n");
	if (check_view_ID3(V_info) == v_success)
	{
	    printf("SUCCESS: Check view ID3\n");
	    if (check_view_version(V_info) == v_success)
	    {
		printf("SUCCESS: Check view version\n");
		if (check_view(V_info) == v_success)
		{
		    printf("SUCCESS: Check view (Tags)\n");
		}
		else 
		{
		    printf("FAILURE: Check view (Tags)\n");
		    return v_failure;
		}
	    }
	    else 
	    {
		printf("FAILURE: Check view version\n");
		return v_success;
	    }
	}
	else 
	{
	    printf("FAILURE: Check view ID3\n");
	    return v_failure;
	}
    }
    else 
    {
	printf("FAILURE: Open view file\n");
	return v_failure;
    }
    return v_success;
}
