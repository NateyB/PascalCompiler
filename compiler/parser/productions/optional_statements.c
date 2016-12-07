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
void optional_statements()
{
    // Production 12.1
    if (curTok -> attribute == CONTROL && curTok -> aspect == 0 // begin
        || curTok -> attribute == CONTROL && curTok -> aspect == 10 // call
        || curTok -> attribute == ID // ID
        || curTok -> attribute == CONTROL && curTok -> aspect == 5 // if
        || curTok -> attribute == CONTROL && curTok -> aspect == 9) // while
    {
        statement_list();
        return;

    // Production 12.2
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 3) // end
        return; // epsilon

    synch();
}
