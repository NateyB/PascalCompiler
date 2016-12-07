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
void simple_expression_tail()
{
    // Production 23.2.1
    if (curTok -> attribute == ADDOP) { // ADDOP
        if (match(ADDOP, 0, false)) { // ADDOP
            term();
            simple_expression_tail();
            return;
        }

    // Production 23.2.2
    } else if (curTok -> attribute == GROUP && curTok -> aspect == 1 // )
        || curTok -> attribute == PUNC && curTok -> aspect == 0 // ,
        || curTok -> attribute == PUNC && curTok -> aspect == 1 // ;
        || curTok -> attribute == GROUP && curTok -> aspect == 3 // ]
        || curTok -> attribute == CONTROL && curTok -> aspect == 1 // do
        || curTok -> attribute == CONTROL && curTok -> aspect == 2 // else
        || curTok -> attribute == CONTROL && curTok -> aspect == 3 // end
        || curTok -> attribute == RELOP                          // RELOP
        || curTok -> attribute == CONTROL && curTok -> aspect == 8) // then
        return; // epsilon

    synch();
}
