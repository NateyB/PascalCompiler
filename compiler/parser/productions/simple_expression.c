#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok, &num_tok, &lparen_tok, &not_tok,
                                   &plus_tok, &minus_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &relop_tok, &semic_tok,
                                  &end_tok, &else_tok, &do_tok, &then_tok,
                                  &rbrac_tok, &rparen_tok, &comma_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void simple_expression()
{
    // Production 23.1.1
    if (tokens_equal(&lparen_tok, current_tok, true)
        || tokens_equal(&id_tok, current_tok, false)
        || tokens_equal(&not_tok, current_tok, true)
        || tokens_equal(&num_tok, current_tok, false))
    {
        term();
        simple_expression_tail();
        return;

    // Production 23.1.2
    } else if (tokens_equal(&addop_tok, current_tok, false)) {
        sign();
        term();
        simple_expression_tail();
        return;
    }

    synch();
}
