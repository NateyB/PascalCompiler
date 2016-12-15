#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&lparen_tok, &semic_tok, &end_tok,
                                   &else_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void optional_expressions(tree_node* to_match, bool should_error)
{
    char* errorMessage;
    // Production 19.1
    if (tokens_equal(&lparen_tok, current_tok, true))
    {
        match(&lparen_tok, true);
        expression_list(to_match, should_error);
        match(&rparen_tok, true);
        return;

    // Production 19.2
    } else if (tokens_equal(&semic_tok, current_tok, true)
          || tokens_equal(&else_tok, current_tok, true)
          || tokens_equal(&end_tok, current_tok, true))
    {
        if (to_match != NULL && should_error) {
            errorMessage  = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Expected an argument of type %s!",
                                    typeNames[to_match -> type]);
            throw_sem_error(errorMessage);
        }

        return; // epsilon
    }

    synch();
}
