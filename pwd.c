#include "headers.h"
//Printing presently working directory with respect to home directory 
int pwd(int k)
{
	int fd;

	//Output redirection
	if(strcmp(file_out,"stdout")!=0)
	{
		//If '<' is inputted, rewrite
		if(k==0)
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}

		//Else we need to append the text
		else
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}

	else
	{
		fd = 1;
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

	char s[1005] = "";
	getcwd(s,1005);
	//Writing the output to stdout or redirected output according to fd
	write(fd,s,strlen(s));
	write(fd,"\n",1);

	return 1;
}