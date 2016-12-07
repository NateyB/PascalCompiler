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
void expression_list_tail()
{
    // Production 20.2.1
    if (curTok -> attribute == PUNC && curTok -> aspect == 0) // ,
    {
        if (match(PUNC, 0, true)) { // ,
            expression();
            expression_list_tail();
            return;
        }

    // Production 20.2.2
    } else if (curTok -> attribute == GROUP && curTok -> aspect == 1) // (
        return; // epsilon

    synch();
}
