#include "headers.h"

int unsettingenv(char* var)
{
	//Unsetting the environment variable var
	int res = unsetenv(var);

	if(res==-1)
	{
		printf("ERROR:Failed to unset the environment variable\n");
		return 0;
	}

	else
	{
		return 1;	
	}

}