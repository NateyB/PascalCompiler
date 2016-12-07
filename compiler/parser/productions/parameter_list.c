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
void parameter_list()
{
    // Production 10.1
    if (curTok -> attribute == ID) {
        if (match(ID, 0, false)) // ID
            if (match(TYPE, 0, true)) { // :
                type();
                parameter_list_tail();
                return;
            }
    }

    synch();
}
