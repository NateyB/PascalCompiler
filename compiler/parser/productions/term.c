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
void term()
{
    // Production 24.1
    if (curTok -> attribute == GROUP && curTok -> aspect == 0 // (
        || curTok -> attribute == ID // ID
        || curTok -> attribute == INVERSE && curTok -> aspect == 0 // not
        || curTok -> attribute == NUM) { // num
        factor();
        term_tail();
        return;
    }

    synch();
}
