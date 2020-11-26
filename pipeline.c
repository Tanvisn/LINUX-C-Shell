#include "headers.h"

int x;

int pipeline(char* cont)
{
	char power[100100] = "";
	
	int len = strlen(cont);
	int i = len-1,j,kk,count,inn,outt;

	inn = dup(STDIN_FILENO);
	outt = dup(STDOUT_FILENO);

	char** argv = malloc(256 * sizeof(char *));
	char* token = strtok(cont," ");

	while( token != NULL ) {

		strcat(power,token);
		strcat(power," ");
		token = strtok(NULL," ");

	}


	kk=0;

	//Storing respective pipe commands in argv
	token = strtok(power, "|");
	count = 0;

	while(token!=NULL)
	{
		if(count==0)
			argv[kk] = token;
		else
			argv[kk] = token+1;
		count++;
		//printf("%s\n",argv[kk]);
		kk++;
		token = strtok(NULL,"|");
	}

	/*printf("1st command %s\n", argv[0]);
	printf("2nd command %s\n", argv[1]);*/

	int mypipe[2],fd,pread,pwrite,cread,cwrite,stat;
	pid_t pid;

	argv[kk] = NULL;

	last_pipe=0;

	for(int t=0;t<count;t++)
	{
		//printf("t = %d\n",t);
		pipe(mypipe);

		pid = fork();

		if(pid < 0)
		{
			perror("fork failed: ");
			return 1;
		}

		//Child process
		if(pid==0)
		{	
			//For second child onwards set the input as read fd
			if(t>0)
				dup2(x,STDIN_FILENO);

			//For all except last child, set output as write fd
			if(t < (count-1))
				dup2(mypipe[1],STDOUT_FILENO);

			close(mypipe[0]);

			close(mypipe[1]);

			//Setting flag for last command in pipe
			if(t==(count-1))
			{
				last_pipe=1;
			}
			
			//Calling function for executing command
			commands(argv[t]);

			exit(2);
		}

		//Parent
		else
		{
			//Wait till child executes
			waitpid(pid,&stat,0);
			
			//Close writing end of pipe as parent will read
			close(mypipe[1]);

			x = mypipe[0];

		}
	}

	return 0;
	
}

