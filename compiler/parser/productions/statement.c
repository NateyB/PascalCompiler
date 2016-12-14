#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&id_tok, &call_tok, &begin_tok, &while_tok,
                                   &if_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok, &semic_tok, &end_tok, &else_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void statement()
{
    char* errorMessage;
    // Production 14.1
    if (tokens_equal(&id_tok, current_tok, false)) { // id
        Token* id_tok = current_tok;
        LangType v_type = variable();
        if (match(&assignop_tok, true)) // :=
        {
            if (get_type(id_tok) == ERR)
            // The only way for this to error is an undeclared variable
            {
                errorMessage = calloc(100, sizeof(*errorMessage));
                sprintf(errorMessage, "ID '%.*s' not in scope!",
                                        id_tok -> length,
                                        &BUFFER[id_tok -> start]);
                throw_sem_error(errorMessage);
                expression();
                return;
            }
            LangType e_type = expression();
            type_lookup(v_type, e_type, &assignop_tok);
            return;
        }

    // Production 14.2
    } else if (tokens_equal(&call_tok, current_tok, true)) { // call
        procedure_statement();
        return;

    // Production 14.3
    } else if (tokens_equal(&begin_tok, current_tok, true)) { // begin
        compound_statement();
        return;

    // Production 14.4
    } else if (tokens_equal(&while_tok, current_tok, true)) { // while
        if (match(&while_tok, true)) { // while
            LangType e_type = expression();
            if (e_type != BOOL && e_type != ERR)
            {
                errorMessage  = calloc(100, sizeof(*errorMessage));
                sprintf(errorMessage, "Expression in while must be boolean, not %s!",
                                        typeNames[e_type]);
                throw_sem_error(errorMessage);
            }
            if (match(&do_tok, true)) { // do
                statement();
                return;
            }
        }

    // Production 14.5
    } else if (tokens_equal(&if_tok, current_tok, true)) { // if
        if (match(&if_tok, true)) { // if
            LangType e_type = expression();
            if (e_type != BOOL && e_type != ERR)
            {
                errorMessage  = calloc(100, sizeof(*errorMessage));
                sprintf(errorMessage, "If clause must be a boolean expression, not %s!",
                                        typeNames[e_type]);
                throw_sem_error(errorMessage);
            }
            if (match(&then_tok, true)) { // then
                statement();
                else_tail();
                return;
            }
        }
    }


    synch();
}
