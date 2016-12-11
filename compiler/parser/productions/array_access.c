#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&assignop_tok, &lbrac_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &assignop_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void array_access()
{
    // Production 17.1
    if (tokens_equal(&lbrac_tok, current_tok, true))
    {
        if (match(&lbrac_tok, true)) {
            expression();
            if (match(&rbrac_tok, true))
                return;
        }

    // Production 17.2
    } else if (tokens_equal(&assignop_tok, current_tok, true))
        return; // epsilon

    synch();
}
