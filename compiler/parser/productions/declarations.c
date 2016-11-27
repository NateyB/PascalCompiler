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
void declarations()
{
    // Production 3.1
    if (curTok -> category == VAR && curTok -> type == 0) // Declaration
    {
        if (match(VAR, 0, true)) // var
            if (match(ID, 0, false)) // ID
                if (match(TYPE, 0, true)) // :
                {
                    type();
                    if (match(PUNC, 1, true)) // ;
                    {
                        declarations();
                        return;
                    }
                }
    // Production 3.2
    } else if ((curTok -> category == CONTROL && curTok -> type == 0) // Begin
               || (curTok -> category == CONTROL && curTok -> type == 6)) //Proc
               return; // Epsilon

    synch();
}
