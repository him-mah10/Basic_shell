//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

int main()
{
	keeprunning=1;
	maxbg=0;
	//builtins[]={"cd","pwd","echo","exit","ls","pinfo","remindme","clock"};
	numberOfBuiltins=15;
	if(signal(SIGINT,siginter)==SIG_ERR)
	{
		printf("SIGINT error\n");
		exit(1);
	}
	signal(SIGTSTP,sigtstper);
	strcpy(preDir,"");
	getcwd(home,sizeof(home));
	start();
	return 0;
}