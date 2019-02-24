//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

int cm_cd(char ** brokenCommand)
{
	if(brokenCommand[1]==NULL || strcmp(brokenCommand[1],"--")==0)
	{
		getcwd(curDir,sizeof(curDir));
		strcpy(preDir,curDir);
		chdir(home);
	}
	else if(brokenCommand[1][0]=='-')
	{
		if(strlen(preDir)==0)
		{
			printf("\033[0;31mError: OLDPWD not set.\n\033[0m");	
		}
		else
		{
			getcwd(curDir,sizeof(curDir));
			chdir(preDir);
			strcpy(preDir,curDir);
		}
	}
	else
	{
		if(brokenCommand[1][0]=='~')
		{
			brokenCommand[1]=brokenCommand[1]+1;
			getcwd(preDir,sizeof(preDir));
			strcpy(curDir,home);
			strcat(curDir,brokenCommand[1]);
			if(chdir(curDir)!=0)
			{
				printf("\033[0;31mError: %s: Wrong file name or directory name.Also if it exits than you don't have permission to access it.\n\033[0m",brokenCommand[1]);		
			}
		}
		else
		{
			getcwd(preDir,sizeof(preDir));
			if(chdir(brokenCommand[1])!=0)
			{
				printf("\033[0;31mError: %s: Wrong file name or directory name.Also if it exits than you don't have permission to access it.\n\033[0m",brokenCommand[1]);		
			}
		}
	}
	return 1;
}


int cm_pwd(char ** brokenCommand)
{
	if(getcwd(curDir,sizeof(curDir))!=NULL)
		printf("%s\n",curDir);
	else
		printf("\033[0;31mError: Unable to access directory.\033[0m\n");
	return 1;
}


int cm_echo(char ** brokenCommand)
{
	if(brokenCommand[1]==NULL)
	{
		printf("\n");
	}
	else if(brokenCommand[1][0]=='$' && brokenCommand[2]==NULL)
	{
		char variable[100];
		for(int i=1;i<strlen(brokenCommand[1]);i++)
		{
			variable[i-1]=brokenCommand[1][i];
		}
		char * value=getenv(variable);
		if(value)
			printf("%s\n",value);
		else
			printf("\n");
	}
	else
	{
		int i=1;
		while(brokenCommand[i]!=NULL)
		{
			printf("%s ",brokenCommand[i]);
			i++;
		}
		printf("\n");
	}
	return 1;
}


int cm_quit(char ** brokenCommand)
{
	return 0;
}


void lsMl(char * fileName)
{
	//ls -l or ls -la
	struct stat file;
	int color=0;
	if(stat(fileName,&file)<0)
		return;
	if(S_ISREG(file.st_mode))
	{
		printf("-");//cyan-6
	}
	else if(S_ISDIR(file.st_mode))
	{
		printf("d");//red-1
		color=1;
	}
	else if(S_ISCHR(file.st_mode))
	{
	    printf("c");//yellow-2
	    color=2;
	}
	else if(S_ISBLK(file.st_mode))
	{
	    printf("b");//green-3
	    color=3;
	}
	else if(S_ISFIFO(file.st_mode))
	{
	    printf("f");//blue-4
	    color=4;
	}
	else if(S_ISLNK(file.st_mode))
	{
	    printf("l");//magenta-5
	    color=5;
	}
	else
	{
	    printf("s");//white-0
	    color=6;
	}

	printf( (file.st_mode & S_IRUSR) ? "r" : "-");
    printf( (file.st_mode & S_IWUSR) ? "w" : "-");
    printf( (file.st_mode & S_IXUSR) ? "x" : "-");
    printf( (file.st_mode & S_IRGRP) ? "r" : "-");
    printf( (file.st_mode & S_IWGRP) ? "w" : "-");
    printf( (file.st_mode & S_IXGRP) ? "x" : "-");
    printf( (file.st_mode & S_IROTH) ? "r" : "-");
    printf( (file.st_mode & S_IWOTH) ? "w" : "-");
    printf( (file.st_mode & S_IXOTH) ? "x " : "- ");
    
    printf("%ld ",file.st_nlink);
    
    struct passwd *pw = getpwuid(file.st_uid);
    struct group *gr = getgrgid(file.st_gid);
    printf("%s ",pw->pw_name);
    printf("%s ",gr->gr_name);

    printf("%ld ",file.st_size);

    char *Time;
    Time=ctime(&file.st_mtime);
    Time=Time+4;
    Time[12]='\0';
    printf("%s",Time);

    if(color==1)
    	printf("\033[0;31m");
    else if(color==2)
    	printf("\033[0;33m");
    else if(color==3)
    	printf("\033[0;32m");
    else if(color==4)
    	printf("\033[0;34m");
	else if(color==5)
		printf("\033[0;35m");
	else if(color==0)    	
		printf("\033[0;36m");
    printf(" %s\033[0m",fileName);
	printf("\n");
}


int cm_ls(char ** brokenCommand)
{
	struct dirent *file;
	DIR *files=opendir(".");

	if(files==NULL)
	{
		printf("\033[0;31mError: Unable to access directory.\033[0m\n");
	}

	if(brokenCommand[1]==NULL || strcmp(brokenCommand[1],".")==0)
	{
		while((file=readdir(files))!=NULL)
		{
			if(file->d_name[0]=='.')
				continue;
			if(file->d_type==DT_DIR)
			{
				printf("\033[1;31m%s\n\033[0m",file->d_name);	
			}
			else
			{
				printf("%s\n",file->d_name);
			}
		}
	}
	else if(strcmp(brokenCommand[1],"-a")==0)
	{
		while((file=readdir(files))!=NULL)
		{
			if(file->d_type==DT_DIR)
			{
				printf("\033[1;31m%s\n\033[0m",file->d_name);	
			}
			else
			{
				printf("%s\n",file->d_name);
			}
		}
	}
	else if(strcmp(brokenCommand[1],"-al")==0 || strcmp(brokenCommand[1],"-la")==0)
	{
		while((file=readdir(files))!=NULL)
		{
			lsMl(file->d_name);
		}	
	}
	else if(strcmp(brokenCommand[1],"-l")==0)
	{
		while((file=readdir(files))!=NULL)
		{
			if(file->d_name[0]!='.')
			{
				lsMl(file->d_name);
			}
		}	
	}
	else
	{
		printf("\033[0;31mls: invalid option '%s'\033[0m\n",brokenCommand[1]);
	}
	file=readdir(files);
	closedir(files);	
	return 1;
}