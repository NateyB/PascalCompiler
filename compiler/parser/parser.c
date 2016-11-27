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
    } while (next -> category == WS || next -> category == NOOP
             || next -> category >= LEXERR);
    return next;
}

void requireSync(const Token* syncSet[], int size)
{
    while (true) {
        for (int i = 0; i < size; i++)
        {
            const Token* syncToken = syncSet[i];
            if (curTok -> category == syncToken -> category
                 && (curTok -> type == syncToken -> type
                 || !syncToken -> start))
             {
                 return;
             }
        }
        curTok = getNextRelevantToken();
    }
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the type
// of the token, or just the category.
bool match(int cat, int type, bool strict)
{
    // if (strict)
    // {
    //     printf("Exp: %d\t%d\n", cat, type);
    //     printf("Rec: %d\t%d\n\n", curTok -> category, curTok -> type);
    // } else {
    //     printf("Exp: %d\t\n", cat);
    //     printf("Rec: %d\t\n\n", curTok -> category);
    // }

    if (cat == FILEEND && curTok -> category == FILEEND)
        return true;
    else if (curTok -> category == cat && (!strict || curTok -> type == type))
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
