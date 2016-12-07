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
void subprogram_head()
{
    // Production 8
    if (curTok -> category == CONTROL && curTok -> type == 6) // procedure
    {
        if (match(CONTROL, 6, true)) // procedure
            if (match(ID, 0, false)) { // id
                arguments();
                if match(PUNC, 1, true) // ;
                    return;
                }
            }
    }

    synch();
}
