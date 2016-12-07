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
void else_tail()
{
    // Production 15.1
    if (curTok -> category == CONTROL && curTok -> type == 2) // else
    {
        if (match(CONTROL, 2, true)) {
            statement();
            return;
        }

    // Production 15.2
    } else if (curTok -> category == CONTROL && curTok -> type == 3 // end
               || curTok -> category == PUNC && curTok -> type == 1) // ;
        return; // epsilon

    synch();
}
