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
void compound_statement()
{
    // Production 11
    if (curTok -> category == CONTROL && curTok -> type == 0) // begin
    {
        if (match(CONTROL, 0, true)) { // begin
            optional_statements();
            if (match(CONTROL, 3, true)) // end
                return;
        }
    }

    synch();
}
