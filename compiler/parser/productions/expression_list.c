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
void expression_list()
{
    // Production 20.1
    if (curTok -> attribute == GROUP && curTok -> aspect == 0 // (
        || curTok -> attribute == ADDOP // + OR -
        || curTok -> attribute == ID // id
        || curTok -> attribute == INVERSE && curTok -> aspect == 0 // not
        || curTok -> attribute == INT || curTok -> attribute == REAL) // num
    {
        expression();
        expression_list_tail();
        return;
    }

    synch();
}
