//DEVELOPED BY: HIMANSHU MAHESHWARI

#ifndef function
#define function

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>

void print_prompt();
void getCommands(char * input);
char ** breakCommands(char * command);
int cm_remindme(char **brokenCommand);
int cm_cd(char ** brokenCommand);
int cm_setenv(char ** brokenCommand);
int cm_unsetenv(char ** brokenCommand);
int cm_pwd(char ** brokenCommand);
int cm_echo(char ** brokenCommand);
int cm_quit(char ** brokenCommand);
int cm_jobs(char ** brokenCommand);
int cm_kjob(char ** brokenCommand);
int cm_fg(char ** brokenCommand);
int cm_bg(char ** brokenCommand);
int cm_overkill(char ** brokenCommand);
void lsMl(char * fileName);
int cm_ls(char ** brokenCommand);
int cm_pinfo(char **brokenCommand);
void signal_handler(int sig);
int cm_clockt(char **brokenCommand);
void storeInfo(int pid,char * command,int flag);
void bgExecute();
void siginter(int signalNum);
void sigtstper(int signalNum);
void nonBuiltInExe(char ** brokenCommand);
int executeCmd(char ** brokenCommand);
int cm_remindme(char **brokenCommand);
void redirection_func(char ** brokenCommand);
void start();
void piping_func(char ** brokenCommand);

char home[4098];
char preDir[4098];
int numberOfBuiltins;
int sigpid;
int keeprunning;
char hostname[66];
char username[66];
char curDir[4098];
char **commands;
struct infoStore
{
	int pid;
	int jobid;
	char command[1000];
	int flag;
}store[1000];
int maxbg;

//The address of any directory can be max 4096(took 2 extra), similarily (home stores the address of place from where the program is called)
//  the hostname and username can be max 64(took 2 extra)
//commands contains all the commands that were seperated by ';' once we have all the commands we need to seperate it by 
//   the spaces. 


#endif
