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
void type()
{
    // Production 4.2
    if (curTok -> category == ARRAY && curTok -> type == 0)
    {
        if (match(ARRAY, 0, true)) // array
            if (match(GROUP, 2, true)) // [
                if (match(INT, 0, false)) // INT
                    if (match(ARRAY, 1, true)) // ..
                        if (match(INT, 0, false)) // INT
                            if (match(GROUP, 3, true)) // ]
                                if (match(ARRAY, 2, true)) // of
                                {
                                    standard_type();
                                    return;
                                }
    // Production 4.1
    } else if ((curTok -> category == TYPE && curTok -> type == 1) // INT
               || (curTok -> category == TYPE && curTok -> type == 2)) // REAL
    {
        standard_type();
        return;
    }

    synch();
}
