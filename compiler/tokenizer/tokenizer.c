#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "tokenizer.h"
#include "../dataStructures/linkedList/linkedlist.h"
#include "machines/machines.h"
#include "../errorHandler/errorHandler.h"
#include "../globals/globals.h"

const machine machines[] = {whitespace, idres, longRealMachine,
        realMachine, intMachine, grouping, catchall, relop, addop, mulop};

// Initialization stuff
static bool initialized = false;

int initializeTokens(FILE* resFile)
{
    if (resFile) {
        initIDResMachine(resFile);
        initialized = true;
    } else {
        fprintf(stderr, "%s\n", "Reserved words file for tokenizer null!");
    }
    return 1;
}

static Token* generateNextToken()
{
    if (initialized) {
        Token* current = malloc(sizeof(*current)); // TODO necessary allocation?
        if ((current = getNextErrorToken()) != NULL)
            return current;
        else
             current = malloc(sizeof(*current));

        int end;
        current -> start = START;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
            current -> aspect = 0;
            end = (*machines[i])(current, BUFFER, START);
            if (end > START) {
                current -> length = end - START;
                START = end;
                return current;
            }
        }

        // Unrecognized symbol error. This error is manual because it takes
        // the place of a lexeme, rather than being processed during one.
        throw_lex_error(LEXERR, 0, START, 1);
        //current -> attribute = NOOP;
        START++;
        return current;
    } else {
        fprintf(stderr, "%s\n", "Tokenizer not initialized. Aborting.");
        return NULL;
    }
}


Token* getNextToken()
{
    Token* next = malloc(sizeof(*next));
    do {
        next = generateNextToken();
    } while (next -> attribute == NOOP);

    return next;
}
