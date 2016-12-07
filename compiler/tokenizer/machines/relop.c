#include "../tokens.h"
#include "machines.h"

int relop(Token* storage, char* str, int start)
{
    storage -> attribute = RELOP;
    char next = str[start];
    switch (next) {
        case '<':
            start++;
            if (str[start] == '=')
            {
                storage -> aspect = 1;
                start++;
            } else if (str[start] == '>')
            {
                storage -> aspect = 5;
                start++;
            } else {
                storage -> aspect = 0;
            }
            break;

        case '=':
            start++;
            storage -> aspect = 2;
            break;

        case '>':
            start++;
            if (str[start] == '=')
            {
                storage -> aspect = 4;
                start++;
            } else {
                storage -> aspect = 3;
            }
            break;

        default: break; // Do not increment; continue on to the next machine.
    }

    return start;
}
