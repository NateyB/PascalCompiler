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

// Needs implementing: All
void sign()
{
    // Production 24.2.1
    if (curTok -> attribute == ADDOP && curTok -> aspect == 0) { // +
        if (match(ADDOP, 0, true)) // +
            return;

    // Production 24.2.2
    } else if (curTok -> attribute == ADDOP && curTok -> aspect == 1) { // -
        if (match(ADDOP, 1, true)) // -
            return; // epsilon
    }
    synch();
}
