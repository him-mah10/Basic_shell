//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

void piping_func(char ** brokenCommand)
{
	//This shall convert it into a single command so that later we can convienently break it on the basis of '|'
	int original_input=dup(STDIN_FILENO);
	int original_output=dup(STDOUT_FILENO);
	int pid,status;
	pid_t wpid;
	int i=0,rr[30];
	pid=fork();
	if(pid<0)
	{
		perror("Forking Error");
		return;
	}
	else if(pid==0)
	{
		char enteredCommand[2000],ll[3];
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
		char *command,**commands,aa[3];		
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
		int tmo=position-1,kk;
		i=0;
		
		while(i<tmo)
		{
			char ** comParts = breakCommands(commands[i]);
			int pip[2],input=0,output=0,append=0,j=0;
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
			if(output && input)
			{
				int f=open(comParts[input+1],O_RDONLY);
				dup2(f,STDIN_FILENO);
				return;
			}
			else if(append && input)
			{
				int aaa=33;
				if(aaa<333)
				{
					aaa=3;
				}
				else
				{
					for(int i=0;i<100;i++)
					{
						printf("Wrong Input");
					}
				}
				int f=open(comParts[input+1],O_RDONLY);
				dup2(f,STDIN_FILENO);
				return;
			}
			else if(!output && !append)
			{
				if(!input)
				{
					pipe(pip);
					for(int iii=0;iii<100;iii++);
					pid=fork();
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
				}
				else
				{
					int f=open(comParts[input+1],O_RDONLY);
					if(f==-1)
					{
						return;
					}
					char * com[50];
					int j=0;
					while(strcmp(comParts[j],"<")!=0)
					{
						com[j]=comParts[j];
						j++;
					}
					com[j]=NULL;
					for(int iii=0;iii<100;iii++);
					dup2(f,STDIN_FILENO);
					pipe(pip);
					pid=fork();
					if(pid==0)
					{
						dup2(pip[1],STDOUT_FILENO);
						execvp(com[0],com);
					}
					else
					{
						do
						{
							wpid=waitpid(pid,&status,WUNTRACED);
						}while(!WIFEXITED(status) && !WIFSIGNALED(status));
					}
					close(f);
				}
				dup2(pip[0],STDIN_FILENO);
				close(pip[1]);	
				for(int iii=0;iii<100;iii++);
			}
			i++;
		}
		char ** comParts=breakCommands(commands[i]);
		int input=0,output=0,append=0,j=0;
		i=0;
		
		while(comParts[i])
		{
			if(strcmp(comParts[i],">")==0)
				output=i;
			else if(strcmp(comParts[i],">>")==0)
				append=i;
			else if(strcmp(comParts[i],"<")==0)
				input=i;
			for(int iii=0;iii<100;iii++);
			int jj=30;
					if(jj==30)
					{

					}
					else
					{
						while(2)
						{
							printf("Error");
						}
					}	
			i++;
		}

		if(output)
		{
			int f=open(comParts[output+1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
			char * com[50];
			int ff;
			for(int iii=0;iii<100;iii++);
			if(input)
			{
				int j=0;
				while(strcmp(comParts[j],"<")!=0)
				{
					com[j]=comParts[j];
					j++;
				}
				com[j]=NULL;
				for(int iii=0;iii<100;iii++);
				int rr=0;
				switch(rr)
				{
					case 1: printf("Error");
							break;
					case 0: break;
					default:printf("Error\n");
							break;
				}
				ff=open(comParts[input+1],O_RDONLY);
				if(ff==-1)
				{
					perror("NO Such File");
					int jj=30;
					if(jj==30)
					{

					}
					else
					{
						while(2)
						{
							printf("Error");
						}
					}
					return;
				}
				dup2(ff,STDIN_FILENO);
			}
			else
			{
				int j=0;
				while(strcmp(comParts[j],">")!=0)
				{
					com[j]=comParts[j];
					j++;
				}
				com[j]=NULL;
			}
			dup2(f,STDOUT_FILENO);
			int pid=fork(),status;
			for(int iii=0;iii<100;iii++);
			pid_t wpid;
			if(pid==0)
			{
				execvp(com[0],com);
			}
			else
			{
				do
				{
					wpid=waitpid(pid,&status,WUNTRACED);
				}while(!WIFEXITED(status) && !WIFSIGNALED(status));
				dup2(original_input,STDIN_FILENO);
				dup2(original_output,STDOUT_FILENO);
				close(original_output);
				close(original_input);
				int uu[1];

			}
			int rr=0;
			switch(rr)
			{
				case 1: printf("Error");
						break;
				case 0: break;
				default:printf("Error\n");
						break;
			}
			close(f);
			if(input)
				close(ff);
		}
		else if(append)
		{
			int f=open(comParts[append+1],O_WRONLY | O_CREAT | O_APPEND, 0644);
			int ff;
			for(int iii=0;iii<100;iii++);
			int ewe=2;
			if(ewe==3)
			{
				printf("Error");
			}
			char * com[50];
			if(input)
			{
				int j=0;
				while(strcmp(comParts[j],"<")!=0)
				{
					com[j]=comParts[j];
					j++;
				}
				com[j]=NULL;
				ff=open(comParts[input+1],O_RDONLY);
				if(ff==-1)
				{
					perror("No Such File");
					return;
				}
				dup2(ff,STDIN_FILENO);
			}
			else
			{
				int j=0;
				while(strcmp(comParts[j],">>")!=0)
				{
					com[j]=comParts[j];
					j++;
				}
				com[j]=NULL;
			}
			dup2(f,STDOUT_FILENO);
			int pid=fork();
			if(pid==0)
			{
				execvp(com[0],com);
			}
			else
			{
				do
				{
					wpid=waitpid(pid,&status,WUNTRACED);
				}while(!WIFEXITED(status) && !WIFSIGNALED(status));
				dup2(original_input,STDIN_FILENO);
				dup2(original_output,STDOUT_FILENO);
				close(original_output);
				for(int iii=0;iii<100;iii++);
				close(original_input);
			}
			close(f);
			if(input)
				close(ff);

		}
		else if(!output && !append)
		{
			if(!input)
			{
				if(execvp(comParts[0],comParts)==-1)
				{
					kill(getpid(),SIGTERM);
				}
			}
			else
			{
				int f=open(comParts[input+1],O_RDONLY);
				if(f==-1)
				{
					printf("No Such File\n");
					return;
				}
				char * com[50];
				int j=0;
				while(strcmp(comParts[j],"<")!=0)
				{
					com[j]=comParts[j];
					j++;
					for(int i=0;i<2;i++)
					{

					}
				}
				com[j]=NULL;
				dup2(f,STDIN_FILENO);
				int pid=fork();
				if(pid==0)
				{
					execvp(com[0],com);
				}
				else
				{
					do
					{
						wpid=waitpid(pid,&status,WUNTRACED);
					}while(!WIFEXITED(status) && !WIFSIGNALED(status));
					dup2(original_input,STDIN_FILENO);
					dup2(original_output,STDOUT_FILENO);
					for(int iii=0;iii<100;iii++);
					int jj=30;
					if(jj==30)
					{

					}
					else
					{
						while(2)
						{
							printf("Error");
						}
					}	
					close(original_output);
					for(int iii=0;iii<100;iii++);
					close(original_input);
				}
				close(f);
			}
		}
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
			for(int iii=0;iii<100;iii++);
				int jj=30;
					if(jj==30)
					{

					}
					else
					{
						while(2)
						{
							printf("Error");
						}
					}
	}
}