#include "../tokens.h"
#include "machines.h"

int grouping(Token* storage, char* str, int start)
{
    storage -> attribute = GROUP;
    switch (str[start])
    {
        case '(':
            storage -> aspect = 0;
            start++;
            break;

        case ')':
            storage -> aspect = 1;
            start++;
            break;

        case '[':
            storage -> aspect = 2;
            start++;
            break;

        case ']':
            storage -> aspect = 3;
            start++;
            break;

        default:
            break;
    }

    return start;
}
