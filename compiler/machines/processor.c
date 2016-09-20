#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

#include "processor.h"
#include "../dataStructures/linkedList/linkedlist.h"
/*

RELOP       (<(=|>)?)|=|>=?
ASSIGNOP    :=
IDRES       {letter}({letter}|{digit})*
WS          {whitespace}+
LONGREAL    {digit}+\.{digit}+\E(\+|\-)?{digit}+
REAL        {digit}+\.{digit}+
INT         {digit}+
UNREC       [^\n \t]
*/

static const char TOKEN_PATH[] = "out/tokens.dat";
static int LINE = 1;

// Begin machine listings

/**************************************************************
*                           ID/RES                            *
***************************************************************/
// The constant file paths.
static const char RESWORD_PATH[] = "compiler/reswords.dat";

// The tables & arrays and stuff
char** reservedWords;
int numReserved;
LinkedList* symbolTable;

// Initialization stuff
int initResWords(FILE* resFile)
{
    static const int length = 11;
    LinkedList* resWords = malloc(sizeof(*resWords));
    char word[length] = {0};
    while (fgets(word, length, resFile))
    {
        word[strcspn(word, "\n")] = 0;
        numReserved = add(resWords, &word, length*sizeof(char));
    }
    reservedWords = malloc(numReserved*sizeof(char*));
    struct node* node = resWords -> head;

    for (size_t i = 0; i < numReserved; i++) {
        reservedWords[i] = (char *) node -> data;
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

char* knownID(char* word)
{
    // Check the reserved words table for a match first
    for (size_t i = 0; i < numReserved; i++) {
        if (!reservedWords[i] || strcmp(reservedWords[i], word) == 0) // Match
            return reservedWords[i];
    }

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

// TODO Sanitize input
int idres(Token* storage, char* str, int start)
{
    LinkedList* id = malloc(sizeof(*id));
    storage -> category = IDRES;
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

        char* address = 0;

        if ((address = knownID(name)))// || ((address = inList(reservedWords, name))))
        {
            storage -> id = address;
        } else
        {
            add(symbolTable, name, (wordSize + 1)*sizeof(char));
            storage -> id = name;
        }

    }
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
    char next = str[start];
    while (isspace(next))
    {
        if (next == '\n')
            LINE++;
        start++;
        next = str[start];
    }
    return start;
}

// // This is weird witchcraft. Will deal with later.
// int longreal(Token* storage, char* str, int start)
// {
//     // We'll have to backtrack if there's no E!
//     int initial = start;
//
//     int sign = 1;
//     char next = str[start];
//     if (isdigit(x))
//     {
//
//     }
//     else if (next == '-')
//         sign = -1;
//     else if (next == '+')
//         sign = 1;
//     else // Not a number.
//         return initial;
//
//
// }

// TODO: Figure out how to handle the mulop/addop keywords; also, spaces.
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

        case 'o':
            if (str[start + 1] == 'r' && isspace(str[start + 2]))
            {
                storage -> type = 2;
                start = start + 2;
                return start;
            }
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
    } else if (strncmp(&str[start], "div ", 4) == 0)
    {
        storage -> type = 2;
        start += 3;
    } else if (strncmp(&str[start], "mod ", 4) == 0)
    {
        storage -> type = 3;
        start += 3;
    } else if (strncmp(&str[start], "and ", 4) == 0)
    {
        storage -> type = 4;
        start += 3;
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
        storage -> category = ARRAYINIT;
        storage -> type = 0;
        start += 2;
    } else if (str[start] == ':'){
        storage -> category = TYPE;
        storage -> type = 0;
        start++;
    } else if (str[start] == ',')
    {
        storage -> category = PUNCTUATION;
        storage -> type = 0;
        start++;
    } else if (str[start] == ';')
    {
        storage -> category = PUNCTUATION;
        storage -> type = 1;
        start++;
    } else if (str[start] == '.')
    {
        storage -> category = PUNCTUATION;
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
    storage -> category = GROUPING;
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
    bool real = false;
    int sign = 1;
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
        add(digits, &str[start], sizeof(char*));
        start++;
    }
    if (str[start] == '.' && isdigit(str[start + 1])) // Match the real
    {
        add(digits,&str[start], sizeof(char*));
        real = true;
        start++;
        while (isdigit(str[start])) // The fraction part of the decimal
        {
            add(digits, &str[start], sizeof(char*));
            start++;
        }
    }
    if (str[start] == 'E') // Match the long real
    {
        add(digits, &str[start], sizeof(char*));
        real = true;
        start++;
        while (isdigit(str[start])) // The exponent part (if applicable)
        {
            add(digits, &str[start], sizeof(char*));
            start++;
        }
    }
    if (real)
    {
        storage -> val = parseReal(digits);
        storage -> category = REAL;
    } else
    {
        storage -> type = parseInt(digits);
        storage -> category = INT;
    }

    return start;
}

// The processing
typedef int (*machine)(Token*, char*, int);
const static machine machines[] = {whitespace, idres, numMachine, grouping, catchall, relop, addop, mulop};

bool initialized = false;
int length = 0;
char* buffer = 0;
int start;

Token* getNextToken()
{
    if (initialized) {
        Token* current = malloc(sizeof(*current));
        if (start == length - 1)
        {
            current -> category = FILEEND;
            current -> type = 0;
            // free(buffer);
            return current;
        }
        int end;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
            current -> type = 0;
            end = (*machines[i])(current, buffer, start);
            if (end > start) {
                start = end;
                return current;
            }
        }
        current -> category = UNREC;
        current -> type = buffer[start];
        start++;
        return current;
    } else {
        fprintf(stderr, "%s\n", "Processor not initialized. Aborting.");
        return NULL;
    }
}

int initializeTokens(FILE* sourceFile, FILE* resFile)
{
    if (sourceFile) {
        initResWords(resFile);
        initSymbolTable();
        // Get the file's size
        fseek(sourceFile, 0, SEEK_END);
        long size = ftell(sourceFile);
        fseek(sourceFile, 0, SEEK_SET);

        buffer = (char*) malloc((size + 1)*sizeof(char));
        if (buffer)
        {
            fread(buffer, 1, size + 1, sourceFile);
            buffer[size] = 0;
            length = size;
            initialized = true;
            start = 0;
            return 0;
        } else {
            fprintf(stderr, "%s\n", "Memory for buffer not allocated properly!");
        }
    } else {
        fprintf(stderr, "%s\n", "Source file for analyzer null!");
    }
    return 1;
}


// void printWords(LinkedList* list) // TODO DELETE OR MOVE
// {
//     struct node* node = list->head;
//     while (node)
//     {
//         printf("Printing symbol: %s\n", (char *) node->data);
//         node = node -> next;
//     }
// }
