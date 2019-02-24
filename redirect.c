//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

void redirection_func(char ** brokenCommand)
{
	int i=0,input=0,output=0,append=0;
	
	while(brokenCommand[i]!=NULL)
	{
		if(strcmp(brokenCommand[i],"<")==0)
		{
			input=i;
		}
		else if(strcmp(brokenCommand[i],">")==0)
		{
			output=i;
		}
		else if(strcmp(brokenCommand[i],">>")==0)
		{
			append=i;
		}
		i++;
	}

	int original_out=dup(fileno(stdout));
	close(fileno(stdout));	

	if(output || append)
	{
		char * cmd[100];
		int out;
		if(output)
			out=open(brokenCommand[output+1], O_WRONLY | O_CREAT | O_TRUNC ,0644);
		else
			out=open(brokenCommand[append+1], O_WRONLY | O_CREAT | O_APPEND ,0644);
		if(out == -1)
		{
			perror("\033[0;31mError opening the file\033[0m\n");
		}

		fflush(stdout);	
		dup2(out,fileno(stdout));

		if(input)
		{
			int j=0;
			while(strcmp(brokenCommand[j],"<") !=0 )
			{
				cmd[j]=brokenCommand[j];
				j++;
			}
			cmd[j]=brokenCommand[input+1];
			cmd[j+1]=NULL;
		}
		else
		{
			int j=0;
			while(strcmp(brokenCommand[j],">")!=0 && strcmp(brokenCommand[j],">>")!=0)
			{
				cmd[j]=brokenCommand[j];
				j++;	
			}
			cmd[j]=NULL;
		}
		
		int pid = fork(),status;
		pid_t wpid;
		if(pid==0)
			execvp(cmd[0],cmd);
		else
		{
			do
			{
				wpid=waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));	
		}

		fflush(stdout);
		close(out);
		dup2(original_out,fileno(stdout));
		close(original_out);
	}
	else if(input)
	{
		dup2(original_out,fileno(stdout));
		close(original_out);
		char * cmd[100];
		int j=0;
		while(strcmp(brokenCommand[j],"<")!=0)
		{
			cmd[j]=brokenCommand[j];
			j++;
		}
		cmd[j]=brokenCommand[input+1];
		cmd[j+1]=NULL;
		j=0;
		int pid=fork();
		int status;
		pid_t wpid;
		if(pid==0)
			execvp(cmd[0],cmd);
		else
		{
			do
			{
				wpid=waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}