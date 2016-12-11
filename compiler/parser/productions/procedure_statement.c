#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&call_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void procedure_statement()
{
    // Production 18
    if (tokens_equal(&call_tok, current_tok, true)) // call
        if (match(&call_tok, true)) // call
            if (match(&id_tok, false)) { // id
                optional_expressions();
                return;
            }

    synch();
}
