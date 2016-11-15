#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

static const Token endOfFile = {
    FILEEND, false, 0, 0
};

static const Token* syncSet[] = {&endOfFile};

void program()
{
    // Program -> production 1
    if (match(CONTROL, 7, true))
        if (match(ID, 0, false))
            if (match(GROUP, 0, true)) // Open paren
            {
                id_list();
                if match(GROUP, 1, true) // Close paren; continue
        if (match(CONTROL, 3, true)) // Successfully matched "end"!
            return;
        else // Uh-oh; a syntax error
            requireSync(syncSet, 1);
    requireSync(syncSet, 1);
}
