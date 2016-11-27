#include<string.h>
#include<stdlib.h>
#include "errorHandler.h"

static LinkedList* errorList;

const char* lexErrs[] = {"Unrecognized symbol:",
                         "ID length exceeded 10 characters:",
                         "Int length exceeded 10 characters:",
                         "Integer part of real exceeded 5 characters:",
                         "Fractional part of real exceeded 5 characters:",
                         "Exponent part of long real exceeded 2 characters:",
                         "Missing exponent part of long real:",
                         "Leading 0 in int:",
                         "Excessive leading 0 in real:",
                         "Trailing 0 in real:",
                         "Leading 0 in exponent:",
                         "Attempt to use real exponent:"};

const char* synErrs[] = {"NOOP", "A", "F", "R", "I"};

int initializeErrorHandler()
{
    errorList = malloc(sizeof(*errorList));
    return errorList != NULL;
}


void throwError(enum TokenType category, int type, int start, int length)
{
    Token* errToken = malloc(sizeof(*errToken));
    errToken -> category = category;
    errToken -> type = type;
    errToken -> start = start;
    errToken -> length = length;

    add(errorList, errToken, sizeof(*errToken));
}

Token* getNextErrorToken()
{
    if (errorList -> size > 0)
        return (Token *) pop(errorList);

    return NULL;
}
