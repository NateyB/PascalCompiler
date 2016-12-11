#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&relop_tok,
                                   &semic_tok, &end_tok, &else_tok, &do_tok,
                                   &then_tok, &rbrac_tok, &rparen_tok,
                                   &comma_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok,
                                  &else_tok, &do_tok, &then_tok, &rbrac_tok,
                                  &rparen_tok, &comma_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void related_expression()
{
    // Production 22.1
    if (tokens_equal(&relop_tok, current_tok, false)) {
        if (match(&relop_tok, false)) {
            simple_expression();
            return;
        }

    // Production 22.2
    } else if (tokens_equal(&rparen_tok, current_tok, true)
        || tokens_equal(&comma_tok, current_tok, true)
        || tokens_equal(&semic_tok, current_tok, true)
        || tokens_equal(&rbrac_tok, current_tok, true)
        || tokens_equal(&do_tok, current_tok, true)
        || tokens_equal(&else_tok, current_tok, true)
        || tokens_equal(&end_tok, current_tok, true)
        || tokens_equal(&then_tok, current_tok, true))
        return; // epsilon

    synch();
}
