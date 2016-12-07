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
void variable()
{
    // Production 16
    if (curTok -> attribute == ID) // id
    {
        if (match(ID, 0, false)) { // id
            array_access();
            return;
        }
    }

    synch();
}
