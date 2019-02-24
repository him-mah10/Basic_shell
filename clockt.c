//DEVELOPED BY: HIMANSHU MAHESHWARI

#include "function.h"

void signal_handler(int sig)
{
	keeprunning=0;
}

int cm_clockt(char **brokenCommand)
{
	//printf("\n");
	if(brokenCommand[1]==NULL || brokenCommand[2]==NULL)
	{
		printf("%s: \033[0;31mcommand not found\033[0m\n",brokenCommand[0]);
		return 1;
	}

	int hour=0,min=0,sec=0,which=0,preSec=0,lim=atoi(brokenCommand[2]),day=0,month=0,year=0;
	char line[4098],mon[4];
	FILE* file=fopen("/proc/driver/rtc","r");
	fgets(line,sizeof(line),file);
	
	for(int i=0;i<strlen(line);i++)
	{
		if(isdigit(line[i]))
		{
			if(which==1)
			{
				hour=hour*10+(int)line[i]-48;
			}
			else if(which==2)
			{
				min=min*10+(int)line[i]-48;
			}
			else
			{
				preSec=preSec*10+(int)line[i]-48;
			}
		}
		if(line[i]==':')
			which++;
	}

	hour=(hour+5+((min+30)/60))%24;
	min=(min+30)%60;
	
	fgets(line,sizeof(line),file);
	which=0;
	for(int i=0;i<strlen(line);i++)
	{
		if(isdigit(line[i]))
		{
			if(which==0)
			{
				year=year*10+(int)line[i]-48;
			}
			else if(which==1)
			{
				month=month*10+(int)line[i]-48;
			}
			else
			{
				day=day*10+(int)line[i]-48;
			}
		}
		if(line[i]=='-')
			which++;
	}
	switch(month)
	{
		case 1:strcpy(mon,"Jan");
			break;
		case 2:strcpy(mon,"Feb");
			break;
		case 3:strcpy(mon,"Mar");
			break;
		case 4:strcpy(mon,"Apr");
			break;
		case 5:strcpy(mon,"May");
			break;
		case 6:strcpy(mon,"Jun");
			break;
		case 7:strcpy(mon,"Jul");
			break;
		case 8:strcpy(mon,"Aug");
			break;
		case 9:strcpy(mon,"Sep");
			break;
		case 10:strcpy(mon,"Oct");
			break;
		case 11:strcpy(mon,"Nov");
			break;
		case 12:strcpy(mon,"Dec");
			break;
	}
	printf("%d %s %d, %d:%d:%d\n",day,mon,year,hour,min,preSec);
	fclose(file);
	while(keeprunning)
	{
		signal(SIGINT,signal_handler);
		signal(SIGTSTP,signal_handler);
		which=0;
		FILE* file=fopen("/proc/driver/rtc","r");
		fgets(line,sizeof(line),file);
		hour=min=sec=day=month=year=0;
		for(int i=0;i<strlen(line);i++)
		{
			if(isdigit(line[i]))
			{
				if(which==1)
				{
					hour=hour*10+(int)line[i]-48;
				}
				else if(which==2)
				{
					min=min*10+(int)line[i]-48;
				}
				else
				{
					sec=sec*10+(int)line[i]-48;
				}
			}
			if(line[i]==':')
				which++;
		}
		if(sec!=preSec)
		{
			preSec=sec;
			lim--;
			hour=(hour+5+((min+30)/60))%24;
			min=(min+30)%60;
			if(lim==0)
			{
				fgets(line,sizeof(line),file);
				which=0;
				for(int i=0;i<strlen(line);i++)
				{
					if(isdigit(line[i]))
					{
						if(which==0)
						{
							year=year*10+(int)line[i]-48;
						}
						else if(which==1)
						{
							month=month*10+(int)line[i]-48;
						}
						else
						{
							day=day*10+(int)line[i]-48;
						}
					}
					if(line[i]=='-')
						which++;
				}
				switch(month)
				{
					case 1:strcpy(mon,"Jan");
							break;
					case 2:strcpy(mon,"Feb");
							break;
					case 3:strcpy(mon,"Mar");
							break;
					case 4:strcpy(mon,"Apr");
							break;
					case 5:strcpy(mon,"May");
							break;
					case 6:strcpy(mon,"Jun");
							break;
					case 7:strcpy(mon,"Jul");
							break;
					case 8:strcpy(mon,"Aug");
							break;
					case 9:strcpy(mon,"Sep");
							break;
					case 10:strcpy(mon,"Oct");
							break;
					case 11:strcpy(mon,"Nov");
							break;
					case 12:strcpy(mon,"Dec");
							break;
				}
				printf("%d %s %d, %d:%d:%d\n",day,mon,year,hour,min,sec);
				lim=atoi(brokenCommand[2]);
				//break;
			}
		}
		fclose(file);
	}
	printf("\n");
	return 1;
}