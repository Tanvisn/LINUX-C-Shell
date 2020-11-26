#include "headers.h"

int bg(char* str)
{
	char temp[1005]="";
	int args=0,i,j;

	//printf("string passed %s\n",str);
	strcat(temp,str);

	//Counting number of arguments
	char* token = strtok(temp," ");
	while(token!=NULL)
	{
		printf("%s\n",token);
		args++;
		token = strtok(NULL," ");
	}

	long long job_num;

	//Error handling with respect to number of arguments
	if(args!=2)
	{
		printf("ERROR: Incorrect number of arguments\n");
		return 1;
	}

	else
	{
		token = strtok(str," ");
		token = strtok(NULL," ");

		{
			job_num = atoi(token);
			printf("%lld\n",job_num);
			token = strtok(NULL," ");
		}

		if(job_num <= job_idx && job_num>0)
		{
			//If its a valid job number send SIGCONT signal to it
			int res = kill(job_number[job_num],SIGCONT);

			if(res == 0)
			{	
				return 0;
			}

			else
			{
				perror("ERROR:");
				return 1;
			}
			
		}

		else
		{
			printf("ERROR: No such process\n");
			return 1;
		}
	}

	
}
