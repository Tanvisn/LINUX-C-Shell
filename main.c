#include "headers.h"

char home[100];
char buffer[100005];
char his_path[1005];
char file_in[1005];
char file_out[1005];
int job_number[100005];
int job_idx=0;
int myshellid;
int curforid;
char curforname[105];
int flag_pipe = 0;
int flag_replace = 0;
int last_pipe=0;
int cd_idx=0;

#define BUFSIZE 100100

void ctrl_c(int sig)
{
	//If its not shell	
	if(curforid!=-1)
		kill(curforid,SIGINT);
	
	//For shell being current foreground process
	if(curforid==-1)
	{
		//printf("curforid -1!!!\n");
		printf("\n");
		prompt();
		fflush(stdout);
		return;
	}

	//signal(SIGINT,ctrl_c);
}


int read_hist()
{
	int res = open(his_path,O_CREAT | O_RDWR, 0644);
	
	if(res < 0)
	{
		printf("Unable to open history\n");
		return 0;
	}

	int length,count=0,i=0;

	if((length = read(res,buffer,BUFSIZE)) > 0)
	{
		int len = strlen(buffer);
		for(i=0;i<len;i++)
		{
			if(buffer[i]=='\n')
				count++;
		}
	}

	return count;
}

void ctrl_z(int sig)
{
	//printf("In ctrl+z signal handler\n");
	
	pid_t p = getpid();

	//printf("myshell pid = %d and curforid = %d and p = %d\n",myshellid,curforid,p);

	if(curforid!=-1)
	{
		kill(curforid,SIGTSTP);

		job_idx++;
		job_number[job_idx] = curforid;
		strcpy(jname[job_idx].name,curforname);
		prompt();
		fflush(stdout);
		return;
	}


	if(curforid==-1)
	{
		//printf("curforid -1!!!\n");
		printf("\n");
		prompt();
		fflush(stdout);
		return;
	}

}

int main()
{
	//Directory from where shell is invoked
	getcwd(home,100);

	strcpy(his_path,home);
	strcat(his_path,"/history.txt");

	strcpy(cd_args[cd_idx].name,"~");
	cd_idx++;
	
	int bufsize = 0,flag_nw;
	int len = 0,i=0,flag_ls=0,flag_back=0,flag_comm=0,hist,flag_in=0,flag_out=0,flag_echo=0,flag_cd=0,flag_mult=0;

	signal(SIGINT, ctrl_c);
	signal(SIGTSTP, ctrl_z);

	myshellid = getpid();
	
	while (1)
	{
		
		//Initialising input and output files to null, that is default input is stdin and default output is stdout
		file_in[0] = '\0';
		file_out[0] = '\0';	
		//Other initialisations and declarations
		char input[1005] = "";
		char input1[1005] = "";
		char input2[1005] = "";
		char input3[1005] = "";
		char input4[1005] = "";
		int arg_pinfo;
		flag_ls=0;
		flag_in=0;
		flag_echo=0;
		flag_out=0;
		flag_back=0;
		flag_nw=0;
		flag_comm = 0;
		flag_replace=0;
		flag_cd=0;
		flag_pipe=0;
		flag_mult=0;
		curforid = -1;

		i=0;
		prompt();
		hist = read_hist();
        //Taking the input
		fgets(input, 1005, stdin);
		
		//Storing length of input
		len = strlen(input);
		input[len-1]='\0'; 
		
		//Converting all tabs to spaces
		for(i=0;i<len;i++)
		{
			if(input[i]=='\t')
			{
				input[i] = ' ';
			}
		}

		strcpy(input4,input);
		input4[len-1]='\0';

		strcpy(input3,input);
		input3[len-1]='\0';

		strcpy(input2,input);
		input2[len-1]='\0';

		//int hist1 = hist;
		history(input2,hist);
		hist = read_hist();

		int com_count = 1,count_colon=0;

		//Counting number of commands to be executed for single input
		for(i=0;i<len;i++)
		{
			if(input3[i]==';')
			{
				/*flag_mult=1;
				break;*/
				com_count++;
			}
		}

		

		//printf("com_count = %d\n",com_count);
		//Calling function for executing commands
		executecom(com_count,input4);

	}

	return 0;
}
