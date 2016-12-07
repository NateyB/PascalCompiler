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
void statement_list_tail()
{
    // Production 13.2.1
    if (curTok -> category == PUNC && curTok -> type == 1) // ;
    {
        if (match(PUNC, 1, true)) {
            statement();
            statement_list_tail();
            return;
        }

    // Production 13.2.2
    } else if (curTok -> category == CONTROL && curTok -> type == 3) // end
        return; // epsilon

    synch();
}
