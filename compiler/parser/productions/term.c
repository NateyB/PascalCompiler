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
    if (curTok -> category == GROUP && curTok -> type == 0 // (
        || curTok -> category == ID // ID
        || curTok -> category == INVERSE && curTok -> type == 0 // not
        || curTok -> cateogry == INT || curTok -> category == REAL) { // num
        factor();
        term_tail();
        return;
    }

    synch();
}
