#include "headers.h"

int jobs()
{
	int i=0,j=0;
	
	//For all the jobs in the background
	for(j=1;j<=job_idx;j++)
	{
		char proc[1005]="",read[1005]="",display_stat[15]="",temp[1005]="";
		
		//creating the string /proc/[pid]/stat for each job number
		strcat(proc,"/proc/");
		sprintf(temp,"%d",job_number[j]);
		strcat(proc,temp);
		strcat(proc,"/stat");


		//Error handling
		int fd_check = open(proc,O_RDONLY);

		if(fd_check < 0)
		{
			printf("No such process exists\n");
		}

		else
		{
			//Creating a file pointer.
			//"r" stands for read only file
			FILE* fd;
			fd = fopen(proc,"r");

			int count=0;
			char temp1[1005]="",status;

			if(fgets(read, 1005, fd)) 
			{
				int len = strlen(read);

				for(i=0;i<len;i++)
				{

					//The 3rd field in the file contains
					//status of process
					if(count==2)
					{
						status = read[i];
						//printf("status is %c\n",status);
						break;
					}

					if(read[i] == ' ')
					{
						count++;
					}
				}
			}

			fclose(fd);

			//Setting the display status according to obtained status 
			if(status=='T')
			{
				strcat(display_stat,"Stopped");
			}

			else
			{
				strcat(display_stat,"Running");
			}

			printf("[%d] %s %s [%d]\n",j,display_stat,jname[j].name,job_number[j]);
		}
	}
}