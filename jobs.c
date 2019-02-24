//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

int cm_jobs(char ** brokenCommand)
{
	for(int i=0;i<maxbg;i++)
	{
		if(store[i].flag==0 || store[i].flag==1)
			printf("[%d]	Running		%s [%d]\n",store[i].jobid+1,store[i].command,store[i].pid);
		else if(store[i].flag==2)
			printf("[%d]	Stopped		%s [%d]\n",store[i].jobid+1, store[i].command, store[i].pid);
	}
	return 1;
}

int cm_kjob(char ** brokenCommand)
{
	if(brokenCommand[1] == NULL || brokenCommand[2] ==NULL)
	{
		printf("\033[0;31mError: \033[0mImproper Number Arguments\n");
		return 1;
	}
	int jobid=atoi(brokenCommand[1]);
	jobid--;
	if(jobid>maxbg)
	{
		printf("\033[0;31mError:\033[0m Job number does not exist\n");
		return 1;
	}
	int signal=atoi(brokenCommand[2]);
	kill(store[jobid].pid,signal);
	if(signal==9)
		store[jobid].flag=-1;//To be ignored
	else if(signal==19 || signal==20)
		store[jobid].flag=2;//To be stoppend
	else if(signal==18)
		store[jobid].flag=0;//To convert stopped into running
	return 1;
}

int cm_fg(char ** brokenCommand)
{
	if(brokenCommand[1] == NULL)
	{
		printf("\033[0;31mError: \033[0mImproper Number Arguments\n");
		return 1;	
	}
	pid_t wpid;
	int jobid=atoi(brokenCommand[1]);
	jobid--;
	if(jobid>=maxbg)
	{
		printf("\033[0;31mError:\033[0m Job number does not exist\n");
		return 1;
	}	
	printf("Running Process: %s\n",store[jobid].command);
	int status;
	if(store[jobid].flag == 0 || store[jobid].flag==1)
		store[jobid].flag=-1;
	else if(store[jobid].flag==2)
	{
		kill(store[jobid].pid,SIGCONT);
		store[jobid].flag=-1;
	}
	do
	{
		wpid=waitpid(store[jobid].pid,&status,WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
	
	return 1;
}

int cm_bg(char ** brokenCommand)
{
	if(brokenCommand[1] == NULL)
	{
		printf("\033[0;31mError: \033[0mImproper Number Arguments\n");
		return 1;	
	}
	int jobid=atoi(brokenCommand[1]);
	jobid--;
	if(store[jobid].flag==2)
	{
		kill(store[jobid].pid,18);
		store[jobid].flag=0;
	}
	return 1;
}

int cm_overkill(char ** brokenCommand)
{
	for(int i=0;i<maxbg;i++)
	{
		if(store[i].flag==0 || store[i].flag==2 ||store[i].flag==1)
		{
			kill(store[i].pid,15);
			store[i].flag=-1;
		}
	}
	maxbg=0;
	return 1;
}

