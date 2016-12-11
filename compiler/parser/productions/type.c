#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token* first_set[] = {&integer_tok, &real_tok, &array_tok};
static const int first_size = sizeof(first_set)/sizeof(first_set[0]);

static const Token* sync_set[] = {&array_tok, &integer_tok, &real_tok};
static const int sync_size = sizeof(sync_set)/sizeof(sync_set[0]);

static void synch()
{
    require_sync(sync_set, sync_size, first_set, first_size);
}

// Needs implementing: None
void type()
{
    // Production 4.2
    if (tokens_equal(&array_tok, current_tok, true))
    {
        if (match(&array_tok, true)) // array
            if (match(&lbrac_tok, true)) // [
                if (match(&num_tok, true)) // INT
                    if (match(&dotdot_tok, true)) // ..
                        if (match(&integer_val_tok, true)) // INT
                            if (match(&rbrac_tok, true)) // ]
                                if (match(&of_tok, true)) // of
                                {
                                    standard_type();
                                    return;
                                }
    // Production 4.1
    } else if (tokens_equal(&integer_tok, current_tok, true) // int
               || tokens_equal(&real_tok, current_tok, true)) // real
    {
        standard_type();
        return;
    }

    synch();
}
