#include "standardheaders.h"

extern const bool DEBUG;

void echo (char *par[])
{
	//TODO: case for no parameters (maybe interactive input?)
	//interpret more parameters:
	//color, format, text parameter on different position
	printf("%s\n", par[0]);
}
