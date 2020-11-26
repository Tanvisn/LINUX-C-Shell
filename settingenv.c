#include "headers.h"

int settingenv(char* var, char* value)
{
	//Setting the environment variable
	//as overwrite is nonzero, if var does not exist
	//its value is set as value
	int res = setenv(var,value,1);

	if(res==-1)
	{
		printf("ERROR:Failed to set the environment variable\n");
		return 0;
	}

	else
	{
		return 1;	
	}

}