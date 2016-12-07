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
void arguments()
{
    // Production 9.1
    if (curTok -> attribute == GROUP && curTok -> aspect == 0) // (
    {
        if (match(GROUP, 0, true)) { // (
            parameter_list();
            if (match(GROUP, 1, true)) // )
                return;
        }

    // Production 9.2
    } else if (curTok -> attribute == PUNC && curTok -> aspect == 1) // ;
        return; // Epsilon

    synch();
}
