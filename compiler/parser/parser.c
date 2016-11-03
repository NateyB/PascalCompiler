#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include "../tokenizer/tokens.h"
#include "productions/productions.h"

/* Unlike the lexical analyzer, which opens the file stream manually and
 * tokenizes it, I wanted the controlling file to push tokens to the
 * recipient, which matches accordingly. Consequently, I'm going to use
 * "goto" statements to emulate Lua coroutines.
 *
 * Because goto obfuscates flow, and for pedagogical purposes, the following
 * is an outline of the control flow:
 * 1) The parser is initialized, and told that its first production is "program"
 * 2) The program production takes a handle, and then instructs the match
 *    function to get one of a series of next tokens.
 * 3) a) The program production is called, and it calls the match function
 *    with its various handles.
 * 3) b) If match does not succeed, then requireSync is called to throw an
 *       error and continue to the next production.
 */

static Token* newestToken;
static production matchProduction;

void requireSync(Token** syncSet)
{
    fprintf(stderr, "%s\n", "Oopsies.");
    // Throw error
    // Skip tokens until one from the sync set is found
    // Continue on to the next production
}

void tokenArrived(Token*);

void pushToParser(Token* rep)
{
    tokenArrived(rep);
    waitForToken: ;
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the type
// of the token, or just the category.
bool match(int cat, int type, bool strict)
{
    goto waitForToken;
    tokenIsHere:;
    if (strict) { // This means that we don't care about the value here
        if (newestToken -> category == cat && newestToken -> type == type)
            return true;
        else
            return false;
    } else {
        if (newestToken -> category == cat)
            return true;
        else
            return false;
    }
}


void tokenArrived(Token* token)
{
    newestToken = token;
    if (matchProduction != NULL)
    {
        matchProduction(token);
        matchProduction = NULL;
    } else {
        goto tokenIsHere;
    }
}

void programProduction(Token* handle)
{
    Token* endOfFile = malloc(sizeof(*endOfFile));
    endOfFile -> category = FILEEND;
    endOfFile -> type = 0;
    Token* syncSet[] = {endOfFile};
    if (handle -> category == CONTROL && handle -> type == 7) // "program"
    {
        if (match(CONTROL, 3, true)) // Successfully matched "end"!
            return;
        else // Uh-oh; a syntax error
            requireSync(syncSet);
    } else { // A syntax error
        requireSync(syncSet);
    }
}

void initParser()
{
    matchProduction = programProduction;
}
