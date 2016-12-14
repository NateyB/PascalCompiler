#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&procedure_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &var_tok, &procedure_tok,
                                  &begin_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
bool subprogram_head()
{
    bool result = false;
    // Production 8
    if (tokens_equal(&procedure_tok, current_tok, true)) // procedure
    {
        Token* id_ref;
        if (match(&procedure_tok, true)) // procedure
            if ((id_ref = match(&id_tok, false))) { // id
                id_ref -> type = PROC;
                id_ref -> param = false;
                result = check_add_node(id_ref);
                arguments();
                if (match(&semic_tok, true)) // ;
                    return result;
                }
    }

    synch();
    return result;
}
