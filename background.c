/*#include "headers.h"

char temp2[1005]="";

/*void signalHandler(int signal)
{
	pid_t pid;
	int stat=0;

	//On success returns process id of terminated child
	pid = wait(&stat);


	//Checking if a status is returned
	if (WIFEXITED(stat)) 
	{
	 	//Calculating the exit status
		const int es = WEXITSTATUS(stat);
        //If exit status is 0
		if(es==0)
		{
			fprintf(stderr,"\n%s with pid %d exited normally\n",temp2,pid);
		}

		else
		{
			fprintf(stderr,"\n%s with pid %d exited abnormally\n",temp2,pid);
		}
	}

	prompt();
	fflush(stdout);
	
	wait(NULL);
	
	return;
}

int background(char* cont)
{
	pid_t pid,pid_child;

	int len = strlen(cont);
	int i = len-1,j,k;

	while(cont[i]!='&') 
	{
		cont[i] = ' ';
		i--;
	}

	cont[i] = '\0';

	printf("calling background for %s\n",cont);

	//Combining all the character pointers
	//for parsing the input arguments to execvp
	char** argv = malloc(256 * sizeof(char *));

	char* token = strtok(cont," ");
	
	k=0;
	while( token != NULL ) 
	{
		argv[k] = token;
		k++;
		token = strtok(NULL," ");
	}

	//Storing name of background command to be executed
	strcpy(temp2,argv[0]);

	int status;
	//Creating child process
	pid = fork();

	printf("fork done\n");

	//Setting the group id
	setpgid(0,0);

	printf("group id set\n");

	if(pid < 0)
	{
		perror("fork failed: ");
	}

	//For child process
	else if(pid==0)
	{
		printf("Child process\n");
		pid_child = getpid();
		//Assigning a process to the child process
		printf("lets do execvp for %s\n",argv[0]);	
		int res = execvp(argv[0],argv);
		if(res < 0)
		{
			perror("Error");
		}
	}

	//For parent process
	else
	{
		printf("Parent process\n");
		//Catching the signal for child termination
		//signal(SIGCHLD,signalHandler);
		job_idx++;
		job_number[job_idx] = pid;
		strcat(job_name[job_idx],temp2); 

	}

	printf("I am done!!!\n");

	return 0;

}

*/

#include "headers.h"

char temp2[1005]="";


void signalHandler(int signal)
{
	pid_t pid;
	int stat=0;

	/*On success returns process id of terminated child*/
	pid = wait(&stat);


	/*Checking if a status is returned*/
	if (WIFEXITED(stat)) 
	{
	 	/*Calculating the exit status*/
		const int es = WEXITSTATUS(stat);
        //If exit status is 0
		if(es==0)
		{
			fprintf(stderr,"\n%s with pid %d exited normally\n",temp2,pid);
		}

		else
		{
			fprintf(stderr,"\n%s with pid %d exited abnormally\n",temp2,pid);
		}
	}

	prompt();
	fflush(stdout);
	
	wait(NULL);
	
	return;
}

int background(char* cont)
{
	pid_t pid,pid_child;

	int len = strlen(cont);
	int i = len-1,j,k;

	//Removing the spaces after &
	while(cont[i]!='&') 
	{
		cont[i] = ' ';
		i--;
	}

	cont[i] = '\0';

	//Creating pointer array for passing to execvp
	char** argv = malloc(256 * sizeof(char *));

	char* token = strtok(cont," ");
	
	k=0;
	while( token != NULL ) {
		argv[k] = token;
		k++;
		token = strtok(NULL," ");
	}

	strcpy(temp2,argv[0]);

	//Creating child
	int status;
	pid = fork();
	setpgid(0,0);

	if(pid < 0)
	{
		perror("fork failed: ");
	}

	//Child process
	else if(pid==0)
	{
		pid_child = getpid();
		//execute inputted command
		int res = execvp(argv[0],argv);
		if(res < 0)
		{
			perror("Error");
		}
	}

	else
	{
		//signal(SIGCHLD,signalHandler);
		//Storing the name and pid of current background process
		job_idx++;
		job_number[job_idx] = pid;
		//printf("job number is %d\n",job_number[job_idx]);
		strcpy(jname[job_idx].name,temp2);
		
		//printf("name is %s\n",jname[job_idx].name);

	}

	return 0;

}
