//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

void piping_func(char ** brokenCommand)
{
	//This shall convert it into a single command so that later we can convienently break it on the basis of '|'
	int original_input=dup(STDIN_FILENO);
	int original_output=dup(STDOUT_FILENO);
	int pid,status;
	pid_t wpid;
	int i=0;
	pid=fork();
	if(pid<0)
	{
		perror("Forking Error");
		return;
	}
	else if(pid==0)
	{
		char enteredCommand[2000];
		enteredCommand[0]='\0';
		while(brokenCommand[i]!=NULL)
		{
			strcat(enteredCommand,brokenCommand[i]);
			strcat(enteredCommand," "
				);
			i++;
		}
		//This shall break it on the basis of '|' and then store it in commands
		//This is analogus to ';' seperation which was there in breakCommand
		int bufsize=64,position=0;
		char *command,**commands;		
		commands=malloc(bufsize*sizeof(char *));
		if(!commands)
		{
			printf("Allocation error\n");
			return;
		}
		command=strtok(enteredCommand,"|");
		while(command!=NULL)
		{
			commands[position]=command;
			position++;
			if(position>=bufsize)
			{
				bufsize+=64;
				commands=realloc(commands,bufsize*sizeof(char*));
				if(!commands)
				{
					printf("Allocation error\n");
					return;			
				}
			}
			command=strtok(NULL,"|");
		}
		commands[position]=NULL;
		int tmo=position-1;
		i=0;
		
		while(i<tmo)
		{
			char ** comParts = breakCommands(commands[i]);
			int pip[2],input=0,output=0,append=0,j=0;
			pipe(pip);
			pid=fork();
			while(comParts[j])
			{
				if(strcmp(comParts[j],"<")==0)
					input=j;
				else if(strcmp(comParts[j],">")==0)
					output=j;
				else if(strcmp(comParts[j],">>")==0)
					append=j;
				j++;
			}
			if(pid==0)
			{
				dup2(pip[1],STDOUT_FILENO);
				execvp(comParts[0],comParts);
			}
			else
			{
				do
				{
					wpid=waitpid(pid,&status,WUNTRACED);
				}while(!WIFEXITED(status) && !WIFSIGNALED(status));
			}
			dup2(pip[0],STDIN_FILENO);
			close(pip[1]);	
			i++;
		}
		char ** comParts=breakCommands(commands[i]);
		if(execvp(comParts[0],comParts)==-1)
			kill(getpid(),SIGTERM);
		exit(0);

	}
	else
	{
			do
			{
				wpid=waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
			dup2(original_input,STDIN_FILENO);
			dup2(original_output,STDOUT_FILENO);
	}
}