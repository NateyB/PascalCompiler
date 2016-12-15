#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&begin_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &period_tok,
                                  &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}


// Needs implementing: None
void compound_statement()
{
    // Production 11
    if (tokens_equal(&begin_tok, current_tok, true))
    {
        match(&begin_tok, true);
        optional_statements();
        match(&end_tok, true);
        return;
    }

    synch();
}
