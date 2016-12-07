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
void statement_list()
{
    // Production 13.1
    if (curTok -> attribute == CONTROL && curTok -> aspect == 0 // begin
        || curTok -> attribute == CONTROL && curTok -> aspect == 10 // call
        || curTok -> attribute == ID // ID
        || curTok -> attribute == CONTROL && curTok -> aspect == 5 // if
        || curTok -> attribute == CONTROL && curTok -> aspect == 9) // while
    {
        statement();
        statement_list_tail();
        return;
    }

    synch();
}
