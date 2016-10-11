#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "tokenizer.h"
#include "../dataStructures/linkedList/linkedlist.h"
#include "machines/machines.h"
#include "../errorHandler/errorHandler.h"
#include "../globals.h"

const machine machines[] = {whitespace, idres, longRealMachine,
        realMachine, intMachine, grouping, catchall, relop, addop, mulop};

// Initialization stuff
static bool initialized = false;
static int start;

int initializeTokens(FILE* resFile)
{
    if (resFile) {
        initResWords(resFile);
    } else {
        fprintf(stderr, "%s\n", "Reserved words file for tokenizer null!");
    }
    return 1;
}

static Token* generateNextToken()
{
    if (initialized) {
        Token* current = malloc(sizeof(*current));
        if ((current = getNextErrorToken()))
            return current;

        int end;
        current -> start = start;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
            current -> type = 0;
            end = (*machines[i])(current, BUFFER, start);
            if (end > start) {
                current -> length = end - start;
                start = end;
                return current;
            }
        }

        // Unrecognized symbol error. This error is manual because it takes
        // the place of a lexeme, rather than being processed during one.
        throwError(LEXERR, 0, start, 1);
        current -> category = NOOP;
        start++;
        return current;
    } else {
        fprintf(stderr, "%s\n", "Processor not initialized. Aborting.");
        return NULL;
    }
}


Token* getNextToken()
{
    Token* next;
    do {
        next = generateNextToken();
    } while (next -> category == NOOP);

    return next;
}
