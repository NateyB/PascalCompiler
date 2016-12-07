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
    if (curTok -> category == GROUP && curTok -> type == 0 // (
        || curTok -> category == ADDOP // + OR -
        || curTok -> category == ID // id
        || curTok -> category == INVERSE && curTok -> type == 0 // not
        || curTok -> category == INT || curTok -> category == REAL) // num
    {
        expression();
        expression_list_tail();
        return;
    }

    synch();
}
