/*Author: Benjamin Brandtner
 * A Read-Evaluate-Print Loop in C
 * Right now the fundamental structure is working, it can read in one command and up to 9 parameters, and make a call to echo, which prints out the first parameter passed to it. */

#define cmdIs(x) (strcmp(command,x)==0)

#include "standardheaders.h"
#include "preprocessorOptions.c"
#include "commands.h"

enum actions {CONT, QUIT};

//Global Variables
const bool DEBUG=false;
char promptText[30]="user@machine ";

//Functions
void getInput (char **input)
{
	*input=readline(promptText);
	add_history(*input);
}

void parseInput (char *input, char **command, char *parameters[])
{
	int i;
	
	*command = strtok(input, " \n");

	//TODO: Don't split something that's inside quotation marks
	parameters[0]=strtok(NULL, " \n");
	i=1;
	while(parameters[i-1]!=NULL)
	{
		parameters[i]=strtok(NULL, " \n");
		i++;
	}
}

enum actions decide (char *command, char *parameters[])
{
	if(command==NULL) //No Input
	{
		//No action
		//has to be tested because strcmp with NULL is a segfault
	}
	else if(cmdIs("echo"))
	{
		echo(parameters);
	}
	else if(cmdIs("prompt"))
	{
		prompt(parameters);
	}
	else if(cmdIs("quit"))
	{
		return QUIT;
	}
	else
	{
		printf("Unknown command: %s\n", command);
	}

	return CONT;
}

int main (void)
{
	char *input;
	char *command;
	char *parameters[10]; 
	enum actions action=CONT;

	while(action != QUIT)
	{
		puts("Bernds Bombastische Konsole Version 0.0.2\n\n");

		getInput(&input);
		parseInput(input, &command, parameters);

		if(DEBUG)
		{
			printf("\e[1;30m\nDebug Infos:\n");
			printf("Command: %s\n", command);
			printf("Parameter %i: %s\n", 0, parameters[0]);
			int i = 1;
			while(parameters[i-1]!=NULL)
			{
				printf("Parameter %i: %s\n", i, parameters[i]);
				i++;
			}
			printf("\n\e[0m");
		}

		action = decide(command, parameters);
		
		free(input);
	}

	printf("\nBye!\n\n");

	return 0;
}

