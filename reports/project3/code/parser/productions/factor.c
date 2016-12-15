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
LangType factor()
{
    // Production 25.1.1
    if (tokens_equal(&id_tok, current_tok, false)) { // id
        char* errorMessage;
        Token* id_ref = match(&id_tok, false); // id
        LangType id_type = get_type(id_ref);
        if (id_type == NULL) {
            errorMessage = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage,
                 "No variable '%.*s' is defined in the local scope!",
                 id_ref -> length, &BUFFER[id_ref -> start]);
             throw_sem_error(errorMessage);
             id_type = ERR;
        }
        return factor_tail(id_type);

    // Production 25.1.2
    } else if (tokens_equal(&num_tok, current_tok, false)) { // num
        Token* num_type;
        num_type = match(&num_tok, false);
        return num_type -> aspect == 0 ? INT : REAL;

    // Production 25.1.3
    } else if (tokens_equal(&lparen_tok, current_tok, true)) { // (
        match(&lparen_tok, true);
        LangType e_type = expression();
        match(&rparen_tok, true); // )
        return e_type;

    // Production 25.1.4
    } else if (tokens_equal(&not_tok, current_tok, true)) { // not
        match(&not_tok, true);
        LangType f_type = factor();
        return type_lookup(f_type, INT, &not_tok);
    }


    synch();
    return ERR;
}
