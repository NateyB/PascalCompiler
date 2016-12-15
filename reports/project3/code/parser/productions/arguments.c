#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&lparen_tok, &semic_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void arguments()
{
    // Production 9.1
    if (tokens_equal(&lparen_tok, current_tok, true))
    {
        match(&lparen_tok, true);
        parameter_list();
        match(&rparen_tok, true);
        return;

    // Production 9.2
    } else if (tokens_equal(&semic_tok, current_tok, true))
        return; // Epsilon

    synch();
}
