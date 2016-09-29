#include "processor.h"
#include "machines.h"

int addop(Token* storage, char* str, int start)
{
    storage -> category = ADDOP;
    switch (str[start])
    {
        case '+':
            storage -> type = 0;
            start++;
            return start;

        case '-':
            storage -> type = 1;
            start++;
            return start;

        default: break;
    }

    return start;
}
