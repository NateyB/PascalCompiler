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
LangType simple_expression()
{
    char* errorMessage;
    // Production 23.1.1
    if (tokens_equal(&lparen_tok, current_tok, true)
        || tokens_equal(&id_tok, current_tok, false)
        || tokens_equal(&not_tok, current_tok, true)
        || tokens_equal(&num_tok, current_tok, false))
    {
        LangType t_type = term();
        return simple_expression_tail(t_type);

    // Production 23.1.2
    } else if (tokens_equal(&plus_tok, current_tok, true)
               || tokens_equal(&minus_tok, current_tok, true)) {
        sign();
        LangType t_type = term();
        if (t_type != INT && t_type != REAL && t_type != ERR)
        {
            errorMessage  = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Expected number, not %s!",
                                    typeNames[t_type]);
            throw_sem_error(errorMessage);
        }
        return simple_expression_tail(t_type);
    }

    synch();
    return ERR;
}
