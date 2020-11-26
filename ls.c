#include "headers.h"

/*Function for printing appropriate information
according to the flags*/

void list(int flag_a, int flag_l,int k)
{
	int fd;

	if(strcmp(file_out,"stdout")!=0)
	{
		if(k==0)
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}

		else
		{
			fd = open (file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}

	else
	{
		fd = 1;
	}

	
	//If both -a and -l are provided
	if(flag_l && flag_a)
	{
		/*Struct storing details of user account*/
		struct passwd *pw;
		struct group *gp;
		/*Directory pointer*/
		DIR *mydir;
		char *c;
		int i;
		/*Struct storing details of directory*/
		struct dirent *myfile;

		/*Struct storing details of file*/
		struct stat fileStat;

		/*Opening the current directory*/
		mydir=opendir(".");

		/*Properties stored in filestat structure*/
		stat(".",&fileStat);

		/*Reading the contents of directory*/ 
		while((myfile=readdir(mydir))!=NULL)
		{
			/*Checking the permissions of files in a directory 
			one by one*/
			stat(myfile->d_name,&fileStat);
			if(S_ISDIR(fileStat.st_mode))
			{
				write(fd,"d",1);
			}
			else
			{
				write(fd,"-",1);
			}

			if(fileStat.st_mode & S_IRUSR)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWUSR)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXUSR)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}


			if(fileStat.st_mode & S_IRGRP)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWGRP)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXGRP)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}


			if(fileStat.st_mode & S_IROTH)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWOTH)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXOTH)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}

			write(fd," ",1);
			/*Number of links to the file*/
			//printf("%ld \n",fileStat.st_nlink);
			char link[105];
			sprintf(link,"%ld",fileStat.st_nlink);
			write(fd,link,strlen(link));
			write(fd," ",1);
			/*User id of file owner*/
			pw=getpwuid(fileStat.st_uid);
			/*Printing user name*/
			//printf("%s ",pw->pw_name);
			write(fd,pw->pw_name,strlen(pw->pw_name));
			write(fd," ",1);
			/*Group id of group owner*/
			gp=getgrgid(fileStat.st_gid);
			/*Printing user name*/
			//printf("%s ",gp->gr_name);
			write(fd,gp->gr_name,strlen(gp->gr_name));
			write(fd," ",1);
			/*File size in bytes*/
			//printf("%4ld ",fileStat.st_size);
			char ssize[105];
			sprintf(ssize,"%4ld",fileStat.st_size);
			write(fd,ssize,strlen(ssize));
			
			write(fd," ",1);
			/*Time of last data modification*/
			c=ctime(&fileStat.st_mtime);
			for(i=4;i<=15;i++)
			{
				//printf("%c",c[i]);
				char let[5];
				sprintf(let,"%d",c[i]);
				write(fd,let,1);
			}
			//printf(" ");
			write(fd," ",1);
			/*Name of directory*/
			//printf("%s\n",myfile->d_name);
			write(fd,myfile->d_name,strlen(myfile->d_name));
			write(fd,"\n",1);
		}

		closedir(mydir);
	}

	//If only -l flag is inputted
	else if(flag_l && !flag_a)
	{
		struct passwd *pw;
		struct group *gp;
		char temp_name[505]="";
		DIR *mydir;
		char *c;
		int i;
		struct dirent *myfile;
		struct stat fileStat;
		mydir=opendir(".");
		stat(".",&fileStat);
		while((myfile=readdir(mydir))!=NULL)
		{
			//Details for '.' and '..' not displayed
			strcpy(temp_name,myfile->d_name);
			/*if(!strcmp(temp_name[0],"."))
				continue;*/
			if(temp_name[0]=='.')
				continue;
			if(!strcmp(myfile->d_name,".."))
				continue;
			stat(myfile->d_name,&fileStat);
			if(S_ISDIR(fileStat.st_mode))
			{
				write(fd,"d",1);
			}
			else
			{
				write(fd,"-",1);
			}

			if(fileStat.st_mode & S_IRUSR)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWUSR)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXUSR)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}


			if(fileStat.st_mode & S_IRGRP)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWGRP)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXGRP)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}


			if(fileStat.st_mode & S_IROTH)
			{
				write(fd,"r",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IWOTH)
			{
				write(fd,"w",1);
			}
			else
			{
				write(fd,"-",1);
			}
			if(fileStat.st_mode & S_IXOTH)
			{
				write(fd,"x",1);
			}
			else
			{
				write(fd,"-",1);
			}

			write(fd," ",1);
			/*Number of links to the file*/
			//printf("%ld \n",fileStat.st_nlink);
			char link[105];
			sprintf(link,"%ld",fileStat.st_nlink);
			write(fd,link,strlen(link));
			write(fd," ",1);
			/*User id of file owner*/
			pw=getpwuid(fileStat.st_uid);
			/*Printing user name*/
			//printf("%s ",pw->pw_name);
			write(fd,pw->pw_name,strlen(pw->pw_name));
			write(fd," ",1);
			/*Group id of group owner*/
			gp=getgrgid(fileStat.st_gid);
			/*Printing user name*/
			//printf("%s ",gp->gr_name);
			write(fd,gp->gr_name,strlen(gp->gr_name));
			write(fd," ",1);
			/*File size in bytes*/
			//printf("%4ld ",fileStat.st_size);
			char ssize[105];
			sprintf(ssize,"%4ld",fileStat.st_size);
			write(fd,ssize,strlen(ssize));
			write(fd," ",1);
			/*Time of last data modification*/
			c=ctime(&fileStat.st_mtime);
			for(i=4;i<=15;i++)
			{
				//printf("%c",c[i]);
				char let[5];
				sprintf(let,"%d",c[i]);
				write(fd,let,1);
			}
			//printf(" ");
			write(fd," ",1);
			/*Name of directory*/
			//printf("%s\n",myfile->d_name);
			write(fd,myfile->d_name,strlen(myfile->d_name));
			write(fd,"\n",1);
		}

		closedir(mydir);
	}

	/*If only -a flag is inputted*/
	else if(!flag_l && flag_a)
	{
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				//printf("%s\n", dir->d_name);
				write(fd,dir->d_name,strlen(dir->d_name));
				write(fd,"\n",1);
			}
			closedir(d);
		}
	}

	/*Only ls command is inputted*/
	else
	{
		DIR *d;
		struct dirent *dir;
		char temp_name2[505]="";
		d = opendir(".");
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				strcpy(temp_name2,dir->d_name);
				/*if(!strcmp(temp_name2[0],"."))
					continue;*/
				if(temp_name2[0]=='.')
					continue;
				if(!strcmp(dir->d_name,"."))
				{
					continue;
				}

				if(!strcmp(dir->d_name,".."))
				{
					continue;
				}

				//printf("%s\n", dir->d_name);
				write(fd,dir->d_name,strlen(dir->d_name));
				write(fd,"\n",1);
			}

			closedir(d);

		}
	}
}

int ls(char cont[],int k)
{
	if(strcmp(file_in,"stdin")!=0)
	{
		int fd_in = open(file_in, O_RDONLY);
		if(fd_in==-1)
		{
			printf("No such file or directory\n");
			return 0;	
		}

	}

	int len = strlen(cont);
	int flag_a=0,flag_l=0,err_flag=0;

	/*For checking which flags are inputted*/
	for(int i=0 ; i<len-1 ; i++)
	{
		if(cont[i]=='-')
		{
			int init = i;
			int l=0;

			/*Counting number of characters when a '-' is encountered*/
			while(cont[i]!=' ' && i<len)
			{
				l++;
				i++;
			}

			/*If number of characters is 3 including the '-'
			checking if it is -la or -al*/
			if(l==3)
			{
				if((cont[i-1]=='l' || cont[i-1]=='a') && (cont[i-2]=='l' || cont[i-2]=='a'))
				{
					flag_a = 1;
					flag_l = 1;
				}

				//Invalid flag input
				else
				{
					err_flag = 1;
				}

			}

			else
			{
				/*If input is -a flag*/
				if(cont[i-1]=='a')
				{
					flag_a = 1;
				}

				/*If input is -l flag*/
				else if(cont[i-1]=='l')
				{
					flag_l = 1;
				}

				/*Invalid flag input*/
				else
				{
					err_flag = 1;
				}

			}

			/*Change the currently obtained flag to spaces*/
			if(i!=len)
			{
				while(i>=init)
				{
					cont[i] = ' ';
					i--;
				}
			}

			/*If i=len we have reached the end of the string*/
			else
			{
				cont[init] = '\0';
			}
		}
	}

	/*After the completion of above loop, cont[]
	will contain ls and all the inputted directory
	names*/

	/*Invalid flag inputted*/
	if(err_flag)
	{
		printf("ls: invalid flag\n");
		return 0;
	}

	/*Length of argument array*/
	len = strlen(cont);
	char temp[len];
	int count = 0;
	/*Copying argument array in temp array*/
	strcpy(temp,cont);

	/*Calling strtok with space as delimeter*/
	char* token = strtok(temp," ");

	/*Counting total number of tokens*/
	while(token!=NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}

	/*No directory name was inputted*/
	if(count == 1 || count==3 || count==5)
	{
		list(flag_a, flag_l,k);
	}

	/*If some directory name(s) inputted*/
	else
	{
		/*The first token is ls, it is excluded*/
		token = strtok(cont, " ");
		token = strtok(NULL, " ");
		count--;

		/*If only one directory name inputted*/
		if(count == 1)
		{
			while(count-- && token!=NULL)
			{
				if(token!=NULL && strcmp(token,">")==0)
				{
					token = strtok(NULL," ");
					if(token!=NULL)
					{
						token = strtok(NULL," ");
					}
				}

				if(token!=NULL && strcmp(token,">>")==0)
				{
					token = strtok(NULL," ");
					if(token!=NULL)
					{
						token = strtok(NULL," ");
					}

				}


				if(token!=NULL && strcmp(token,"<")==0)
				{
					token = strtok(NULL," ");
					if(token!=NULL)
					{
						token = strtok(NULL," ");
					}

				}

				/*token1 contains the path
				of directory whose containts
				need to be displayed*/
				char token1[1005]="";

				/*If directory inputted is ~*/
				if(token[0]=='~')
				{
					/*concatinating with home directory of shell*/
					strcpy(token1,home);
					strcat(token1,token+1);
					int len1 = strlen(token1);
				}

				/*Directly put the directory name in token1*/
				else
				{
					strcat(token1,token);
				}

				/*x contains current working directory*/
				char x[100];
				getcwd(x,100);

				/*Entering into given directory*/
				int c=cd(token1);

				/*cd function returns zero for
				unsuccessful execution*/
				if(!c)
				{
					continue;
				}

				/*Calling the function displaying information*/
				list(flag_a,flag_l,k);

				/*coming back to current working directory*/
				cd(x);
				token = strtok(NULL, " ");
			}
		}

		/*More than one directory names are inputted*/
		else
		{
			while(count-- && token!=NULL)
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

				/*token1 contains the path
				of directory whose containts
				need to be displayed*/
				char token1[1005] = "";

				/*If directory inputted is ~*/
				if(token[0]=='~')
				{
					/*concatinating with home directory of shell*/
					strcpy(token1,home);
					strcat(token1,token+1);
					int len1 = strlen(token1);
				}

				/*Directly put the directory name in token1*/
				else
				{
					strcat(token1,token);
				}

				/*Printing directory name whose contents
				are displayed*/
				printf("%s:\n",token1);
				
				/*x contains current working directory*/
				char x[1005];
				getcwd(x,1005);

				/*Entering into given directory*/
				int c = cd(token1);

				/*cd function returns zero for
				unsuccessful execution*/
				if(!c)
				{
					continue;
				}

				/*Calling the function displaying information*/
				list(flag_a,flag_l,k);

				/*coming back to current working directory*/
				cd(x);
				printf("\n");

				token = strtok(NULL, " ");
			}
		}
	}

	return 0;
}