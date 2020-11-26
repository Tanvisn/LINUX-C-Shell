#include "headers.h"

int pinfo(char cont[],int arg,int k)
{
	printf("Its my pinfo\n");
	char proc[1005] = "",exec_path[1005] = "", status,temp[1005] = "",read[1005] = "",num_pid[15]="";

	pid_t pid;

	int fd_out;

	//Output redirection
	if(strcmp(file_out,"stdout")!=0)
	{
		//If '<' is inputted, rewrite
		if(k==0)
		{
			fd_out = open (file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}

		//Else we need to append the text
		else
		{
			fd_out = open (file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}

	else
	{
		fd_out = 1;
	}

	if(strcmp(file_in,"stdin")!=0)
	{
		int fd_in = open(file_in, O_RDONLY);
		if(fd_in==-1)
		{
			printf("No such file or directory\n");
			return 0;	
		}

	}

	/*Only pinfo is passed as argument*/
	if(arg==1)
	{
		/*Getting process id of currently
		running process*/
		pid = getpid();
		/*concatinating the strings to
		form the file name /proc/[pid]/stat
		and /proc/[pid]/exe*/
		sprintf(temp,"%d",pid);
		strcat(proc,"/proc/");
		strcat(exec_path,"/proc/");
		strcat(proc,temp);
		strcat(exec_path,temp);
		strcat(proc,"/stat");
		strcat(exec_path,"/exe");
	}

	/*A process pid is given*/
	else
	{
		/*concatinating the strings to
		form the file name /proc/[pid]/stat
		and /proc/[pid]/exe*/
		strcat(proc,"/proc/");
		strcat(exec_path,"/proc/");
		strcat(proc,cont);
		strcat(exec_path,cont);
		strcat(proc,"/stat");
		strcat(exec_path,"/exe");
	}

	/*Error handling if process with
	given pid does not exist*/
	int fd_check = open(proc,O_RDONLY);

	if(fd_check < 0)
	{
		printf("No such process exists\n");
	}

	else
	{
		/*printing the pid*/
		if(arg==1)
		{
			//printf("pid -- %d\n",pid);
			write(fd_out,"pid -- ",7);
			sprintf(num_pid,"%d",pid);
			write(fd_out,num_pid,strlen(num_pid));
			write(fd_out,"\n",1);
		}

		else
		{
			//printf("pid -- %s\n",cont);
			write(fd_out,"pid -- ",7);
			write(fd_out,cont,strlen(cont));
			write(fd_out,"\n",1);
		}

		/*Creating a file pointer.
		"r" stands for read only file*/
		FILE* fd;
		fd = fopen(proc,"r");

		int i=0,count=0;
		char temp1[1005]="";

		if(fgets(read, 1005, fd)) 
		{
			int len = strlen(read);

			for(i=0;i<len;i++)
			{

				/*The 3rd field in the file contains
				status of process*/
				if(count==2)
				{
					//printf("Process status -- %c\n",read[i]);
					write(fd_out,"Process status -- ",18);
					char temp_stat[2]="";
					temp_stat[0] = read[i];
					write(fd_out,temp_stat,1);
					write(fd_out,"\n",1);
					i++;
				}

				/*The 23rd field in the file contains
				virtual memory size in bytes*/
				if(count==22)
				{
					/*As string is traversed characterwise,
					the characters between 22nd and 23rd space
					are stored together in a string*/

					int j=0;
					while(read[i]!=' ')
					{
						temp1[j] = read[i];
						i++;
						j++;
					}

					temp1[j] = '\0';

					//printf("memory -- %s\n",temp1);
					write(fd_out,"memory -- ",10);
					write(fd_out,temp1,strlen(temp1));
					write(fd_out,"\n",1);
					//count++;
				}

				if(read[i] == ' ')
				{
					count++;
				}
			}
		}

		fclose(fd);
		/*returns number of bytes placed in buffer*/
		int x = readlink(exec_path, read, 1005);
		read[x] = '\0';

		char path[] = "~",display[1005]="";
		strcat(display,path);
		int len2 = strlen(home);
		char path2[1005]="";
		int len1 = strlen(read);
		/*Replacing the path of directory
		from where shell is invoked by ~*/
		for(i=len2 ; i<len1 ; i++)
		{
			path2[i-len2] = read[i];
		}
		
		path2[len1] = '\0';
		strcat(display,path2);
		//printf("Executable Path -- %s\n",display);
		write(fd_out,"Executable path -- ",19);
		write(fd_out,display,strlen(display));
		write(fd_out,"\n",1);

	}

	
}