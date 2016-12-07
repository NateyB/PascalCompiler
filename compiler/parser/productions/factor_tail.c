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
void factor_tail()
{
    // Production 25.2.1
    if (curTok -> category == GROUP && curTok -> category == 2) { // [
        if (match(GROUP, 2, true)) { // [
            expression();
            if (match(GROUP, 3, true)) // ]
                return;
        }

    // Production 25.2.2
    } else if (curTok -> category == GROUP && curTok -> type == 1 // )
        || curTok -> category == PUNC && curTok -> type == 0 // ,
        || curTok -> category == PUNC && curTok -> type == 1 // ;
        || curTok -> category == GROUP && curTok -> type == 3 // ]
        || curTok -> category == ADDOP                         // ADDOP
        || curTok -> category == CONTROL && curTok -> type == 1 // do
        || curTok -> category == CONTROL && curTok -> type == 2 // else
        || curTok -> category == CONTROL && curTok -> type == 3 // end
        || curTok -> category == MULOP                          // MULOP
        || curTok -> category == RELOP                          // RELOP
        || curTok -> category == CONTROL && curTok -> type == 8) // then
        return; // epsilon

    synch();
}
