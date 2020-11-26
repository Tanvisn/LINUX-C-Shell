#include "echo.h"
#include "headers.h"

int echo(char* cont,int k)
{
	int fd;

	//Output redirection
	if(strcmp(file_out,"stdout")!=0)
	{
		//If output file is to be overwritten
		if(k==0)
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}

		//If text is to be appended to output file 
		else
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}

	else
	{
		fd = 1;
	}

	//Input redirection
	if(strcmp(file_in,"stdin")!=0)
	{
		int fd_in = open(file_in, O_RDONLY);
		if(fd_in==-1)
		{
			printf("No such file or directory\n");
			return 0;	
		}

	}

	//writing the string token wise to output file
	//Not including the redirection symbols and input output files
	char * token = strtok(cont," ");
	token = strtok(NULL," ");

	while(token!=NULL)
	{
		
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

		if(token!=NULL && strcmp(token,"\n")==0)
		{
			write(fd,"\n",1);
		}

		else if(token!=NULL)
		{
			write(fd,token,strlen(token));
			write(fd," ",1);
		}

		token = strtok(NULL," ");
	}

	write(fd,"\n",1);

	//printf("out of echo token loop\n");

	return 1;
}