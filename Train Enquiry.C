#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct Train
{
    char train_name[200];
    char train_no[20];
    char interval[20];
    char speed[20];
    char size[20];
    char time[20];
};

struct Train te;

void add_record()
{
    FILE *t;
	t= fopen("detail.bin","ab+");
    if(t == NULL)
	{
	printf("File Does not Exits\n");
    }
    else
    {
	printf("ADD RECORD\n");
	fflush(stdin);
	printf("\nENTER FULL NAME OF TRAIN: ");
	gets(te.train_name);
	printf("\nNow Enter Train Details: \n\n");
	printf("\nENTER THE TRAIN NUMBER: ");
	gets(te.train_no);
	printf("\nENTER THE TOTAL JOURNEY TIME(IN MINUTES) : ");
	gets(te.time);
	printf("\nENTER THE TIME INTERVAL BETWEEN THE STATIONS(IN MINUTES): ");
	gets(te.interval);
	printf("\nENTER SIZE OF TRAIN: ");
	gets(te.size);
	printf("\nENTER THE SPEED OF TRAIN(SLOW/FAST): ");
	gets(te.speed);
	fwrite(&te, sizeof(te), 1, t);
	printf("THE RECORD IS CREATED.......\n");
    }
    fclose(t);
    return;
}


void search_record()
{
     FILE *t;
    char ts_name[20];
    int isFound = 0;
    printf("SEARCHING A SPECIFIC TRAIN:\n");

    printf("ENTER TRAIN NAME : \n");
    fflush(stdin);
    gets(ts_name);

    t = fopen("detail.bin","rb");
    while(fread(&te,sizeof(te),1,t) == 1)
	{
	if(strcmp(ts_name,te.train_name) == 0)
		{
	    isFound = 1;
	    break;
	}
    }
    if(isFound == 1)
    {
	 printf("The record is Found............\n");
	 printf("\nTRAIN NAME: %s",te.train_name);
	 printf("\n TRAIN NUMBER:%s",te.train_no);
	 printf("\nTOTAL TIME(IN MINUTES): %s",te.time);
	 printf("\nTIME INTERVAL(IN MINUTES): %s",te.interval);
	 printf("\nSize: %s",te.size);
	 printf("\nSPEED: %s",te.speed);
    }
    else
	{
	printf("Sorry, No record found in the database!!!!!!!!!\n");
    }
    fclose(t);
    return;
}

void modify_record()
{
       FILE *t;
     char ts_name[20];
    int isFound = 0;
    printf("MODIFICATION OF RECORD..\n");

    printf("\nEnter TRAIN NUMBER to Modify its DETAILS: ");
    fflush(stdin);
    gets(ts_name);

    t = fopen("detail.bin","rb+");
    while(fread(&te, sizeof(te),1,t) == 1)
	{
	if(strcmp(ts_name, te.train_no) == 0)
	{
		fflush(stdin);
	    printf("\nEnter TIME INTERVAL Required: ");
	    gets(te.interval);
	    printf("\nTrain Number: ");
	    gets(te.train_no);
	    printf("\nSpeed: ");
	    gets(te.speed);
	    printf("\nTotal Time: ");
	    gets(te.time);
	    printf("\nSize: ");
	    gets(te.size);
	    fseek(t,sizeof(te), SEEK_CUR);
	    fwrite(&te,sizeof(te), 1, t);
	    isFound = 1;
	    break;
	}
    }
    if(!isFound)
    {
	printf("No Record Found!!!!!!!!!\n");
    }
    fclose(t);
    return;
}


void delete_record()
{
	FILE *t, *temp;
	char ts_name[15];

    printf("Delete Record\n");


    t = fopen("detail.bin","rb");
    temp = fopen("temp.bin", "wb");
    printf("Enter TRAIN Name to Delete : ");
    fflush(stdin);
	gets(ts_name);
    while(fread(&te, sizeof(te),1,t) == 1)
	{
	if(strcmp(ts_name,te.train_name) != 0)
	{
	    fwrite(&te,sizeof(te),1,temp);
	}
    }
    fclose(t);
    fclose(temp);
    remove("detail.bin");
    rename("temp.bin","detail.bin");
    printf("The record is  deleted.....\n");
    return;
}


void display_record()
{
	FILE *t;
	t= fopen("detail.bin","rb");
    while(fread(&te, sizeof(te),1,t))
    {
	if(t==NULL)
	     printf("NO TRAIN RECORD...");
	else
	{
	     printf("\n  TRAIN NAME: %s",te.train_name);
	     printf("\n  TRAIN NUMBER: %s",te.train_no);
	     printf("\n  TOTAL TIME(IN MINUTES): %s",te.time);
	     printf("\n  TIME INTERVAL(IN MINUTES): %s",te.interval);
	     printf("\n  SIZE: %s",te.size);
	     printf("\n  SPEED: %s",te.speed);
	}
    }
    fclose(t);
}
/*void gotoxy(int a, int b)
{
	COORD c;
	c.X=a;
	c.Y=b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
} */
void main()
{
	      int choice;
		gotoxy(50,50);
//	SetConsoleTitle("TRAIN ENQUIREY SYSTEM");

    while(1)
    {
	printf("\n             \t WELCOME TO RAILWAY ENQURIEY       \n");
	printf("****************************************************\n");
	printf("*         1. ADD TRAIN DETAILS:                    *\n");
	printf("*         2. SEARCHING OF A TRAIN:                 *\n");
	printf("*         3. MODIFICATION OF TRAIN RECORD:         *\n");
	printf("*         4. DELETE OF TRAIN RECORD:               *\n");
	printf("*         5. DISPLAY OF ALL TRAIN RECORDS:         *\n");
	printf("*         6. EXIT:                                 *\n");
	printf("****************************************************\n");
	printf("\n\n SELECT YOUR OPTION: ");
	scanf("%d",&choice);

	switch(choice)
	{
	    case 1:
		add_record();
		break;
	    case 2:
		search_record();
		break;
	    case 3:
		modify_record();
		break;
	    case 4:
		delete_record();
		break;
	    case 5:
		display_record();
			break;
	   case 6:
			 exit(0);
			 break;
	    default:
		break;
	}

    }

}