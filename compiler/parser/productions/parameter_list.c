#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &rparen_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void parameter_list()
{
    // Production 10.1
    if (tokens_equal(&id_tok, current_tok, false)) {
        if (match(&id_tok, false)) // ID
            if (match(&colon_tok, true)) { // :
                type();
                parameter_list_tail();
                return;
            }
    }

    synch();
}
