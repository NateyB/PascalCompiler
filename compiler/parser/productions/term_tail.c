#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&mulop_tok, &addop_tok, &relop_tok,
                                   &semic_tok, &end_tok, &else_tok, &do_tok,
                                   &then_tok, &rbrac_tok, &rparen_tok,
                                   &comma_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &addop_tok, &relop_tok, &semic_tok,
                                  &end_tok, &else_tok, &do_tok, &then_tok,
                                  &rbrac_tok, &rparen_tok, &comma_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void term_tail()
{
    // Production 24.2.1
    if (tokens_equal(&mulop_tok, current_tok, false)) { // MULOP
        if (match(&mulop_tok, false)) { // MULOP
            factor();
            term_tail();
            return;
        }

    // Production 24.2.2
    } else if (tokens_equal(&rparen_tok, current_tok, true)
        || tokens_equal(&comma_tok, current_tok, true)
        || tokens_equal(&semic_tok, current_tok, true)
        || tokens_equal(&rbrac_tok, current_tok, true)
        || tokens_equal(&addop_tok, current_tok, false)
        || tokens_equal(&do_tok, current_tok, true)
        || tokens_equal(&else_tok, current_tok, true)
        || tokens_equal(&end_tok, current_tok, true)
        || tokens_equal(&relop_tok, current_tok, false)
        || tokens_equal(&then_tok, current_tok, true))
        return; // epsilon

    synch();
}
