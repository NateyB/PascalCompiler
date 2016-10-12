#include<stdio.h>
#include<stdlib.h>
#include "dataStructures/linkedList/linkedlist.h"
#include "errorHandler/errorHandler.h"
#include "tokenizer/tokenizer.h"
#include "globals/globals.h"

// Global file constants
static const char TOKEN_PATH[] = "out/tokens.dat";
static const char LISTING_PATH[] = "out/listing.txt";
static const char RESWORD_PATH[] = "compiler/data/reswords.dat";
static const char* TEST_PATH;

static const int TokenLineSpace = 10;
static const int TokenTypeSpace = 15;
static const int TokenAttrSpace = 20;
static const int  TokenLexSpace = 20;

static const int ListingLineSpace = 10;
static const int ListingErrSpace = 50;
static const int ListingLexSpace = 20;

static FILE* sourceFile;
static FILE* listingFile;
static FILE* tokenFile;

// Returns 1 on failure, 0 on success.
int init() {
    sourceFile = fopen(TEST_PATH, "r");
    listingFile = fopen(LISTING_PATH, "w+");
    tokenFile = fopen(TOKEN_PATH, "w+");
    FILE* resFile = fopen(RESWORD_PATH, "r");
    initializeTokens(resFile);
    fclose(resFile);
    initializeGlobals();
    initializeErrorHandler();

    if (sourceFile == NULL)
    {
        fprintf(stderr, "%s\n", "Source was null?");
        fclose(listingFile);
        return 1;
    }
    if (tokenFile == NULL)
    {
        fprintf(stderr, "%s\n", "Token file could not be created.");
        fclose(listingFile);
        return 1;
    }
    for (size_t i = ASSIGNOP; i <= SYNERR; i++) {
        fprintf(tokenFile, "%-5zu%s\n", i, catNames[i]);
    }
    fprintf(tokenFile, "%*s%*s%*s%*s\n", TokenLineSpace, "Line",
                                            TokenLexSpace, "Lexeme",
                                            TokenTypeSpace, "Token Type",
                                            TokenAttrSpace, "Token Attribute");


    return 0;
}

int passError(Token* description)
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE,
            TokenLexSpace, description -> length, &BUFFER[description -> start],
            TokenTypeSpace, description -> category, TokenAttrSpace,
            description -> type);
    fprintf(listingFile, "%*s:%*s%*.*s\n", ListingLineSpace - 1,
            catNames[description -> category], ListingErrSpace,
            lexErrs[description -> type], ListingLexSpace, description -> length,
            &BUFFER[description -> start]);
    return 0;
}

void writeEOFToken()
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE, TokenLexSpace,
            3, "EOF", TokenTypeSpace, FILEEND, TokenAttrSpace, 0);
}

void writeToken(Token* token)
{
    if (token -> category == WS || token -> category == NOOP) // Don't bother including in the output file.
        return;
    if (token -> category == LEXERR) // For catching the unrecognized symbol error
    {
        passError(token);
        return;
    }


    fprintf(tokenFile, "%*d%*.*s%*d", TokenLineSpace, LINE, TokenLexSpace,
            token -> length, &BUFFER[token -> start], TokenTypeSpace,
            token -> category);
    switch (token -> category) {
        case REAL:
            fprintf(tokenFile, "%*f", TokenAttrSpace, token -> val);
            break;

        case ID:
            fprintf(tokenFile, "%*p", TokenAttrSpace, token -> id);
            break;

        default:
            fprintf(tokenFile, "%*d", TokenAttrSpace, token -> type);
            break;
    }
    fprintf(tokenFile, "\n");
}

void handleToken(Token* token)
{
    writeToken(token);
}

int run()
{
    char line[72];
    if (fgets(line, sizeof(line), sourceFile) != NULL)
    {
        updateLine(line);
        fprintf(listingFile, "%s", line);
    }

    Token* next = malloc(sizeof(*next));
    while ((next = getNextToken()))
    {
        handleToken(next);
        if (next -> category == WS && next -> type == 1)
        {
            if (fgets(line, sizeof(line), sourceFile) != NULL)
            {
                updateLine(line);
                fprintf(listingFile, "%s", line);
            } else { // Error or end of file (assume the latter)
                LINE++;
                writeEOFToken();
                return 0;
            }
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", "Expected exactly one file to compile!");
    } else {
        TEST_PATH = argv[1];
    }
    if (init() == 0) {
        if (run() != 0)
            fprintf(stderr, "%s\n", "Run failed. Could not terminate properly.");
    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in tokenizer.");
    }
    fclose(listingFile);
    return 0;
}
