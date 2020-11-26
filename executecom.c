#include "headers.h"

int executecom(int num, char* cont)
{
	char power[100100] = "";
	

	int len = strlen(cont);
	int i = len-1,j,kk,count,inn,outt,flag_back=0,len1;

	char** argv = malloc(256 * sizeof(char *));
	
	//Storing in power by removing unnecessary spaces
	char* token = strtok(cont," ");

	while( token != NULL ) {

		strcat(power,token);
		strcat(power," ");
		token = strtok(NULL," ");

	}

	//printf("%s\n",power);

	kk=0;

	//If more than 1 commands to be executed for single input
	if(num > 1)
	{
		token = strtok(power, ";");
		count = 0;

		//Tokenizing with respect to semicolon and storing each command distinctly
		while(token!=NULL)
		{
			argv[kk] = token;
			count++;
			kk++;
			token = strtok(NULL,";");
		}

		for(int t=0;t<count;t++)
		{
			//printf("executing %s\n", argv[t]);
			
			char input1[1005] = "";
			char input2[1005] = "";

			strcpy(input1,argv[t]);
			len1 = strlen(argv[t]);
			//input1[len1-1]='\0'; 

			strcpy(input2,argv[t]);
			//input2[len1-1]='\0'; 

			flag_pipe=0;
			flag_back=0;

			//Checking for pipes
			for(int l=0;l<(len1-1);l++)
			{
				if(input1[l]=='|')
				{
					flag_pipe = 1;
					break;
				}
			}

			if(flag_pipe==1)
			{
				//printf("Calling pipe\n");
				//strcat(input1," ");
				char* token1 = strtok(input2,"|");
				//printf("%s passed to in_out before pipe\n",token1);
				in_out(token1);
				//printf("input to pipe %s\n",input1);
				pipeline(input1);
			}

			else
			{
				//Checking for background process
				for(int a=0;a<len1;a++)
				{
					if(input1[a]=='&')
					{
						flag_back = 1;
						break;
					}
				}

				if(flag_back==1)
				{
					//printf("Calling background process\n");
					background(input1);
				}

				else
				{
					commands(argv[t]);	
				}
				
			}

			
		}	
	}

	//For single command
	else
	{
		//printf("executing %s\n",power);

		char input1[1005] = "";
		char input2[1005] = "";
		char input3[1005] = "";

		strcpy(input1,power);
		len1 = strlen(power);
		//input1[len1-1]='\0'; 

		strcpy(input2,power);
		//input2[len1-1]='\0';

		strcpy(input3,power);
		//input3[len1-1]='\0';

		char* token3 = strtok(input3,";");
		//printf("one comm %s\n",input3);

		flag_pipe=0;
		flag_back=0;

		for(int t=0;t<(len1-1);t++)
		{
			if(input1[t]=='|')
			{
				flag_pipe = 1;
				break;
			}
		}

		if(flag_pipe==1)
		{
			char* token1 = strtok(input2,"|");
			in_out(token1);
			pipeline(input1);
			return 0;
		}

		else
		{
			for(int t=0;t<len1;t++)
			{
				if(input1[t]=='&')
				{
					flag_back = 1;
					break;
				}
			}

			if(flag_back==1)
			{
				background(input1);
				return 0;
			}

			else
			{
				if(token3!=NULL)
					commands(token3);
				else
				{
					//Exit for ctrl+d
					if(feof(stdin))
					{
						printf("\n");
						exit(0);
					}

					return 1;
				}
			}

		}

		

	}

	return 0;
}