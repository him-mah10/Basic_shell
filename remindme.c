//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

char *remindmeComm[]={"sleep","20"};

int cm_remindme(char **brokenCommand)
{
	pid_t pid,wpid;
	pid=fork();
	int status;
	if(pid<0)
	{
		printf("\033[0;32mCannot Create Child Process\033[0m\n");
	}
	else if(pid==0)
	{
		strcpy(remindmeComm[1],brokenCommand[1]);
		printf("%s",remindmeComm[1]);
		if(execvp(remindmeComm[0],remindmeComm)==-1)
		{
			printf("%s: \033[0;31mcommand not found\033[0m\n",brokenCommand[0]);
		}
	}
	else
	{
		int j=3;
		char message[10000];
		strcpy(message,brokenCommand[2]);
		while(brokenCommand[j]!=NULL)
		{
			strcat(message,brokenCommand[j++]);
		}
		storeInfo(pid,message,1);
	}
	return 1;
}