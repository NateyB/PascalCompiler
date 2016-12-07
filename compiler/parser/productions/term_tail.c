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
void term_tail()
{
    // Production 24.2.1
    if (curTok -> attribute == MULOP) { // MULOP
        if (match(MULOP, 0, false)) { // MULOP
            factor();
            term_tail();
            return;
        }

    // Production 24.2.2
    } else if (curTok -> attribute == GROUP && curTok -> aspect == 1 // )
        || curTok -> attribute == PUNC && curTok -> aspect == 0 // ,
        || curTok -> attribute == PUNC && curTok -> aspect == 1 // ;
        || curTok -> attribute == GROUP && curTok -> aspect == 3 // ]
        || curTok -> attribute == ADDOP                         // ADDOP
        || curTok -> attribute == CONTROL && curTok -> aspect == 1 // do
        || curTok -> attribute == CONTROL && curTok -> aspect == 2 // else
        || curTok -> attribute == CONTROL && curTok -> aspect == 3 // end
        || curTok -> attribute == RELOP                          // RELOP
        || curTok -> attribute == CONTROL && curTok -> aspect == 8) // then
        return; // epsilon

    synch();
}
