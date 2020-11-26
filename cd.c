#include "headers.h"

//home is the directory from where shell is invoked

int cd(char* dir,int k)
{
	if(strcmp(dir,"-")!=0)
	{
		strcpy(cd_args[cd_idx].name,dir);
		cd_idx++;
	}
/*
	for(int k=0;k<cd_idx;k++)
	{
		printf("%d. %s\n",k+1,cd_args[k].name);
	}
*/
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

	if(strcmp(dir,"-")==0)
	{
		//printf("idx = %d\n",cd_idx);

		if(cd_idx>=1)
		{
			//printf("try open %s\n",cd_args[cd_idx-2].name);

			strcpy(dir,cd_args[cd_idx-2].name);

			strcpy(cd_args[cd_idx].name,cd_args[cd_idx-2].name);
			cd_idx++;

		}

		else
			return 0;
	}


	//If input is cd ~
	if(strcmp(dir,"~")==0)
	{
		/*Till the directory from where shell is 
		invoked is not reached, keep coming one level up */
		while(1)
		{
			char s[1005]="";
			getcwd(s, 1005);

			if(strcmp(s,home)==0)
			{
				break;
			}

			chdir("..");
		}

		return 1;
	}

	else
	{
		char s[100] = "";

		//If cd .. is entered and shell is in its home directory
		if(!(strcmp(getcwd(s,100),home) || (strcmp(dir,".."))))
		{
			//Print the shell's parent directory
			chdir("..");
			printf("%s\n",getcwd(s,100));
			chdir(home);
			return 1;
		}

		//Entering into the directory with given name
		int x = chdir(dir);
		//If some error occurs
		if(x<0)
		{
			printf("No such file or directory\n");
			return 0;
		}

		//Successful execution
		else if(x==0)
		{
			return 1;
		}
	}
}