#include "headers.h"

//Function for setting input and output of a command
int in_out(char* token)
{
	int flag_in=0;
	int flag_out=0;

	flag_replace=0;

	while(token!=NULL)
	{
		//If output redirection is given
		if(flag_out == 1)
		{
			//Set the output file accordingly
			int len1 = strlen(token);
			for(int ii=0;ii<len1;ii++)
			{
				file_out[ii] = token[0];
				token++;
			}

			token = token - len1;
			file_out[len1] = '\0';

			flag_out = 0;
		}

		//If input redirection is given
		if(flag_in == 1)
		{
			//Set the input file accordingly
			int len1 = strlen(token);
			for(int ii=0;ii<len1;ii++)
			{
				file_in[ii] = token[0];
				token++;
			}

			token = token - len1;
			file_in[len1] = '\0';
			flag_in = 0;
		}

		//Checking if any redirection symbols are provided
		//and setting the flags accordingly
		if(strcmp(token,">>")==0)
		{
			flag_replace = 1;
			flag_out = 1;
		}

		if(strcmp(token,">")==0)
		{
			flag_out = 1;
		}

		if(strcmp(token,"<")==0)
		{
			flag_in = 1;
		}

		token = strtok(NULL, " "); 
	}

	//If no input or output redirections given, 
	//set stdout as output and stdin as input
	if(file_out[0]=='\0')
	{
		char stdoutt[] = "stdout";
		strcat(file_out,stdoutt);
	}

	if(file_in[0]=='\0')
	{
		char stdinn[] = "stdin";
		strcat(file_in,stdinn);
	}

	//printf("file_in = %s and file_out = %s\n",file_in,file_out);

	return 0;
}
