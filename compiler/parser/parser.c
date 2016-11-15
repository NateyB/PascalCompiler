#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include "../tokenizer/tokens.h"
#include "productions/productions.h"
#include "../tokenizer/tokenizer.h"
#include "../handler/handler.h"

Token* queuedToken = NULL;

Token* getNextRelevantToken()
{
    if (queuedToken != NULL)
        return queuedToken;
    Token* next = malloc(sizeof(*next));
    do {
        next = getNextToken();
        if (!handleToken(next))
            return NULL;
    } while (next -> category == WS || next -> category == NOOP
             || next -> category >= LEXERR);
    return next;
}

void requireSync(const Token* syncSet[], int size)
{
    Token* next = malloc(sizeof(*next));
    do {
        next = getNextRelevantToken();
        if (next == NULL) // EOF
            return;
        for (int i = 0; i < size; i++)
        {
            const Token* syncToken = syncSet[i];
            if (next -> category == syncToken -> category
                 && (next -> type == syncToken -> type
                 || !next -> start))
             {
                 printf("%d\n", next -> category);
                 return;
             }
        }
    } while (true);
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the type
// of the token, or just the category.
bool match(int cat, int type, bool strict)
{
    Token* next = getNextRelevantToken();
    if (next -> category == cat && (next -> type == type || !strict))
    {
        queuedToken = NULL;
        return true;
    }
    return false;
}

int generateParseTree()
{
    Token* first = getNextToken();
    handleToken(first);
    program(first);

    return 0;
}
