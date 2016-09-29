#include<stdlib.h>
#include<ctype.h>

#include "processor.h"
#include "machines.h"

int whitespace(Token* storage, char* str, int start)
{
    storage -> category = WS;
    if (isspace(str[start]))
    {
        storage -> type = 0;
        if (str[start] == '\n')
            storage -> type = 1;
        start++;
    }
    return start;
}
