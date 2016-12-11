#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&procedure_tok, &begin_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &begin_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void subprogram_declarations()
{
    // Production 6.1
    if (tokens_equal(&procedure_tok, current_tok, true)) // procedure
    {
        subprogram_declaration();
        if (match(&semic_tok, true)) { // ;
            subprogram_declarations();
            return;
        }

    // Production 6.2
    } else if (tokens_equal(&begin_tok, current_tok, true)) // begin
        return; // Epsilon

    synch();
}
