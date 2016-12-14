#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&lbrac_tok, &mulop_tok, &addop_tok, &relop_tok,
                                   &semic_tok, &end_tok, &else_tok, &do_tok,
                                   &then_tok, &rbrac_tok, &rparen_tok,
                                   &comma_tok};
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

static LangType array_compare(LangType a_vals, LangType e_type) {
    if ((a_vals == INT || a_vals == REAL) && e_type == INT)
        return a_vals;
    if (a_vals != ERR && e_type != ERR)
        // SEMERR
        ;

    return ERR;
}

// Needs implementing: None
LangType factor_tail(id_type)
{
    // Production 25.2.1
    if (tokens_equal(&lbrac_tok, current_tok, true)) {
        if (match(&lbrac_tok, true)) {
            LangType e_type = expression();
            if (match(&rbrac_tok, true))
            {
                LangType n_type = convert_from_array(id_type);
                return array_compare(n_type, e_type);
            }
        }

    // Production 25.2.2
    } else if (tokens_equal(&rparen_tok, current_tok, true)
        || tokens_equal(&comma_tok, current_tok, true)
        || tokens_equal(&semic_tok, current_tok, true)
        || tokens_equal(&rbrac_tok, current_tok, true)
        || tokens_equal(&addop_tok, current_tok, false)
        || tokens_equal(&do_tok, current_tok, true)
        || tokens_equal(&else_tok, current_tok, true)
        || tokens_equal(&end_tok, current_tok, true)
        || tokens_equal(&mulop_tok, current_tok, false)
        || tokens_equal(&relop_tok, current_tok, false)
        || tokens_equal(&then_tok, current_tok, true))
        return id_type; // epsilon

    synch();
    return ERR;
}
