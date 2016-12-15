#include<string.h>

#include "../tokens.h"
#include "machines.h"

int catchall(Token* storage, char* str, int start)
{
    if (strncmp(&str[start], ":=", 2) == 0)
    {
        storage -> attribute = ASSIGNOP;
        storage -> aspect = 0;
        start += 2;
    } else if (strncmp(&str[start], "..", 2) == 0)
    {
        storage -> attribute = ARRAY;
        storage -> aspect = 1;
        start += 2;
    } else if (str[start] == ':'){
        storage -> attribute = TYPE;
        storage -> aspect = 0;
        start++;
    } else if (str[start] == ',')
    {
        storage -> attribute = PUNC;
        storage -> aspect = 0;
        start++;
    } else if (str[start] == ';')
    {
        storage -> attribute = PUNC;
        storage -> aspect = 1;
        start++;
    } else if (str[start] == '.')
    {
        storage -> attribute = PUNC;
        storage -> aspect = 2;
        start++;
    }

    return start;
}
