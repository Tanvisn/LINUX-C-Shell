#include "headers.h"

int fg(char* str)
{
	char temp[1005]="";
	int args=0,i,j,status;

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
		//Getting the inputted job number
		token = strtok(str," ");
		token = strtok(NULL," ");

		{
			job_num = atoi(token);
			//printf("%lld\n",job_num);
			token = strtok(NULL," ");
		}

		if(job_num <= job_idx && job_num>0)
		{
			int pid = job_number[job_num];

			for(i=job_num;i<job_idx;i++)
			{
				job_number[i] = job_number[i+1];
				strcpy(jname[i].name,jname[i+1].name);
				job_idx--;
			}

			//The process can then change from the background group to the foreground process group by making a call to tcsetpgrp 
			//and specifying the PGID of the new foreground group as one of the arguments passed to tcsetpgrp.
			//After the PGID for a terminal has been changed, reads by the process group that was associated with the terminal prior 
			//to the call to tcsetpgrp either fail or cause the generation of a SIGTTIN signal. A SITTIN signal causes the process group to stop. 
			//Depending upon the setting of the TOSTOP bit in the termios structure, writes may also cause the process group 
			//to stop due to the generation of a SIGTTOU signal.
			
			//Ignore the SIGTTIN and SIGTTOU signals
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);


			tcsetpgrp(STDIN_FILENO, pid);

			//For running the process
			kill(pid,SIGCONT);

			//Waiting till the process finishes
			waitpid(pid,&status,0);

			tcsetpgrp(STDIN_FILENO, getpgrp());

			//Setting signal's behaviour to default
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);

			return 0;
		}

		else
		{
			printf("ERROR: No such process\n");
			return 1;
		}
	}
}