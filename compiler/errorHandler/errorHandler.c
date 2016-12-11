//#include<string.h>
#include<stdlib.h>
#include<string.h>

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

char* synErr;

int initializeErrorHandler()
{
    errorList = malloc(sizeof(*errorList));
    return errorList != NULL;
}

void throw_syn_error(Token* received, const Token** expected, int exp_size)
{
    // Generate token
    Token* errToken = malloc(sizeof(*errToken));
    errToken -> attribute = SYNERR;
    errToken -> aspect = 0;
    errToken -> start = received -> start;
    errToken -> length = received -> length;

    add(errorList, errToken, sizeof(*errToken));

    // Generate error message
    // Calculate space needed
    int size = strlen("Found ''; expected ");
    size += strlen(getLexFromToken(received, true));
    for (int i = exp_size - 1; i >= 0; i--) {
        size += strlen("''");
        size += strlen(getLexFromToken(expected[i], expected[i] -> start));
        if (i > 0)
            size += strlen(", ");
    }
    size += strlen(" instead.");
    size += 1; // Null terminator

    synErr = malloc(sizeof(*synErr) * size);
    synErr[size - 1] = '\0';
    strcpy(synErr, "Found '");
    int current = 7;
    int len = strlen(getLexFromToken(received, true));
    strcpy(&synErr[current], getLexFromToken(received, true));
    current += len;
    strcpy(&synErr[current], "'; expected ");
    current += 12;
    for (int i = exp_size - 1; i >= 0; i--) {
        strcpy(&synErr[current], "'");
        current += 1;
        len = strlen(getLexFromToken(expected[i], expected[i] -> start));
        strcpy(&synErr[current], getLexFromToken(expected[i], expected[i] -> start));
        current += len;
        strcpy(&synErr[current], "'");
        current += 1;
        if (i > 0) {
            strcpy(&synErr[current], ", ");
            current += 2;
        }
    }
    strcpy(&synErr[current], " instead.");
}

void throw_lex_error(enum TokenType attribute, int aspect, int start, int length)
{
    Token* errToken = malloc(sizeof(*errToken));
    errToken -> attribute = attribute;
    errToken -> aspect = aspect;
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
