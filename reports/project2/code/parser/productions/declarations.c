#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&var_tok, &procedure_tok, &begin_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &procedure_tok, &begin_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void declarations()
{
    // Production 3.1
    if (tokens_equal(&var_tok, current_tok, true))
    {
        match(&var_tok, true);
        Token* id_ref = match(&id_tok, false);
        match(&colon_tok, true);
        if (id_ref != NULL) {
            id_ref -> type = type(id_ref);
            id_ref -> param = false;
            check_add_node(id_ref);
        } else {
            type(NULL);
        }
        match(&semic_tok, true);
        declarations();
        return;

    // Production 3.2
    } else if (tokens_equal(&begin_tok, current_tok, true)
               || tokens_equal(&procedure_tok, current_tok, true))
               return; // epsilon

    synch();
}
