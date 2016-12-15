#include "../tokens.h"
#include "machines.h"

int addop(Token* storage, char* str, int start)
{
    storage -> attribute = ADDOP;
    switch (str[start])
    {
        case '+':
            storage -> aspect = 0;
            start++;
            return start;

        case '-':
            storage -> aspect = 1;
            start++;
            return start;

        default: break;
    }

    return start;
}
