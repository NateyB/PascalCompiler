#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&else_tok, &semic_tok, &end_tok, &else_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void else_tail()
{
    // Production 15.1
    if (tokens_equal(&else_tok, current_tok, true)) // else
    {
        if (match(&else_tok, true)) {
            statement();
            return;
        }

    // Production 15.2
    } else if (tokens_equal(&end_tok, current_tok, true) // end
               || tokens_equal(&semic_tok, current_tok, true)) // ;
        return; // epsilon

    synch();
}
