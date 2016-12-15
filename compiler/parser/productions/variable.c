#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &assignop_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
LangType variable()
{
    // Production 16
    if (tokens_equal(&id_tok, current_tok, false)) // id
    {
        Token* id_ref;
        id_ref = match(&id_tok, false);
        return array_access(get_type(id_ref));
    }

    synch();
    return ERR;
}
