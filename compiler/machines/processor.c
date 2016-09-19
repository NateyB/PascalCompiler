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

/**************************************************************
*                           ID RES                            *
***************************************************************/
// The constant file paths.
static const char RESWORD_PATH[] = "compiler/reswords.dat";

// The tables & arrays and stuff
char** reservedWords;
int numReserved;
LinkedList* symbolTable;

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
        }

    }
    return start;
}

// Begin machine listings
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



void printWords(LinkedList* list) // TODO DELETE OR MOVE
{
    struct node* node = list->head;
    while (node)
    {
        printf("Printing symbol: %s\n", (char *) node->data);
        node = node -> next;
    }
}


// The processing
typedef int (*machine)(Token*, char*, int);
const static machine machines[] = {relop, idres};

bool initialized = false;
int length = 0;
char* buffer = 0;
int start;

Token* getNextToken()
{
    if (initialized) {
        if (start == length - 1)
        {
            printf("%s\n", "EOF reached.");
            free(buffer);
            return NULL;
        }
        Token* current = malloc(sizeof(*current));
        int end;
        for (int i = 0; i < sizeof(machines)/sizeof(machine); i++)
        {
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

int initializeTokens(FILE* sourceFile, FILE* resFile)
{
    if (sourceFile) {
        initResWords(resFile);
        symbolTable = malloc(sizeof(*symbolTable));
        symbolTable -> head = 0;
        // Get a file's size
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
