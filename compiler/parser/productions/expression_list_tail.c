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
void expression_list_tail(tree_node* to_match, bool should_error)
{
    char* errorMessage;
    // Production 20.2.1
    if (tokens_equal(&comma_tok, current_tok, true))
    {
        match(&comma_tok, true);
        if ((to_match == NULL || !to_match -> param) && should_error)
        {
            errorMessage = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Incorrect number of arguments!");
            throw_sem_error(errorMessage);
        }
        LangType e_type = expression();
        if (should_error && to_match != NULL && to_match -> param && e_type != ERR && e_type != to_match -> type) {
            errorMessage = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Expected type %s, not %s!",
                                    typeNames[to_match -> type], typeNames[e_type]);
            throw_sem_error(errorMessage);
        }
        expression_list_tail(to_match == NULL || !to_match -> param ? NULL :
                        to_match -> left, e_type != ERR && should_error);
        return;

    // Production 20.2.2
    } else if (tokens_equal(&rparen_tok, current_tok, true))
    {
        if (to_match != NULL && to_match -> param && should_error) {
            errorMessage = calloc(100, sizeof(*errorMessage));
            sprintf(errorMessage, "Incorrect number of arguments!",
                                    typeNames[to_match -> type]);
            throw_sem_error(errorMessage);
        }
        return; // epsilon
    }

    synch();
}
