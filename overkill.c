#include "headers.h"

int overkill()
{
	//printf("currently %d jobs are running\n",job_idx);
	for(int i=1;i<=job_idx;i++)
	{
		//printf("kill job %s with number %d\n",jname[i].name,job_number[i]);
		int res = kill(job_number[i],9);
		
		if(res==-1)
		{
			perror("ERROR:");
		}

	}

	//set the job index to 0
	job_idx = 0;

	return 0;
}