#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&program_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&eof_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void program()
{
    Token* id_ref;
    // Production 1
    if (tokens_equal(&program_tok, current_tok, true)) {
        match(&program_tok, true); // program
        id_ref = match(&id_tok, false); // id
        if (id_ref != NULL) {
            id_ref -> type = PGNAME;
            id_ref -> param = false;
            check_add_node(id_ref);
        }
        match(&lparen_tok, true); // (
        id_list();
        match(&rparen_tok, true); // )
        match(&semic_tok, true); // ;
        declarations();
        subprogram_declarations();
        compound_statement();
        match(&period_tok, true); // .
        return;
    }

    synch();
}
