#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "globals.h"

char* BUFFER;
int LINE = 0;
int START = 0;

int initializeGlobals()
{
    BUFFER = malloc(sizeof(char*)*73);
    return (BUFFER != NULL);
}

void updateLine(char* line)
{
    START = 0;
    LINE++;
    strcpy(BUFFER, line);
}
