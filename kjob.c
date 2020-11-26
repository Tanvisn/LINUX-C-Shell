#include "headers.h"

int kjob(char* str)
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

	long long job_num,sig_num;

	//Error handling
	if(args!=3)
	{
		printf("ERROR: Incorrect number of arguments\n");
		return 1;
	}

	else
	{
		token = strtok(str," ");
		token = strtok(NULL," ");

		//while(token!=NULL)
		{
			job_num = atoi(token);
			//printf("%lld\n",job_num);
			token = strtok(NULL," ");
			
			sig_num = atoi(token);
			//printf("%lld\n",sig_num);
			token = strtok(NULL," ");
		}

		if(job_num <= job_idx && job_num>0)
		{
			//Send given signal to given job number

			int res = kill(job_number[job_num],sig_num);
			if(res == 0)
			{
				//If process is to be killed, remove from job storage
				if(sig_num==9)
				{
					for(i=job_num;i<job_idx;i++)
					{
						job_number[i] = job_number[i+1];
						strcpy(jname[i].name,jname[i+1].name);
						job_idx--;
					}

				}
				
				return 0;
			}

			else
			{
				perror("ERROR:");
			}
			
		}

		else
		{
			printf("ERROR: No such process\n");
			return 1;
		}
	}

	
}