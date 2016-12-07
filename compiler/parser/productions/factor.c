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

// Needs implementing: 25.1.2
void factor()
{
    // Production 25.1.1
    if (curTok -> category == ID) { // id
        if (match(ID, 0, false)) // id
        {
            factor_tail();
            return;
        }

    // Production 25.1.2
    } else if (curTok -> category == INT || curTok -> category == REAL) { // num
        // TODO Implement as num
        return;

    // Production 25.1.3
    } else if (curTok -> category == GROUP && curTok -> type == 0) { // (
        if (match(GROUP, 0, true)) { // (
            expression();
            if (match(GROUP, 1, true)) // )
                return;
        }

    // Production 25.1.4
    } else if (curTok -> category == INVERSE && curTok -> type == 0) { // not
        if (match(INVERSE, 0, true)) { // not
            factor();
            return;
        }
    }


    synch();
}
