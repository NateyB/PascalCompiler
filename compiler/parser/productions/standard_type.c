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
void standard_type()
{
    // Production 5.1
    if (curTok -> category == TYPE && curTok -> type == 1) // integer
    {
        if (match(TYPE, 1, true))
            return;

    // Production 5.2
    } else if (curTok -> category == TYPE && curTok -> type == 2) { // real
        if (match(TYPE, 2, true))
            return;
    }

    synch();
}
