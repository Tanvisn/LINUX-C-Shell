#include "headers.h"
char buffer2[100100];

int status,input,output,inn,outt;

int foreground(char* cont,int k)
{
	//printf("This is a foreground process\n");
	pid_t pid;

	//printf("command passed to foreground is %s\n",cont);

	int len = strlen(cont);
	int i = len-1,j,kk;

	//Combining all the character pointers
	//for parsing the input arguments to execvp
	char** argv = malloc(256 * sizeof(char *));
	char* token = strtok(cont," ");

	kk=0;

	while( token != NULL ) 
	{

		//Not considering redirection symbols and output file names
		if(token!=NULL && strcmp(token,">")==0)
		{
			token = strtok(NULL," ");
			if(token!=NULL)
			{
				token = strtok(NULL," ");
			}

			continue;
		}

		if(token!=NULL && strcmp(token,">>")==0)
		{
			token = strtok(NULL," ");
			if(token!=NULL)
			{
				token = strtok(NULL," ");
			}

			continue;
		}


		if(token!=NULL && strcmp(token,"<")==0)
		{
			token = strtok(NULL," ");
			if(token!=NULL)
			{
				token = strtok(NULL," ");
			}

			continue;
		}

		argv[kk] = token;
		kk++;
		token = strtok(NULL," ");

	}

	
	inn = dup(STDIN_FILENO);
	outt = dup(STDOUT_FILENO);

	//If both input and output files are same and we are overwriting
	if(strcmp(file_in,file_out)==0 && k==0)
	{
		//printf("INSIDE THE RIGHT LOOP!\n");
		//Name of the temporary file used as buffer
		char temp[1005] = "sameFileHandling.txt";

		//Input redirection
		if(strcmp(file_in,"stdin")!=0)
		{
			int input = open(file_in, O_RDONLY);
			if(input==-1)
			{
				printf("No such file or directory\n");
				return 0;	
			}

			
			if(dup2(input,0) < 0)
			{
				perror("ERROR:");
				return 1;
			}
		}

		
		else
		{
			if(dup2(inn,0) < 0)
			{
				perror("ERROR:");
				return 1;
			}
		}

		//For output redirection
		if(strcmp(temp,"stdout")!=0)
		{
			//Overwriting the output file
			if(k==0)
			{
				output = open (temp, O_CREAT | O_RDWR | O_TRUNC, 0644);
			}

			else
			{
				output = open (temp, O_CREAT | O_RDWR | O_APPEND, 0644);
			}

			if(dup2(output,1) < 0)
			{
				perror("ERROR:");
				return 1;
			}
		}

		else
		{
			if(dup2(outt,1)<0)
			{
				perror("ERROR:");
				return 1;
			}	
		}

		close(input);
		close(output);

		pid = fork();
		//Foreground process name and pid
		if(pid>0)
		{
			curforid = pid;
			strcpy(curforname,argv[0]);

		}
		
		if(pid < 0)
		{
			perror("fork failed: ");
		}
		else if(pid==0)
		{

			if(execvp(argv[0],argv) < 0)
			{
				perror("Error");
			}
		}

		//For parent process
		else
		{
			//The parent waits till the
			//child process with pid is being executed
			waitpid(pid,&status,0);

			dup2(inn,0);
			dup2(outt,1);

		}

		output = open(temp, O_CREAT | O_RDWR, 0644);
		int outputt = open(file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if(outputt > 0)
		{
			printf("OPENED SUCCESSFULLY!\n");
		}

		int len1=0;
		while((len1 = read(output,buffer2,100100))>0)
		{
			write(outputt,buffer2,strlen(buffer2));
		}

		close(output);
		close(outputt);

		remove(temp);
	}
	
	//When input and output files are different
	else
	{
		//Input redirection	
		if(strcmp(file_in,"stdin")!=0)
		{
			int input = open(file_in, O_RDONLY, 0644);
			
			if(input==-1)
			{
				printf("No such file or directory\n");
				return 0;	
			}

			if(dup2(input,0) < 0)
			{
				perror("ERROR:");
				return 1;
			}
			
		}

		else
		{
			if(dup2(inn,0) < 0)
			{
				perror("ERROR:");
				return 1;
			}
		}

		//Output redirection
		if(strcmp(file_out,"stdout")!=0)
		{
			if(k==0)
			{
				output = open (file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
				
			}

			else
			{
				output = open (file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
				
			}

			if(dup2(output,1) < 0)
			{
				perror("ERROR:");
				return 1;
			}

		}

		else
		{
			if(dup2(outt,1) < 0)
			{
				perror("ERROR:");
				return 1;
			}
		}


		//Creating child process
		pid = fork();
		//Foreground process name and pid
		if(pid>0)
		{
			curforid = pid;
			strcpy(curforname,argv[0]);

		}
		
		//Error handling
		if(pid < 0)
		{
			perror("fork failed: ");
		}

		//For child processes
		else if(pid==0)
		{

			//Assigning a process to the child process	

			if(execvp(argv[0],argv) < 0)
			{
				perror("Error");
			}

		}

		//For parent process
		else
		{
			//The parent waits till the
			//child process with pid is being executed
			waitpid(pid,&status,0);

			dup2(inn,0);
			dup2(outt,1);

		}
	}

	return 0;

}