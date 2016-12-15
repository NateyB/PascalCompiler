#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&integer_tok, &real_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &rparen_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
LangType standard_type()
{
    // Production 5.1
    if (tokens_equal(&integer_tok, current_tok, true)) // integer
    {
        match(&integer_tok, true);
        return INT;

    // Production 5.2
    } else if (tokens_equal(&real_tok, current_tok, true)) { // real
        match(&real_tok, true);
        return REAL;
    }

    synch();
    return ERR;
}
