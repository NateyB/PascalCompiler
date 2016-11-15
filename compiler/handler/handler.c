#include<stdio.h>

#include "handler.h"
#include "../globals/globals.h"
#include "../tokenizer/tokenizer.h"
#include "../errorHandler/errorHandler.h"

static FILE* listingFile;
static FILE* tokenFile;
static FILE* sourceFile;

static const int TokenLineSpace = 10;
static const int TokenTypeSpace = 15;
static const int TokenAttrSpace = 20;
static const int  TokenLexSpace = 20;

static const int ListingLineSpace = 10;
static const int ListingErrSpace = 50;
static const int ListingLexSpace = 20;

void writeEOFToken()
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE, TokenLexSpace,
            3, "EOF", TokenTypeSpace, FILEEND, TokenAttrSpace, 0);
}

int initializeHandler(const char* sourcePath, const char* resPath,
                        const char* listingPath, const char* tokenPath)
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
        (tokenFile = fopen(tokenPath, "w+")) == NULL)
        return 0;

    for (size_t i = ASSIGNOP; i <= SYNERR; i++) {
        fprintf(tokenFile, "%-5zu%s\n", i, catNames[i]);
    }


    char line[72];
    if (fgets(line, sizeof(line), sourceFile) != NULL)
    {
        updateLine(line);
        fprintf(listingFile, "%s", line);
    } else {
        writeEOFToken();
    }

    fprintf(tokenFile, "%*s%*s%*s%*s\n", TokenLineSpace, "Line",
                                            TokenLexSpace, "Lexeme",
                                            TokenTypeSpace, "Token Type",
                                            TokenAttrSpace, "Token Attribute");

    return 1;
}

void writeError(Token* description)
{
    fprintf(tokenFile, "%*d%*.*s%*d%*d\n", TokenLineSpace, LINE,
            TokenLexSpace, description -> length, &BUFFER[description -> start],
            TokenTypeSpace, description -> category, TokenAttrSpace,
            description -> type);
    fprintf(listingFile, "%*s:%*s%*.*s\n", ListingLineSpace - 1,
            catNames[description -> category], ListingErrSpace,
            lexErrs[description -> type], ListingLexSpace, description -> length,
            &BUFFER[description -> start]);
}

void writeToken(Token* token)
{
    // Don't bother including in the output file.
    if (token -> category == WS || token -> category == NOOP)
        return;

    if (token -> category == LEXERR)
    {
        writeError(token);
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

bool handleToken(Token* token)
{
    writeToken(token);
    if (token -> category == WS && token -> type == 1) // A newline
    {
        char line[72];
        if (fgets(line, sizeof(line), sourceFile) != NULL)
        {
            updateLine(line);
            fprintf(listingFile, "%s", line);
        } else { // Error or end of file (assume the latter)
            LINE++;
            writeEOFToken();
            return false; // Terminate
        }
    }
    return true; // Continue
}
