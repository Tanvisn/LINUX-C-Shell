#include "headers.h"
#define BUFSIZE 100100

char buffer2[100100];

int history(char cont[],int k)//By default adding the command to history
{
	if(cont[0] == '\n')//handling edge case of no input
	{
		return 0;
	}
	int res = open(his_path,O_CREAT | O_RDWR, 0644);//stored file for history
	if(res < 0)
	{
		printf("Unable to open history\n");//error handling for file issues
		return 0;
	}

	char* tok = strtok(cont," ");//tokenizing the input
	int length;
	char temp1[1005] = "";

	int len1=0;
	int len = 0;

	if((length = read(res,buffer2,BUFSIZE)) > 0)//reading the file so that the command isnt repeated
        {
		len = strlen(buffer2);
		for(int i=len-1 ; i>=0 ; i--)
		{
			if(buffer2[i]=='\n')
				break;
			len1++;
		}
	}

	while(tok!=NULL)//tokenizing and storing input
	{
		strcat(temp1,tok);
		strcat(temp1," ");
		tok = strtok(NULL," ");
	}

	int len2 = strlen(temp1);
	int flag = 0;

	if(len2==len1)//handling repeated commands
	{
		int j=len1-1;
		for(int i=len-1 ; i>=0 , j>=0; i--,j--)
		{
			if(buffer2[i]!=temp1[j])
			{
				flag = 1;
				break;
			}
		}
	}
	else
	{
		flag = 1;
	}
	
	lseek(res,0,SEEK_END);//entering at the end of the file to avoid rewriting
	if(flag)//present command not matched with previous command
	{
		write(res,"\n",1);
		write(res,temp1,strlen(temp1));
		len1=0;
		lseek(res,0,SEEK_SET);
		if((length = read(res,buffer2,BUFSIZE)) > 0)
        {
                len = strlen(buffer2);
                for(int i=len-1 ; i>=0 ; i--)
                {
                        if(buffer2[i]=='\n')
                                break;
                        len1++;
                }
        }
		if(k==20)//limiting commands to 20
		{
			char* xyz = buffer2;
			//for(int i=0 ; i<len ; i++)
			//{
			remove(his_path);//deleting file to change its contents
			xyz++;
			len--;
			while(*xyz!='\n')
			{
				len--;
				xyz++;
			}
			res = open(his_path,O_CREAT | O_RDWR | O_TRUNC, 0644);//restoring the file with changed contents
			write(res,xyz,len);
			close(res);
		}
		return 1;
	}
	else
	{
		close(res);
		return 0;
	}
}

int history_num(int k)//triggered when the input if of type history
{
	int res = open(his_path,O_CREAT | O_RDWR, 0644);
	
	if(res < 0)//handling file related errors
	{
		printf("Unable to open history\n");
		return 0;
	}

	int length,count=0,i=0;

	if((length = read(res,buffer2,BUFSIZE)) > 0)//reading file
	{
		int len = sizeof(buffer2);
		for(i=len-1 ; i>=0 ; i--)//writing the commands in reverse order
		{
			if(count<k)
			{
				int in = i;
				int length = 0;
				while(buffer2[in]!='\n')
				{
					length++;
					in--;
				}
				in++;
				while(in<=i)
				{
					printf("%c",buffer2[in]);
					in++;
				}
				printf("\n");
				i-=length;
				i--;
			}

			count++;//making sure it doesnt exceed the given count
		}
	}

	close(res);
}