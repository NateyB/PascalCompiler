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
void id_list()
{
    // Production 2.1
    if (curTok -> attribute == ID)
        if (match(ID, 0, false)) // ID
        {
            id_list_tail();
            return;
        }

    synch();
}
