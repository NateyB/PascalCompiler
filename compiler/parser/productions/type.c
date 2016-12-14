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
LangType type(Token* id_ref)
{
    // Production 4.2
    if (tokens_equal(&array_tok, current_tok, true))
    {
        Token* numI;
        Token* numF;
        if (match(&array_tok, true)) // array
            if (match(&lbrac_tok, true)) // [
                if ((numI = match(&num_tok, false))) // num
                    if (match(&dotdot_tok, true)) // ..
                        if ((numF = match(&num_tok, false))) // num
                            if (match(&rbrac_tok, true)) // ]
                                if (match(&of_tok, true)) // of
                                {
                                    if (type_lookup(numI -> aspect == 0 ? INT : REAL, numF -> aspect == 0 ? INT : REAL, &dotdot_tok) != ERR) {
                                        if (numI -> int_val <= numF -> int_val)
                                            // SEMERR: Value mismatch
                                            ;
                                        id_ref -> array_length = numF -> int_val - numI -> int_val + 1;
                                    }
                                    return convert_to_array(standard_type());
                                }
    // Production 4.1
    } else if (tokens_equal(&integer_tok, current_tok, true) // int
               || tokens_equal(&real_tok, current_tok, true)) // real
    {
        return standard_type();
    }

    synch();
    return ERR;
}
