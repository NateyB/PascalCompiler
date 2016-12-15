#include "../tokens.h"
#include "machines.h"

int mulop(Token* storage, char* str, int start)
{
    storage -> attribute = MULOP;
    if (str[start] == '*')
    {
        storage -> aspect = 0;
        start++;
    } else if (str[start] == '/')
    {
        storage -> aspect = 1;
        start++;
    }

    return start;
}
