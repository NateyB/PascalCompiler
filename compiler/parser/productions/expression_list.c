#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok, &num_tok, &lparen_tok, &not_tok,
                                   &plus_tok, &minus_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &rparen_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void expression_list(tree_node* to_match)
{
    // Production 20.1
    if (tokens_equal(&lparen_tok, current_tok, true)
        || tokens_equal(&addop_tok, current_tok, false) // + OR -
        || tokens_equal(&id_tok, current_tok, false) // ID
        || tokens_equal(&not_tok, current_tok, true)
        || tokens_equal(&num_tok, current_tok, false)) // num
    {
        char* errorMessage;
        if (to_match == NULL)
        {
            errorMessage  = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Attempt to pass extraneous paramters!");
            throw_sem_error(errorMessage);
        }
        LangType e_type = expression();
        if (to_match != NULL && e_type != to_match -> type) {
            errorMessage  = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Expected type %s, not %s!",
                                    typeNames[to_match -> type], typeNames[e_type]);
            throw_sem_error(errorMessage);
        }
        expression_list_tail(to_match == NULL ? NULL : to_match -> left);
        return;
    }

    synch();
}
