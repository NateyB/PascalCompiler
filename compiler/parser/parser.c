#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include "../tokenizer/tokens.h"
#include "productions/productions.h"
#include "../tokenizer/tokenizer.h"
#include "../handler/handler.h"

void requireSync(Token** syncSet, int size)
{
    printf("Unfortunately, a sync is required.\n");
    // Throw error
    // Skip tokens until one from the sync set is found
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the type
// of the token, or just the category.
bool match(int cat, int type, bool strict)
{
    Token* next;
    do {
        next = getNextToken();
        if (!handleToken(next))
            return false;
    } while (next -> category == WS || next -> category == NOOP
             || next -> category >= LEXERR);

    return (next -> category == cat && (next -> type == type || !strict));
}

int generateParseTree()
{
    Token* first = getNextToken();
    handleToken(first);
    programProduction(first);

    return 0;
}
