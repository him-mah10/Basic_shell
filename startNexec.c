//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

char *builtins[]={"cd","pwd","echo","quit","ls","pinfo","remindme","clock","setenv","unsetenv","jobs","kjob","fg","bg","overkill"};
int (*builtinsFunc[]) (char **)={ &cm_cd, &cm_pwd, &cm_echo, &cm_quit, &cm_ls, &cm_pinfo, &cm_remindme, &cm_clockt, &cm_setenv, &cm_unsetenv, &cm_jobs, &cm_kjob, &cm_fg, &cm_bg, &cm_overkill};

int executeCmd(char ** brokenCommand)
{
	if(brokenCommand[0]==NULL)
	{
		return 1;
	}

	
	int redirection=0,i=0,piping=0;
	
	while(brokenCommand[i]!=NULL)
	{
		if((strcmp(brokenCommand[i],">") == 0) || (strcmp(brokenCommand[i],"<") == 0) || (strcmp(brokenCommand[i],">>") == 0) )
		{
			redirection=1;
		}
		if(strcmp(brokenCommand[i],"|")==0)
		{
			piping=1;
		}
		i++;
	}

	if(piping)
	{
		piping_func(brokenCommand);
		return 1;
	}

	if(redirection)
	{
		redirection_func(brokenCommand);
		return 1;
	}

	for(int i=0;i<numberOfBuiltins;i++)
	{
		if(strcmp(builtins[i],brokenCommand[0])==0)
		{
			return (*builtinsFunc[i])(brokenCommand);
		}
	}
	nonBuiltInExe(brokenCommand);
	return 1;
}



void start()
{
	int status=0;
	//Status decides if we have to quit or not
	do
	{
		print_prompt();
		keeprunning=1;
		char * input = NULL;
		ssize_t input_size=0;
		
		//This block gets the input from the user
		//Ctrl + D returns -1, so this case handles it
		bgExecute();

		if(getline(&input,&input_size,stdin)==-1)
		{
			printf("\n");
			exit(1);
		}

		//This block gets all the commands that are seperated by ;
		getCommands(input);
		int position=0;
		while(commands[position])
		{
			//This block breaks the command on the basis of spaces
			char **brokenCommand = breakCommands(commands[position]);
			status=executeCmd(brokenCommand);
			position++;
		}
	}while(status);
}

