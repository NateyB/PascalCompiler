#include<stdlib.h>
#include<ctype.h>

#include "../tokens.h"
#include "machines.h"

int whitespace(Token* storage, char* str, int start)
{
    storage -> attribute = WS;
    if (isspace(str[start]))
    {
        storage -> aspect = 0;
        if (str[start] == '\n')
            storage -> aspect = 1;
        start++;
    }
    return start;
}
