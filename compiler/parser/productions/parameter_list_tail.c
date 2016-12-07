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
void parameter_list_tail()
{
    // Production 10.2.1
    if (curTok -> attribute == PUNC && curTok -> aspect == 1) // ;
    {
        if (match(PUNC, 1, true)) // ;
            if (match(ID, 0, false)) // ID
                if (match(TYPE, 0, true)) { // :
                    type();
                    parameter_list_tail();
                    return;
                }

    // Production 10.2.2
    } else if (curTok -> attribute == GROUP && curTok -> aspect == 2) // )
        return; // epsilon

    synch();
}
