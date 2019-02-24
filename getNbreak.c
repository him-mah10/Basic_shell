//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

void getCommands(char * input)
{
	//Get input from the user, it has semi colon seperated commands
		int bufsize=64,position=0;
		commands=malloc(bufsize*sizeof(char *));
		char *command;		
		//command is just a temporary string to store the commands.
		if(!commands)
		{
			printf("Allocation error\n");
			exit(1);
		}
		command=strtok(input,";");
		while(command!=NULL)
		{
			commands[position]=command;
			position++;
			if(position>=bufsize)
			{
				//Incase there are more than 64 commands.
				bufsize+=64;
				commands=realloc(commands,bufsize*sizeof(char*));
				if(!commands)
				{
					printf("Allocation error\n");
					exit(1);			
				}
			}
			command=strtok(NULL,";");
		}
		commands[position]=NULL;
		//Last contains NULL, so that we know where is the ending
		/*
		--> Tester
		printf("Here");
		position=0;
		command=commands[position];
		while(command)
		{
			printf("\n%s",command);
			position++;
			command=commands[position];
		}
		*/
}

char ** breakCommands(char * command)
{
	//command -> contains the command that needs to be seperated by space,
	//    the breakCommands seperate commands on the basis of space(tabs,newline etc.)
	int bufsize=64,position=0;
	char **comParts=malloc(bufsize*sizeof(char *));
	char *comPart;
	//comParts stores all the parts of the command viz the command name, its arguments etc.		
	//comPart is just a temporary string to store the commands.
	if(!comParts)
	{
		printf("Allocation error\n");
		exit(1);
	}
	comPart=strtok(command," \t\r\n\a");
	while(comPart!=NULL)
	{
		comParts[position]=comPart;
		position++;
		if(position>=bufsize)
		{
			//Incase there are more than 64 commands.
			bufsize+=64;
			comParts=realloc(comParts,bufsize*sizeof(char*));
			if(!comParts)
			{
				printf("Allocation error\n");
				exit(1);			
			}
		}
		comPart=strtok(NULL," \t\r\n\a");
	}
	comParts[position]=NULL;
	//Last contains NULL, so that we know where is the ending
	/*
	--> Tester
	printf("Here");
	position=0;
	comPart=comParts[position];
	while(comPart)
	{
		printf("\n%s",comPart);
		position++;
		comPart=comParts[position];
	}
	*/	
	return comParts;	
}