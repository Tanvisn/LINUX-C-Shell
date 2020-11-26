#include "headers.h"

int commands(char* input)
{	
	int bufsize = 0,flag_nw,arg_pinfo;
	int len = 0,i=0,flag_ls=0,flag_back=0,flag_comm=0,hist,flag_in=0,flag_out=0,flag_echo=0,flag_cd=0,flag_pipe=0;

	flag_replace = 0;
	
	{
		i=0;
		char input1[1005] = "";

		//Copying the original input string in another string
		strcpy(input1,input);
		input1[len-1]='\0'; 
		

		//Calling strtok with delimeter as space
		char* token = strtok(input, " ");
		
		int j=0;
		
		//Processing the input string tokenwise
		if(token != NULL) 
		{ 
			
			{
				//Exit if quit is pressed
				if(strcmp(token,"quit")==0)
				{
					exit(0);
				}

				//If command is cd
				if(strcmp(token,"cd")==0)
				{
					int ff=0;
					char** argv = malloc(5 * sizeof(char *));
					token = strtok(NULL, " ");

					in_out(token);

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

						ff=1;
						argv[0] = token;
						token = strtok(NULL," ");

					}

					//Pass the argument input for cd command to function 
					if(ff)
					{
						cd(argv[0],flag_replace);
					}

					else if(token==NULL || strlen(token)==0)
					{
						char* token1 = "~";
						cd(token1,flag_replace);
					}

					flag_comm = 1;
					flag_cd = 1;
				}

				//If command is echo
				else if(strcmp(token,"echo")==0)
				{

					token = strtok(NULL, " "); 

					in_out(token);

					flag_echo = 1;
					flag_comm = 1;

				}

				//If command is pwd
				else if(strcmp(token,"pwd")==0)
				{
					token = strtok(NULL, " "); 

					in_out(token);

					pwd(flag_replace);
					flag_comm = 1;
				}

				//If command is ls
				else if(strcmp(token,"ls")==0)
				{
					token = strtok(NULL, " "); 

					in_out(token);

					flag_ls = 1;
					flag_comm = 1;

				}

				//If command is pinfo
				else if(strcmp(token,"pinfo")==0)
				{
					int ff=0;
					char** argv = malloc(5 * sizeof(char *));
					token = strtok(NULL, " ");

					in_out(token);

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

						ff=1;
						argv[0] = token;
						token = strtok(NULL," ");

					}


					//If information of process with given pid is to be printed
					if(ff)
					{
						arg_pinfo = 2;
						pinfo(argv[0],arg_pinfo,flag_replace);
					}  

					//If information of current process is to be printed
					else
					{
						arg_pinfo = 1;
						pinfo("pid",arg_pinfo,flag_replace);
					}

					flag_comm = 1;

				}

				else if(strcmp(token,"history")==0)
				{
					token = strtok(NULL," ");
					if(token!=NULL)
					{
						int num = atoi(token);
						if(num < (hist))
						{
							history_num(num);
						}

						else
						{
							printf("The requested number exceeds size of history\n");
							printf("Printing present commands in history:\n");
							history_num(hist);
						}

					}

					else
					{
						if((hist) < 11)
						{
							history_num(hist);
						}

						else
						{
							history_num(10);
						}

					}

					flag_comm = 1;				
				}

				//Setting environment variables
				else if(strcmp(token,"setenv")==0)
				{
					char* varname;
					char* set_value;

					token = strtok(NULL," ");

					//Setting inputs for setenv and error handling					
					if(token!=NULL)
					{
						varname = token;	
					}

					else
					{
						printf("ERROR:Insufficient number of arguments\n");
						return 1;
					}
					
					token = strtok(NULL," ");

					if(token!=NULL)
					{
						set_value = token;
					}

					else
					{
						set_value = "";
					}

					token = strtok(NULL," ");

					if(token==NULL)
					{
						settingenv(varname,set_value);
					}

					else
					{
						printf("ERROR:Number of arguments exceeds 2\n");
						return 1;
					}
					
					flag_comm = 1;
				}

				//Unsetting environment variables
				else if(strcmp(token,"unsetenv")==0)
				{
					char* varname;

					token = strtok(NULL," ");
					
					//Setting inputs for unsetenv and error handling	
					if(token!=NULL)
					{
						varname = token;	
					}

					else
					{
						printf("ERROR:Insufficient number of arguments\n");
						return 1;
					}
					
					token = strtok(NULL," ");

					if(token!=NULL)
					{
						printf("ERROR:Number of arguments exceeds 1\n");
						return 1;
					}

					else
					{
						unsettingenv(varname);
					}
					
					flag_comm = 1;
				}

				else if(strcmp(token,"jobs")==0)
				{
					jobs();
					flag_comm = 1;
				}

				else if(strcmp(token,"kjob")==0)
				{
					kjob(input1);
					flag_comm = 1;
				}

				else if(strcmp(token,"overkill")==0)
				{
					overkill();
					flag_comm = 1;
				}

				else if(strcmp(token,"bg")==0)
				{
					bg(input1);
					flag_comm = 1;
				}

				else if(strcmp(token,"fg")==0)
				{
					fg(input1);
					flag_comm = 1;
				}

			}

			//Passing the whole input string to ls function
			if(flag_ls)
			{
				ls(input1,flag_replace);
			}

			if(flag_echo)
			{
				echo(input1,flag_replace);
			}

			else if(flag_comm==0)
			{
				//printf("Calling foreground ");

				if(flag_pipe)
				{
					if(last_pipe)
					{
						in_out(token);
						//printf("in = %s and out = %s\n",file_in,file_out);
					}

					else
					{
						token = strtok(NULL, "|"); 
						in_out(token);	
					}
					
				}

				else
				{
					token = strtok(NULL, " "); 
					in_out(token);
				}

				//printf("for %s\n",input1);
				foreground(input1,flag_replace);

			}
		}

		//Exit on pressing ctrl+d
		else if(feof(stdin))
		{
			printf("\n");
			exit(0);
		}

	}

	return 0;
}
