#include<stdio.h>
#include<stdlib.h>
#include "dataStructures/linkedList/linkedlist.h"
#include "machines/processor.h"

// Global file constants
static const char* catNames[] = {"ASSIGNOP", "FILEEND", "RELOP", "IDRES",
                    "ADDOP", "MULOP", "WS", "ARRAYINIT", "TYPE",
                    "INT", "REAL", "PUNCTUATION", "GROUPING", "LEXERR"};

static const char* lexErrs[] = {"Unrecognized symbol:",
                                "ID length exceeded 10 character maximum:"};

static const char TOKEN_PATH[] = "out/tokens.dat";
static const char RESWORD_PATH[] = "compiler/reswords.dat";

static const int TokenLineSpace = 10;
static const int TokenTypeSpace = 15;
static const int TokenAttrSpace = 20;
static const int  TokenLexSpace = 20;

static const int ListingLineSpace = 10;
static const int ListingErrSpace = 50;
static const int ListingLexSpace = 20;

static int LINE = 1;
static FILE* sourceFile;
static FILE* listingFile;
static FILE* tokenFile;

// Returns 1 on failure, 0 on success.
int init() {
    sourceFile = fopen("tests/fib.pas", "r");
    listingFile = fopen("out/listing.txt", "w+");
    tokenFile = fopen(TOKEN_PATH, "w+");
    FILE* resFile = fopen(RESWORD_PATH, "r");
    initializeTokens(resFile);
    fclose(resFile);

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
    fprintf(tokenFile, "%*s%*s%*s%*s\n", TokenLineSpace, "Line",
                                            TokenTypeSpace, "Token Type",
                                            TokenAttrSpace, "Token Attribute",
                                            TokenLexSpace, "Lexeme");


    return 0;
}

int passError(Token* description, char* line)
{
    fprintf(tokenFile, "%*d%*s%*d%*.*s\n", TokenLineSpace, LINE,
                                            TokenTypeSpace, catNames[description -> category],
                                            TokenAttrSpace, description -> type,
                                            TokenLexSpace, description -> length, &line[description -> start]);
    fprintf(listingFile, "%*s:%*s%*.*s\n", ListingLineSpace - 1, catNames[description -> category],
                                            ListingErrSpace, lexErrs[description -> type],
                                            ListingLexSpace, description -> length, &line[description -> start]);
    return 0;
}

void writeEOFToken()
{
    fprintf(tokenFile, "%*d%*s%*d%*s\n", TokenLineSpace, LINE, TokenTypeSpace, catNames[FILEEND], TokenAttrSpace, 0, TokenLexSpace, "EOF");
}

void updateLine(char* line)
{
    passLine(line);
    fprintf(listingFile, "%*d\t\t%s", ListingLineSpace, LINE, line);
}

void writeToken(Token* token, char* line)
{
    if (token -> category == WS) // Don't bother including in the output file.
        return;


    fprintf(tokenFile, "%*d%*s", TokenLineSpace, LINE, TokenTypeSpace, catNames[token -> category]);
    switch (token -> category) {
        case REAL:
            fprintf(tokenFile, "%*f", TokenAttrSpace, token -> val);
            break;

        case IDRES:
            fprintf(tokenFile, "%*p", TokenAttrSpace, token -> id);
            break;

        default:
            fprintf(tokenFile, "%*d", TokenAttrSpace, token -> type);
            break;
    }
    fprintf(tokenFile, "%*.*s\n", TokenLexSpace, token -> length, &line[token -> start]);
}

int run()
{
    char line[72];
    if (fgets(line, sizeof(line), sourceFile) != NULL)
        updateLine(line);
    Token* next = malloc(sizeof(*next));
    while ((next = getNextToken()))
    {
        if (next -> category == WS && next -> type == 1)
        {
            LINE++;
            if (fgets(line, sizeof(line), sourceFile) != NULL)
            {
                updateLine(line);
            } else { // Error or end of file (assume the latter)
                writeEOFToken();
                return 0;
            }
        }
        writeToken(next, line);
    }
    return 1;
}

int main() {
    if (init() == 0) {
        if (run() != 0)
            fprintf(stderr, "%s\n", "Run failed. Could not terminate properly.");
    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in lexical analyzer.");
    }
    fclose(listingFile);
    return 0;
}
