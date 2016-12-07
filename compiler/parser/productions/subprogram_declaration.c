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
void subprogram_declaration()
{
    // Production 7
    if (curTok -> category == CONTROL && curTok -> type == 6) // procedure
    {
        subprogram_head();
        declarations();
        subprogram_declarations();
        compound_statement();
        return;
    }

    synch();
}
