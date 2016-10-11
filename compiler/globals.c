#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "globals.h"

char* BUFFER;

void initializeGlobals()
{
    BUFFER = malloc(sizeof(char*)*73);
}

void updateLine(char* line)
{
    LINE++;
    strcpy(BUFFER, line);
}
