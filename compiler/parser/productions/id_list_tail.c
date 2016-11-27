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
void id_list_tail()
{
    // Production 2.2.1
    if (curTok -> category == PUNC && curTok -> type == 0) // ,
    {
        match(PUNC, 0, true);
        if (match(ID, 0, false)) // ID
        {
            id_list_tail();
            return;
        }
    // Production 2.2.2
    } else if (curTok -> category == GROUP && curTok -> type == 1) // )
        return; // Epsilon

    synch();
}
