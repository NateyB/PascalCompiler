#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include "processor.h"
/*

RELOP       (<(=|>)?)|=|>=?
ASSIGNOP    :=
IDRES       {letter}({letter}|{digit})*
WS          {whitespace}+
LONGREAL    {digit}+\.{digit}+\E(\+|\-)?{digit}+
REAL        {digit}+\.{digit}+
INT         {digit}+
UNREC       [^\n \t]

*/

// Begin machine listings
int relop(Token* storage, char* str, int start)
{
    storage -> category = RELOP;
    char next = str[start];
    switch (next) {
        case '<':
            start++;
            if (str[start] == '=')
            {
                storage -> type = 1;
                start++;
            } else if (str[start] == '>')
            {
                storage -> type = 5;
                start++;
            } else {
                storage -> type = 0;
            }
            break;

        case '=':
            start++;
            storage -> type = 2;
            break;

        case '>':
            start++;
            if (str[start] == '=')
            {
                storage -> type = 4;
                start++;
            } else {
                storage -> type = 3;
            }
            break;

        default: break; // Do not increment; continue on to the next machine.
    }

    return start;
}




// The processing
typedef int (*machine)(Token*, char*, int);
const static machine machines[] = {&relop};

bool initialized = false;
int length = 0;
char* buffer = 0;
int start;

Token* getNextToken()
{
    if (initialized) {
        if (start == length - 1)
        {
            printf("%s\n", "EOF reached.");
            free(buffer);
            return NULL;
        }
        Token* current = malloc(sizeof(*current));
        int end;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
            end = (*machines[i])(current, buffer, start);
            if (end > start) {
                start = end;
                return current;
            }
        }
        current -> category = UNREC;
        current -> type = buffer[start];
        start++;
        return current;
    } else {
        fprintf(stderr, "%s\n", "Processor not initialized. Aborting.");
        return NULL;
    }
}

int initializeTokens(FILE* sourceFile)
{
    if (sourceFile) {
        // Get a file's size
        fseek(sourceFile, 0, SEEK_END);
        long size = ftell(sourceFile);
        fseek(sourceFile, 0, SEEK_SET);

        buffer = (char*) malloc((size + 1)*sizeof(char));
        if (buffer)
        {
            fread(buffer, 1, size + 1, sourceFile);
            buffer[size] = 0;
            length = size;
            initialized = true;
            start = 0;
            return 0;
        } else {
            fprintf(stderr, "%s\n", "Memory for buffer not allocated properly!");
        }
    } else {
        fprintf(stderr, "%s\n", "Source file for analyzer null!");
    }
    return 1;
}
