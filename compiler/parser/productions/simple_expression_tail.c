#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&addop_tok, &relop_tok,
                                   &semic_tok, &end_tok, &else_tok, &do_tok,
                                   &then_tok, &rbrac_tok, &rparen_tok,
                                   &comma_tok};
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
LangType simple_expression_tail(LangType t_type)
{
    // Production 23.2.1
    if (tokens_equal(&addop_tok, current_tok, false)) {
        Token* addop_op;
        addop_op = match(&addop_tok, false);
        LangType t_type2 = term();
        return simple_expression_tail(type_lookup(t_type, t_type2, addop_op));


    // Production 23.2.2
    } else if (tokens_equal(&rparen_tok, current_tok, true)
        || tokens_equal(&comma_tok, current_tok, true)
        || tokens_equal(&semic_tok, current_tok, true)
        || tokens_equal(&rbrac_tok, current_tok, true)
        || tokens_equal(&do_tok, current_tok, true)
        || tokens_equal(&else_tok, current_tok, true)
        || tokens_equal(&end_tok, current_tok, true)
        || tokens_equal(&relop_tok, current_tok, false)
        || tokens_equal(&then_tok, current_tok, true))
        return t_type; // epsilon

    synch();
    return ERR;
}
