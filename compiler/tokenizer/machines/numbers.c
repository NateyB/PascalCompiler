#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>

#include "../tokens.h"
#include "machines.h"
#include "../../errorHandler/errorHandler.h"

// Assumes that "str" is valid as an integer.
char* parseNum(LinkedList* chars, bool real)
{
    char* num = malloc((chars -> size + 1) * sizeof(char));
    size_t count = chars -> size;
    num[count--] = 0;
    struct node* node = chars -> head;
    while (node)
    {
        num[count--] = *(char *)node -> data;
        node = node -> next;
    }

    return num;
}

double parseReal(LinkedList* digits)
{
    char* array = parseNum(digits, true);
    double val = strtod(array, NULL);
    free(array);
    return val;
}

int parseInt(LinkedList* digits)
{
    char* array = parseNum(digits, false);
    int val = (int) strtol(array, NULL, 10);
    free(array);
    return val;
}

int intMachine(Token* storage, char* str, int start)
{
    storage -> attribute = NUM;

    bool errored = false;
    int initial = start;

    LinkedList* digits = malloc(sizeof(*digits));
    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    if (start - initial > 10)
    {
        errored = true;
        throw_lex_error(LEXERR, 2, initial, start - initial);
    }
    if (start > initial + 1 && str[initial] == '0')
    {
        errored = true;
        throw_lex_error(LEXERR, 7, initial, start - initial);
    }
    if (errored)
        storage -> attribute = NOOP;
    else if (start > initial) // It's a proper integer!
    {
        storage -> aspect = 0;
        storage -> int_val = parseInt(digits);
    }

    return start;
}

// NOTE: Pay attention to memory stuff here (the linked list takes up space).
int realMachine(Token* storage, char* str, int start)
{
    storage -> attribute = NUM;

    int initial = start;
    bool errored = false;

    int intPart = 0;
    int fracPart = 0;

    LinkedList* digits = malloc(sizeof(*digits));
    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    intPart = start - initial;
    if (intPart == 0) // Not a real. Must start with a digit.
        return initial;

    if (str[start] == '.')
        add(digits, &str[start++], sizeof(char*));
    else // Not a real
        return initial;


    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    fracPart = start - (initial + intPart + 1);

    if (fracPart == 0) // Not a real
        return initial;

    // Now, we check for errors.
    if (intPart > 5)
    {
        throw_lex_error(LEXERR, 3, initial, start - initial);
        errored = true;
    }
    if (fracPart > 5)
    {
        throw_lex_error(LEXERR, 4, initial, start - initial);
        errored = true;
    }
    if (str[initial] == '0' && intPart > 1) // Leading zero!
    {
        throw_lex_error(LEXERR, 8, initial, start - initial);
        errored = true;
    }
    if (str[start - 1] == '0' && fracPart > 1) // Trailing zero!
    {
        throw_lex_error(LEXERR, 9, initial, start - initial);
        errored = true;
    }

    if (errored)
        storage -> attribute = NOOP;
    else
    {
        storage -> aspect = 1;
        storage -> real_val = parseReal(digits);
    }

    return start;
}

int longRealMachine(Token* storage, char* str, int start)
{
    storage -> attribute = NUM;

    int initial = start;
    bool errored = false;

    int intPart = 0;
    int fracPart = 0;
    int expPart = 0;

    LinkedList* digits = malloc(sizeof(*digits));
    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    intPart = start - initial;
    if (intPart == 0) // Not a real. Must start with a digit.
        return initial;

    // REAL part
    if (str[start] == '.')
        add(digits, &str[start++], sizeof(char*));
    else // Not a real
        return initial;


    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    fracPart = start - (initial + intPart + 1);

    if (fracPart == 0) // Not a real
        return initial;


    // LONG REAL part
    int signum = 0;

    if (str[start] == 'E')
        add(digits, &str[start++], sizeof(char*));
    else // Not a long real
        return initial;

    if (str[start] == '+' || str[start] == '-')
    {
        signum++;
        add(digits, &str[start++], sizeof(char*));
    }

    while (isdigit(str[start]))
        add(digits, &str[start++], sizeof(char*));

    expPart = start - (initial + fracPart + intPart + signum + 2);

    if (expPart == 0) // Not a long real
        return initial;


    // Now, we check for errors.
    if (intPart > 5)
    {
        throw_lex_error(LEXERR, 3, initial, start - initial);
        errored = true;
    }
    if (fracPart > 5)
    {
        throw_lex_error(LEXERR, 4, initial, start - initial);
        errored = true;
    }
    if (str[initial] == '0' && intPart > 1) // Leading zero!
    {
        throw_lex_error(LEXERR, 8, initial, start - initial);
        errored = true;
    }
    if (str[start - expPart - 2] == '0' && fracPart > 1) // Trailing zero in real!
    {
        throw_lex_error(LEXERR, 9, initial, start - initial);
        errored = true;
    }
    if (expPart > 2) // Exponent too long!
    {
        throw_lex_error(LEXERR, 5, initial, start - initial);
        errored = true;
    }
    if (str[start - expPart] == '0') // Leading zero in exponent!
    {
        throw_lex_error(LEXERR, 10, initial, start - initial);
        errored = true;
    }

    if (errored)
        storage -> attribute = NOOP;
    else
    {
        storage -> aspect = 1;
        storage -> real_val = parseReal(digits);
    }

    return start;
}
