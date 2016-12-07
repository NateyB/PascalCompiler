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
void procedure_statement()
{
    // Production 18
    if (curTok -> attribute == CONTROL && curTok -> aspect == 10) // call
        if (match(CONTROL, 10, true)) // call
            if (match(ID, 0, false)) { // id
                optional_expressions();
                return;
            }

    synch();
}
