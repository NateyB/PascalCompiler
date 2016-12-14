#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&comma_tok, &rparen_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &rparen_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void id_list_tail()
{
    // Production 2.2.1
    if (tokens_equal(&comma_tok, current_tok, true))
    {
        match(&comma_tok, true);
        Token* id_ref;
        // Production 2.1
        if ((id_ref = match(&id_tok, false)))
        {
            id_ref -> type = PPNAME;
            id_ref -> param = true;
            check_add_node(id_ref);id_list_tail();
            return;
        }
    // Production 2.2.2
    } else if (tokens_equal(&rparen_tok, current_tok, true))
        return; // Epsilon

    synch();
}
