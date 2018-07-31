#include "standardheaders.h"

extern const bool DEBUG;
extern char promptText[30];

void echo (char *par[])
{
	//TODO: case for no parameters (maybe interactive input?)
	//interpret more parameters:
	//color, format, text parameter on different position
	
	if(par[0]==NULL)
	{
		char temp[100];
		char *pTemp;
		fgets(temp, 99, stdin);
		pTemp=strtok(temp, "\n");
		printf("%s\n", pTemp);
	}
	else
	{
		printf("%s\n", par[0]); 
	}
}

void prompt (char *par[])
{
	if(par[0]==NULL)
	{
		printf("Usage: prompt \"New prompt message\"\n");
	}
	else
	{
		strcpy(promptText, par[0]);
	}
}
