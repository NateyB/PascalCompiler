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
    if (curTok -> attribute == CONTROL && curTok -> aspect == 2) // else
    {
        if (match(CONTROL, 2, true)) {
            statement();
            return;
        }

    // Production 15.2
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 3 // end
               || curTok -> attribute == PUNC && curTok -> aspect == 1) // ;
        return; // epsilon

    synch();
}
