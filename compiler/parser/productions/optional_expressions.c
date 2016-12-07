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
void optional_expressions()
{
    // Production 19.1
    if (curTok -> category == GROUP && curTok -> type == 0) // (
    {
        if (match(GROUP, 0, true)) { // (
            expression_list();
            if (match(GROUP, 1, true)) // )
                return;
        }

    // Production 19.2
    } else if (curTok -> category == PUNC && curTok -> type == 1 // ;
          || curTok -> category == CONTROL && curTok -> type == 2 // else
          || curTok -> category == CONTROL && curTok -> type == 3) // end
        return; // epsilon

    synch();
}
