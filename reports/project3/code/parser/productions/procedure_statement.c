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
    char* errorMessage;
    // Production 18
    if (tokens_equal(&call_tok, current_tok, true)) // call
    {
        Token* id_ref;
        match(&call_tok, true); // call
        id_ref = match(&id_tok, false);
        if (id_ref != NULL) {
            tree_node* addition = start_param_matching(id_ref);
            if (addition == NULL) {
                errorMessage  = calloc(100, sizeof(*errorMessage));
                sprintf(errorMessage, "Procedure '%s' not in scope!", id_ref -> id);
                throw_sem_error(errorMessage);

                optional_expressions(NULL, false);
            } else
               optional_expressions(addition -> left == NULL ? NULL : addition -> left -> param ? addition -> left : NULL, true);
        } else {
            optional_expressions(NULL, false);
        }
        return;
    }

    synch();
}
