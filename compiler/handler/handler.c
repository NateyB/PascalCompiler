#include<stdio.h>

#include "handler.h"
#include "../globals/globals.h"
#include "../tokenizer/tokenizer.h"
#include "../errorHandler/errorHandler.h"

static FILE* listingFile;
static FILE* tokenFile;
static FILE* sourceFile;
static FILE* memFile;

static const int TokenLineSpace = 10;
static const int TokenTypeSpace = 20;
static const int TokenAttrSpace = 20;
static const int  TokenLexSpace = 20;

static const int ListingLineSpace = 7;
static const int ListingErrSpace = 50;
static const int ListingLexSpace = 20;

static const int MemNameSpace = 10;
static const int MemValSpace = 20;

void writeEOFToken()
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE, TokenLexSpace,
            3, "EOF", TokenTypeSpace, FILEEND, TokenAttrSpace, 0);
}

int initializeHandler(const char* sourcePath, const char* resPath,
                        const char* listingPath, const char* tokenPath,
                        const char* memPath)
{
    if ((sourceFile = fopen(sourcePath, "r")) == NULL)
    {
        fprintf(stderr, "%s\n", "Source was null?");
        return 0;
    }

    FILE* resFile = fopen(resPath, "r");
    initializeTokens(resFile);
    fclose(resFile);

    if ((listingFile = fopen(listingPath, "w+")) == NULL ||
        (tokenFile = fopen(tokenPath, "w+")) == NULL ||
        (memFile = fopen(memPath, "w+")) == NULL)
        return 0;

    for (size_t i = FILEEND; i <= SEMERR; i++) {
        fprintf(tokenFile, "%-5zu%s\n", i, catNames[i]);
    }


    char line[72];
    if (fgets(line, sizeof(line), sourceFile) != NULL)
    {
        updateLine(line);
        fprintf(listingFile, "%*d\t%s", ListingLineSpace, LINE, line);
    } else {
        writeEOFToken();
    }

    fprintf(tokenFile, "%*s%*s%*s%*s\n", TokenLineSpace, "Line",
                                            TokenLexSpace, "Lexeme",
                                            TokenAttrSpace, "Token Attribute",
                                            TokenTypeSpace, "Token Type");

    fprintf(memFile, "%*s%*s\n", MemNameSpace, "ID",
                MemValSpace, "Memory Offset");
    return 1;
}

void outputWidth(char* lex, int width) {
    fprintf(memFile, "%*s%*d\n", MemNameSpace, lex, MemValSpace, width);
}

void writeError(Token* description)
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE,
            TokenLexSpace, description -> length, &BUFFER[description -> start],
            TokenTypeSpace, description -> attribute, TokenAttrSpace,
            description -> aspect);
    if (description -> attribute == LEXERR)
        fprintf(listingFile, "%*s:%*s%*.*s\n", ListingLineSpace - 1,
                catNames[description -> attribute], ListingErrSpace,
                lexErrs[description -> aspect], ListingLexSpace,
                description -> length, &BUFFER[description -> start]);
    else if (description -> attribute == SYNERR)
        fprintf(listingFile, "%*s: %s\n", ListingLineSpace - 1,
                catNames[description -> attribute], synErr);
}

void writeToken(Token* token)
{
    // Don't bother including in the output file.
    if (token -> attribute == WS || token -> attribute == NOOP)
        return;

    if (token -> attribute >= LEXERR)
    {
        writeError(token);
        return;
    }


    fprintf(tokenFile, "%*d%*.*s%*d", TokenLineSpace, LINE, TokenLexSpace,
            token -> length, &BUFFER[token -> start], TokenTypeSpace,
            token -> attribute);
    switch (token -> attribute) {
        case ID:
            fprintf(tokenFile, "%*p", TokenAttrSpace, token -> id);
            break;

        default:
            fprintf(tokenFile, "%*d", TokenAttrSpace, token -> aspect);
            break;
    }
    fprintf(tokenFile, "\n");
}

bool handleToken(Token* token)
{
    writeToken(token);
    if (token -> attribute == WS && token -> aspect == 1) // A newline
    {
        char line[72];
        if (fgets(line, sizeof(line), sourceFile) != NULL)
        {
            updateLine(line);
            fprintf(listingFile, "%*d\t%s", ListingLineSpace, LINE, line);
        } else { // Error or end of file (assume the latter)
            LINE++;
            writeEOFToken();
            return false; // Terminate
        }
    }
    return true; // Continue
}
