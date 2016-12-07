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
void statement()
{
    // Production 14.1
    if (curTok -> attribute == ID) { // id
        variable();
        if (match(ASSIGNOP, 0, true)) // :=
        {
            expression();
            return;
        }

    // Production 14.2
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 10) { // call
        procedure_statement();
        return;

    // Production 14.3
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 0) { // begin
        compound_statement();
        return;

    // Production 14.4
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 9) { // while
        if (match(CONTROL, 9, true)) { // while
            expression();
            if (match(CONTROL, 1, true)) { // do
                statement();
                return;
            }
        }

    // Production 14.5
    } else if (curTok -> attribute == CONTROL && curTok -> aspect == 5) { // if
        if (match(CONTROL, 5, true)) { // if
            expression();
            if (match(CONTROL, 8, true)) { // then
                statement();
                else_tail();
                return;
            }
        }
    }


    synch();
}
