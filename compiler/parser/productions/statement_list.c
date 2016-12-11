#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"
static const Token* first_set[] = {&id_tok, &call_tok, &begin_tok, &while_tok,
                                   &if_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &end_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void statement_list()
{
    // Production 13.1
    if (tokens_equal(&begin_tok, current_tok, true)
        || tokens_equal(&call_tok, current_tok, true)
        || tokens_equal(&id_tok, current_tok, false)
        || tokens_equal(&if_tok, current_tok, true)
        || tokens_equal(&while_tok, current_tok, true))
    {
        statement();
        statement_list_tail();
        return;
    }

    synch();
}
