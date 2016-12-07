#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* syncSet[] = {&endOfFile};
static const int sync_size = sizeof(syncSet)/sizeof(syncSet[0]);

static void synch()
{
    requireSync(syncSet, sync_size);
}

// Needs implementing: None
void subprogram_declarations()
{
    // Production 6.1
    if (curTok -> attribute == CONTROL && curTok -> aspect == 6) // procedure
    {
        subprogram_declaration();
        if (match(PUNC, 1, true)) { // ;
            subprogram_declarations();
            return;
        }

    // Production 6.2
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 0) // begin
        return; // Epsilon

    synch();
}
