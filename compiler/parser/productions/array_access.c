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
void array_access()
{
    // Production 17.1
    if (curTok -> attribute == GROUP && curTok -> aspect == 2) // [
    {
        if (match(GROUP, 2, true)) { // [
            expression();
            if (match(GROUP, 3, true)) // ]
                return;
        }

    // Production 17.2
    } else if (curTok -> attribute == ASSIGNOP && curTok -> aspect == 0) // :=
        return; // epsilon

    synch();
}
