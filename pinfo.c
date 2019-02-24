//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

int cm_pinfo(char **brokenCommand)
{
	int pid;
	char str[128];
	if(brokenCommand[1]==NULL)
	{
		pid=getpid();
	}
	else
	{
		pid=atoi(brokenCommand[1]);
		if(kill(pid,0))
		{
			perror("\033[0;32mInvalid PID\033[0m");
			return 1;
		}
		//kill(pid,0) is just used to check if the pid provided is correct of not
	}
	printf("\033[0;32mpid -- \033[0m%d\n",pid);	
	sprintf(str,"/proc/%d/status",pid);
	FILE* file=fopen(str,"r");
	int i=0;
	char line[4098];
	while(fgets(line,sizeof(line),file))
	{
		i++;
		if(i==3)
		{
			printf("\033[0;32mProcess Status -- \033[0m%c\n",line[7]);
		}
		else if(i==18)
		{
			printf("\033[0;32mVirtual Memory - \033[0m");
			for(int j=0;j<strlen(line);j++)
			{
				if(isdigit(line[j]))
					printf("%c",line[j]);
			}
			printf("\n");
		}
	}
	fclose(file);
	sprintf(str,"/proc/%d/exe",pid);
	int p=readlink(str,line,sizeof(line));
	line[p]='\0';
	//sprintf store '/proc/pid/status' in str string
	
	int ii=0,flag=0;
	//flag==0 => that we went into the subdirectory
	//flag==1 => that we are in any directory other than subdirectory
	char addPrint[4098];
	if(strlen(line)<strlen(home))
	{
		flag=1;
		strcpy(addPrint,line);
	}
	while(home[ii]!='\0' && flag==0)
	{
		if(home[ii]!=line[ii])
		{
			flag=1;
		}
		ii++;
	}
	if(flag == 0 && strlen(line)==strlen(home))
	{
		addPrint[0]='~';
		addPrint[1]='\0';
	}
	else if(flag==0)
	{
		int len=1;
		addPrint[0]='~';
		if(line[ii]!='/')
		{
			addPrint[len++]='/';	
		}
		while(line[ii]!='\0')
		{
			addPrint[len]=line[ii];
			ii++;
			len++;
		}
		addPrint[len]='\0';
	}
	else if(flag==1)
	{
		strcpy(addPrint,line);
	}
	//The above code is just to print it in the format of ~/
	//printf("%s",str);nshu-VPCEB16FG:~$ 



	printf("\033[0;32mExecutable Path -- \033[0m%s\n",addPrint);
	return 1;
}
