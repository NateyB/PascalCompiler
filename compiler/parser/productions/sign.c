#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&plus_tok, &minus_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &id_tok, &num_tok,
    &not_tok, &rparen_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void sign()
{
    // Production 24.2.1
    if (tokens_equal(&plus_tok, current_tok, true)) {
        match(&plus_tok, true);
        return;

    // Production 24.2.2
    } else if (tokens_equal(&minus_tok, current_tok, true)) {
        match(&minus_tok, true);
        return; // epsilon
    }
    synch();
}
