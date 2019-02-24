//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

int cm_setenv(char **brokenCommand)
{
	int i=0,count=0;
	while(brokenCommand[i])
	{
		count++;
		i++;
	}
	if(count==1 || count>3)
	{
		printf("\033[0;31mArguments Not Correct\033[0m\n");
		return 1;
	}
	else if(count==2)
	{
		setenv(brokenCommand[1],"",1);
	}
	else if(count==3)
	{
		setenv(brokenCommand[1],brokenCommand[2],1);
	}
	return 1;
}

int cm_unsetenv(char **brokenCommand)
{
	if(brokenCommand[1]==NULL)
	{
		printf("\033[0;31mArguments Not Correct\033[0m\n");
		return 1;
	}
	if(unsetenv(brokenCommand[1])!=0)
		printf("\033[0;31mError: Envriornment Variable Not Found\033[0m\n");
	return 1;
}