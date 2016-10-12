#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "globals.h"

char* BUFFER;
int LINE = 0;
int START = 0;

void initializeGlobals()
{
    BUFFER = malloc(sizeof(char*)*73);
}

void updateLine(char* line)
{
    START = 0;
    LINE++;
    strcpy(BUFFER, line);
}
