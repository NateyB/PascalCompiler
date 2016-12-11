#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok, &num_tok, &lparen_tok, &not_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &mulop_tok, &addop_tok, &relop_tok,
                                  &semic_tok, &end_tok, &else_tok, &do_tok,
                                  &then_tok, &rbrac_tok, &rparen_tok,
                                  &comma_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: 25.1.2
void factor()
{
    // Production 25.1.1
    if (tokens_equal(&id_tok, current_tok, false)) { // id
        if (match(&id_tok, false)) // id
        {
            factor_tail();
            return;
        }

    // Production 25.1.2
    } else if (tokens_equal(&num_tok, current_tok, false)) { // num
        if (match(&num_tok, false))
            return;

    // Production 25.1.3
    } else if (tokens_equal(&lparen_tok, current_tok, true)) { // (
        if (match(&lparen_tok, true)) { // (
            expression();
            if (match(&rparen_tok, true)) // )
                return;
        }

    // Production 25.1.4
    } else if (tokens_equal(&not_tok, current_tok, true)) { // not
        if (match(&not_tok, true)) { // not
            factor();
            return;
        }
    }


    synch();
}
