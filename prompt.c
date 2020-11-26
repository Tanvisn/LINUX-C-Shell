#include "headers.h"

void prompt_col () {
  printf("\033[1;36m");
}

void col_reset () {
  printf("\033[0m");
}



int prompt()
{
	char hostbuffer[256]; 
	int i,hostname; 
	
	/*Display contains the final prompt string*/
	char display[100005] = "";
	
	display[0] = '<';
	
	/*getlogin() returns a pointer to a string containing 
	the name of the user logged in on the controlling 
	terminal of the process, or a NULL pointer if this 
	information cannot be determined*/
	char* p = getlogin();

	if(p==NULL) 
		return 1;
	
	char ch = '@';
	strcat(display,p);
	strncat(display,&ch,1);

	/*Getting the host name*/
	hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
	if (hostname == -1) 
	{ 
		perror("gethostname"); 
		exit(1); 
	} 

	strcat(display,hostbuffer);
	
	ch = ':';
	strncat(display,&ch,1);

	char* path = "~";
	strcat(display,path);

	//home is directory from where shell is invoked
	int len = strlen(home);
	char path1[100] = "";
	char path2[100]="";

	//Path of current working directory
	getcwd(path1,100);
        
	int len1 = strlen(path1);

	/*Extracting the path with respect to
	directory from where shell is invoked*/
	for(i=len ; i<len1 ; i++)
	{
		path2[i-len] = path1[i];
	}

	path2[len1] = '\0';
        
	strcat(display,path2);

	ch = '>';
	strncat(display,&ch,1);

	//Adding color to the prompt
	prompt_col();
	printf("%s",display);
	col_reset();

	return 0;
}

