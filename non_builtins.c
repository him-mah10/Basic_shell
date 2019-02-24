//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

char cnd[1000];

void storeInfo(int pid,char * command,int flag)
{
	store[maxbg].pid=pid;
	store[maxbg].jobid=maxbg;
	strcpy(store[maxbg].command,command);
	store[maxbg].flag=flag;
	maxbg++;
	//printf("%s\n",store[maxbg-1].command);
}

void bgExecute()
{
	pid_t wpid;
	int status;
	while((wpid=waitpid(-1,&status,WNOHANG))>0)
	{
		if(WIFEXITED(status) == 0 || WIFSIGNALED(status) ==0)
		{
			for(int i=0;i<maxbg;i++)
			{
				if(store[i].pid==wpid && store[i].flag==0)
				{
					printf("\n[%d] Done       %s       with pid %d\n",store[i].jobid,store[i].command,wpid);
					print_prompt();
				}
				else if(store[i].pid==wpid && store[i].flag==1)
				{
					printf("\n\033[0;31mReminder:\033[0m %s\n",store[i].command);
					print_prompt();
				}
			}
		}
	}
	if(waitpid(-1,&status,WNOHANG)==-1)
		maxbg=0;	
}

void nonBuiltInExe(char ** brokenCommand)
{
	int status,bg=0;
	pid_t pid,wpid;
	pid=fork();
	for(int i=0;;i++)
	{
		if(brokenCommand[i]==NULL)
			break;
		if(strcmp(brokenCommand[i],"&")==0)
		{
			bg=1;
			brokenCommand[i]=NULL;
			break;
		}
	}

	if(pid<0)
	{
		printf("\033[0;32mCannot Create Child Process\033[0m\n");
	}
	else if(pid==0)
	{
		if(execvp(brokenCommand[0],brokenCommand)==-1)
		{
			printf("%s: \033[0;31mcommand not found\033[0m\n",brokenCommand[0]);
		}
		else
			exit(0);
	}
	else
	{
		if(bg==1)
		{
			storeInfo(pid,brokenCommand[0],0);
			//printf("fdsd\n");
			//bgExecute();
		}
		else
		{
			sigpid=pid;
			do
			{
				wpid=waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status)&&!WIFSIGNALED(status));
			sigpid=0;
			strcpy(cnd,brokenCommand[0]);

		}
	}
	//bgExecute();
}

void siginter(int signalNum)
{
	if(sigpid)
	{
		if(kill(sigpid,SIGINT))
		{
			return;
		}
	}
	else
	{
		signal(signalNum,SIG_IGN);
		//printf("\n");
		//print_prompt();
		fflush(stdout);
		signal(signalNum,siginter);
	}
}

void sigtstper(int signalNum)
{
	if(sigpid)
	{
		if(kill(sigpid,SIGTSTP)==0)
		{
			store[maxbg].pid=sigpid;
			strcpy(store[maxbg].command,cnd);
			store[maxbg].jobid=maxbg;
			store[maxbg].flag=2;
			maxbg++;
			printf("[%d] Stopped %s[%d]\n",store[maxbg-1].jobid,store[maxbg-1].command,store[maxbg-1].pid);
			start();
		}
	}
	else
	{
		printf("\n");
		print_prompt();
		signal(signalNum,SIG_IGN);
		fflush(stdout);
		signal(signalNum,sigtstper);
	}
}