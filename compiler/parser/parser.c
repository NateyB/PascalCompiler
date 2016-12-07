#include<stdlib.h>
#include<stdbool.h>

#include "../tokenizer/tokens.h"
#include "productions/productions.h"
#include "../tokenizer/tokenizer.h"
#include "../handler/handler.h"
#include "../errorHandler/errorHandler.h"

Token* curTok = NULL;
static Token EOFToken = {
    FILEEND, false, 0, 0
};


Token* getNextRelevantToken()
{
    Token* next = malloc(sizeof(*next));
    do {
        next = getNextToken();
        if (!handleToken(next))
            return &EOFToken;
    } while (next -> attribute == WS || next -> attribute == NOOP
             || next -> attribute >= LEXERR);
    return next;
}

void requireSync(const Token* syncSet[], int size)
{
    while (true) {
        for (int i = 0; i < size; i++)
        {
            const Token* syncToken = syncSet[i];
            if (curTok -> attribute == syncToken -> attribute
                 && (curTok -> aspect == syncToken -> aspect
                 || !syncToken -> start))
             {
                 return;
             }
        }
        curTok = getNextRelevantToken();
    }
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the aspect
// of the token, or just the attribute.
bool match(int cat, int aspect, bool strict)
{
    if (cat == FILEEND && curTok -> attribute == FILEEND)
        return true;
    else if (curTok -> attribute == cat && (!strict || curTok -> aspect == aspect))
    {
        curTok = getNextRelevantToken();
        return true;
    }
    else
    {
        throwError(SYNERR, 0, 0, 0);
        curTok = getNextRelevantToken();
        return false;
    }
}

int generateParseTree()
{
    curTok = malloc(sizeof(*curTok));
    curTok = getNextRelevantToken();
    program();
    return match(FILEEND, 0, false);
}
