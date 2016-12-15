#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&assignop_tok, &lbrac_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &assignop_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

static LangType array_compare(LangType a_vals, LangType e_type) {
    if ((a_vals == INT || a_vals == REAL) && e_type == INT)
        return a_vals;
    if (a_vals != ERR)
    {
        char* errorMessage = calloc(100, sizeof(*errorMessage));
        sprintf(errorMessage, "Attempt to index variable of type %s!", typeNames[a_vals]);
        throw_sem_error(errorMessage);
    }

    return ERR;
}

// Needs implementing: None
LangType array_access(LangType id_type)
{
    // Production 17.1
    if (tokens_equal(&lbrac_tok, current_tok, true))
    {
        match(&lbrac_tok, true);
        LangType e_type = expression();
        match(&rbrac_tok, true);
        LangType n_type = convert_from_array(id_type);
        return array_compare(n_type, e_type);

    // Production 17.2
    } else if (tokens_equal(&assignop_tok, current_tok, true))
        return id_type; // epsilon

    synch();
    return ERR;
}
