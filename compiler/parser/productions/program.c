#include "productions.h"
#include "../../tokenizer/tokens.h"

void program(Token* handle)
{
    Token* endOfFile = malloc(sizeof(*endOfFile));
    endOfFile -> category = FILEEND;
    endOfFile -> type = 0;
    Token* syncSet[] = {endOfFile};
    if (handle -> category == CONTROL && handle -> type == 7) // "program"
    {
        if (match(CONTROL, 3, true)) // Successfully matched "end"!
            return;
        else // Uh-oh; a syntax error
            requireSync(syncSet, 1);
    } else { // A syntax error
        requireSync(syncSet, 1);
    }
}
