#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok, &call_tok, &begin_tok, &while_tok,
                                   &if_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void statement()
{
    // Production 14.1
    if (tokens_equal(&id_tok, current_tok, false)) { // id
        variable();
        if (match(&assignop_tok, true)) // :=
        {
            expression();
            return;
        }

    // Production 14.2
    } else if (tokens_equal(&call_tok, current_tok, true)) { // call
        procedure_statement();
        return;

    // Production 14.3
    } else if (tokens_equal(&begin_tok, current_tok, true)) { // begin
        compound_statement();
        return;

    // Production 14.4
    } else if (tokens_equal(&while_tok, current_tok, true)) { // while
        if (match(&while_tok, true)) { // while
            expression();
            if (match(&do_tok, true)) { // do
                statement();
                return;
            }
        }

    // Production 14.5
    } else if (tokens_equal(&if_tok, current_tok, true)) { // if
        if (match(&if_tok, true)) { // if
            expression();
            if (match(&then_tok, true)) { // then
                statement();
                else_tail();
                return;
            }
        }
    }


    synch();
}
