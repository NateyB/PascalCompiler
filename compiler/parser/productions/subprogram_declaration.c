#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&procedure_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&procedure_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void subprogram_declaration()
{
    // Production 7
    if (tokens_equal(&procedure_tok, current_tok, true)) // procedure
    {
        subprogram_head();
        declarations();
        subprogram_declarations();
        compound_statement();

        reached_end_of_scope(); // pop from stack
        return;
    }

    synch();
}
