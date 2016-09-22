#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

#include "processor.h"
#include "../dataStructures/linkedList/linkedlist.h"
#include "../lexicalanalyzer.h"

const char* catNames[] = {"ASSIGNOP", "FILEEND", "RELOP", "ID", "CONTROL",
                    "ADDOP", "MULOP", "WS", "ARRAY", "TYPE", "VAR",
                    "INT", "REAL", "PUNC", "GROUP", "INVERSE", "LEXERR"};

static char* buffer;
// Begin machine listings

/* TODO Include the following errors:
 * 0. Symbol not recognized √
 * 1. ID too long (10 char maximum) √
 * 2. Int too long (10 digit maximum) √
 * 3. Int part of real too long (5 digits maximum) √
 * 4. Fraction part of real too long (5 digits maximum) √
 * 5. Exponent part of real too long (2 digits maximum) √
 * 6. Missing exponent on real √
 * 7. Leading 0 for ints (when not equal to 0) √
 * 8. Leading 0 for reals (when not 0.x) √
 * 9. Trailing 0 for reals √
 *10. Leading 0 for exponent. √
*/
/**************************************************************
*                           ID/RES                            *
***************************************************************/
int getIndex(const char** array, size_t arr_size, char* item)
{
    while (arr_size > 0)
    {
        if (strcmp(array[arr_size - 1], item) == 0)
            return arr_size - 1;
        arr_size--;
    }
    return -1;
}


// The tables & arrays and stuff
char** reservedWords;
int numReserved;
static enum TokenType* categories;
static int* attributes;

LinkedList* symbolTable;

static LinkedList* errorList;
static struct node* errorHead;

void throwError(enum TokenType category, int type, int start, int length)
{
    Token* errToken = malloc(sizeof(*errToken));
    errToken -> category = category;
    errToken -> type = type;
    errToken -> start = start;
    errToken -> length = length;

    add(errorList, errToken, sizeof(*errToken));
}

// Initialization stuff
int initResWords(FILE* resFile)
{
    static const int length = 11;
    LinkedList* resWords = malloc(sizeof(*resWords));
    LinkedList* cats = malloc(sizeof(*cats));
    LinkedList* attrs = malloc(sizeof(*attrs));

    char word[length] = {0};
    char category[length] = {0};
    int attr = 0;
    //while (fgets(word, length, resFile))
    while (true)
    {
        fscanf(resFile, "%s", word);
        if (feof(resFile))
            break;
        fscanf(resFile, "%s", category); // The actual name.
        fscanf(resFile, "%d", &attr);
        numReserved = add(resWords, &word, length*sizeof(char));
        add(cats, &category, length*sizeof(char));
        add(attrs, &attr, sizeof(int));
    }

    // Initialize the lexeme table
    reservedWords = malloc(numReserved*sizeof(char*));
    struct node* node = resWords -> head;

    for (size_t i = 0; i < numReserved; i++) {
        reservedWords[i] = (char *) node -> data;
        node = node -> next;
    }

    // Initialize the category table
    categories = malloc(numReserved*sizeof(enum TokenType));
    node = cats -> head;

    for (size_t i = 0; i < numReserved; i++) {
        categories[i] = (enum TokenType) getIndex(catNames, sizeof(catNames)/sizeof(char*), (char *) node -> data);
        node = node -> next;
    }

    // Initialize the attribute table
    attributes = malloc(numReserved*sizeof(int));
    node = attrs -> head;

    for (size_t i = 0; i < numReserved; i++) {
        attributes[i] = *(int *) node -> data;
        node = node -> next;
    }


    return 0;
}

int initSymbolTable()
{
    symbolTable = malloc(sizeof(*symbolTable));
    symbolTable -> head = 0;
    return 0;
}

int isReserved(char* word)
{
    // Check the reserved words table for a match first
    for (size_t i = 0; i < numReserved; i++) {
        if (!reservedWords[i] || strcmp(reservedWords[i], word) == 0) // Match
            return i;
    }

    return -1;
}

char* knownID(char* word)
{
    // Then check the symbol table
    struct node* node = symbolTable -> head;
    while (node)
    {
        if (strcmp(node -> data, word) == 0) // Match
            return (char *)(node -> data);
        node = node -> next;
    }

    return NULL;
}

int idres(Token* storage, char* str, int start)
{
    int initial = start;
    LinkedList* id = malloc(sizeof(*id));
    storage -> category = ID;
    storage -> type = 0;
    char next = str[start];
    if (isalpha(next)) // Can actually be an id/reserved
    {
        size_t wordSize = 0;
        do
        {
            wordSize = add(id, &next, sizeof(char));
            start++;
            next = str[start];
        } while(isalpha(next) || isdigit(next)); // Match ID

        char* name = malloc((wordSize + 1)*sizeof(char)); // The string of the id name
        name[wordSize] = '\0';
        struct node* node = id -> head;
        for (size_t i = 0; i < wordSize; i++) {
            name[wordSize - i - 1] = *(char *)(node -> data);
            node = node -> next;
        }

        int index = -1;
        char* address = 0;
        if ((index = isReserved(name)) >= 0)
        { // It's a reserved word!
            storage -> category = categories[index];
            storage -> type = attributes[index];
        }
        else if ((address = knownID(name)))
        {
            storage -> id = address;
        } else
        {
            add(symbolTable, name, (wordSize + 1)*sizeof(char));
            storage -> id = name;
        }

    }
    if (start - initial > 10) // ID Too long err
        throwError(LEXERR, 1, initial, start - initial);
    return start;
}
/**************************************************************
*                         END ID/RES                          *
***************************************************************/


int relop(Token* storage, char* str, int start)
{
    storage -> category = RELOP;
    char next = str[start];
    switch (next) {
        case '<':
            start++;
            if (str[start] == '=')
            {
                storage -> type = 1;
                start++;
            } else if (str[start] == '>')
            {
                storage -> type = 5;
                start++;
            } else {
                storage -> type = 0;
            }
            break;

        case '=':
            start++;
            storage -> type = 2;
            break;

        case '>':
            start++;
            if (str[start] == '=')
            {
                storage -> type = 4;
                start++;
            } else {
                storage -> type = 3;
            }
            break;

        default: break; // Do not increment; continue on to the next machine.
    }

    return start;
}

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

int mulop(Token* storage, char* str, int start)
{
    storage -> category = MULOP;
    if (str[start] == '*')
    {
        storage -> type = 0;
        start++;
    } else if (str[start] == '/')
    {
        storage -> type = 1;
        start++;
    }

    return start;
}


int catchall(Token* storage, char* str, int start)
{
    if (strncmp(&str[start], ":=", 2) == 0)
    {
        storage -> category = ASSIGNOP;
        storage -> type = 0;
        start += 2;
    } else if (strncmp(&str[start], "..", 2) == 0)
    {
        storage -> category = ARRAY;
        storage -> type = 1;
        start += 2;
    } else if (str[start] == ':'){
        storage -> category = TYPE;
        storage -> type = 0;
        start++;
    } else if (str[start] == ',')
    {
        storage -> category = PUNC;
        storage -> type = 0;
        start++;
    } else if (str[start] == ';')
    {
        storage -> category = PUNC;
        storage -> type = 1;
        start++;
    } else if (str[start] == '.')
    {
        storage -> category = PUNC;
        storage -> type = 2;
        start++;
    }

    return start;
}

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

int grouping(Token* storage, char* str, int start)
{
    storage -> category = GROUP;
    switch (str[start])
    {
        case '(':
            storage -> type = 0;
            start++;
            break;

        case ')':
            storage -> type = 1;
            start++;
            break;

        case '[':
            storage -> type = 2;
            start++;
            break;

        case ']':
            storage -> type = 3;
            start++;
            break;

        default:
            break;
    }

    return start;
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

int numMachine(Token* storage, char* str, int start)
{
    int initial = start; // For keeping track
    bool real = false;
    bool hasE = false;
    bool started = false;
    bool leadZero = false;
    bool expLeadZero = false;
    bool trailZero = false;

    int sign = 1;
    int intLen = 0;
    int fractionLen = 0;
    int expLen = 0;

    if (str[start] == '-' && isdigit(str[start + 1]))
    {
        start++;
        sign = -1;
    }
    else if (str[start] == '+' && isdigit(str[start + 1]))
        start++;

    LinkedList* digits = malloc(sizeof(*digits));
    while (isdigit(str[start])) // Match the beginning integer
    {
        if (str[start] == '0' && !started)
            leadZero = true;
        add(digits, &str[start], sizeof(char*));
        started = true;
        start++;
        intLen++;
    }
    if (str[start] == '.' && isdigit(str[start + 1])) // Match the real
    {
        add(digits,&str[start], sizeof(char*));
        real = true;
        start++;
        while (isdigit(str[start])) // The fraction part of the decimal
        {
            add(digits, &str[start], sizeof(char*));
            if (str[start] == '0')
                trailZero = true;
            else
                trailZero = false;
            start++;
            fractionLen++;
        }
    }
    if (str[start] == 'E') // Match the long real
    {
        hasE = true;
        add(digits, &str[start], sizeof(char*));
        real = true;
        bool initialRun = true;
        start++;
        while (isdigit(str[start])) // The exponent part (if applicable)
        {
            if (str[start] == '0' && initialRun)
                expLeadZero = true;
            initialRun = false;
            add(digits, &str[start], sizeof(char*));
            start++;
            expLen++;
        }

    }
    if (real)
    {
        if (intLen > 5) // Too long.
            throwError(LEXERR, 3, initial, start - initial);
        if (fractionLen > 5) // Nope. Too long.
            throwError(LEXERR, 4, initial, start - initial);
        if (expLen > 2) // Too long again.
            throwError(LEXERR, 5, initial, start - initial);
        if (hasE && expLen == 0) // 3.4E what???
            throwError(LEXERR, 6, initial, start - initial);

        storage -> val = parseReal(digits);

        if (leadZero && intLen > 1) // Leading zero error!
            throwError(LEXERR, 8, initial, start - initial);
        if (expLeadZero)
            throwError(LEXERR, 10, initial, start - initial);
        if (trailZero) // Trailing zero error!
            throwError(LEXERR, 9, initial, start - initial);
        storage -> category = REAL;
    } else
    {
        if (intLen > 10)
            throwError(LEXERR, 2, initial, start - initial);
        storage -> type = parseInt(digits);
        if (leadZero && !(storage -> type == 0))
            throwError(LEXERR, 7, initial, start - initial);
        storage -> category = INT;
    }

    return start;
}

// The processing
typedef int (*machine)(Token*, char*, int);
const static machine machines[] = {whitespace, idres, numMachine, grouping, catchall, relop, addop, mulop};

bool initialized = false;
int start;

int passLine(char* newLine)
{
    strcpy(buffer, newLine);
    start = 0;
    initialized = true;
    return 0;
}

Token* getNextToken()
{
    if (initialized) {
        while (errorList -> size > 0)
            passError((Token *) pop(errorList), buffer);

        Token* current = malloc(sizeof(*current));
        int end;
        current -> start = start;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
            current -> type = 0;
            end = (*machines[i])(current, buffer, start);
            if (end > start) {
                current -> length = end - start;
                start = end;
                return current;
            }
        }

        // Unrecognized symbol error. This error is manual because it takes
        // the place of a lexeme, rather than being processed during one.
        current -> category = LEXERR;
        current -> type = 0;
        current -> start = start;
        current -> length = 1;
        start++;
        return current;
    } else {
        fprintf(stderr, "%s\n", "Processor not initialized. Aborting.");
        return NULL;
    }
}

int initializeTokens(FILE* resFile)
{
    if (resFile) {
        buffer = malloc(sizeof(char)*73);
        initResWords(resFile);
        initSymbolTable();
        errorList = malloc(sizeof(*errorList));
    } else {
        fprintf(stderr, "%s\n", "Reserved words file for analyzer null!");
    }
    return 1;
}
