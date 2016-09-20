#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataStructures/linkedList/linkedlist.h"
#include "machines/processor.h"

enum ListingType {LNNUM, ERROR};
const static char* catNames[] = {"ASSIGNOP", "FILEEND", "RELOP", "IDRES",
                            "ADDOP", "MULOP", "WS", "ARRAYINIT", "TYPE",
                            "INT", "REAL", "PUNCTUATION", "GROUPING", "UNREC"};

const static char RESWORD_PATH[] = "compiler/reswords.dat";
const static char TOKEN_PATH[] = "out/tokens.dat";
const static char LISTING_PATH[] = "out/listing.txt";
char TEST_PATH[256];
FILE* tokenFile;

struct Listing {
    enum ListingType type;
    char message[72];

    union {
        int ln;
        char error[7];
    };
};

void outToListing(struct Listing* entry, FILE *listingFile) {
    switch (entry -> type)
    {
        case LNNUM:
            fprintf(listingFile, "%7d   %s", entry -> ln, entry -> message);
            break;

        case ERROR:
            fprintf(listingFile, "%7s   %s", entry -> error, entry -> message);
            break;
    }
}

// This function outputs a copy of the source file with line numbers to the
// output file.
void copyFile(FILE *sourceFile, FILE *listingFile) {
    int ln = 1;
    int c = 0;
    struct Listing* list = malloc(sizeof(*list));

    while (fgets(list->message, 73, sourceFile))
    {
        list->ln++;
        outToListing(list, listingFile);
    }

}

void writeToken(Token* token)
{
    switch (token -> category)
    {
        case FILEEND:
            fprintf(tokenFile, "%15s %20d\n", catNames[token -> category], token -> type);
            break;

        case IDRES:
            fprintf(tokenFile, "%15s %20s\n", catNames[token -> category], token -> id);
            break;

        case REAL:
            fprintf(tokenFile, "%15s %20f\n", catNames[token -> category], token -> val);
            break;

        case UNREC:
            fprintf(tokenFile, "%15s %c\n", catNames[token -> category], token -> type);
            break;

        default:
            fprintf(tokenFile, "%15s %20d\n", catNames[token -> category], token -> type);
            break;
    }
}

int initTokenFile()
{
    tokenFile = fopen(TOKEN_PATH, "w+");
    if (tokenFile == NULL) {
        fprintf(stderr, "%s%s%s\n", "Could not create token file at ", TOKEN_PATH, " - aborting.");
        return 1;
    }
    return 0;
}

// Returns 1 on failure, 0 on success.
int init() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    FILE *listingFile = fopen(LISTING_PATH, "w+");
    FILE *resFile = fopen(TOKEN_PATH, "r");
    initializeTokens(sourceFile, resFile);
    initTokenFile();
    fclose(resFile);
    if (sourceFile == NULL)
    {
        printf("%s\n", "It was null?");
        fclose(listingFile);
        return 1;
    }


    copyFile(sourceFile, listingFile);
    fclose(sourceFile);
    fclose(listingFile);

    return 0;
}


void printInts(LinkedList* list)
{
    struct node* node = list->head;
    while (node != NULL)
    {
        printf("%d ", *(int *) node->data);
        node = node -> next;
    }
    printf("\n");
}

void printChars(LinkedList* list)
{
    struct node* node = list->head;
    while (node != NULL)
    {
        printf("%c", *(char *) node->data);
        node = node -> next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (init() == 0) {
        Token* next = malloc(sizeof(*next));
        while ((next = getNextToken()))
        {
            int cat = next -> category;
            writeToken(next);
            if (next -> category == FILEEND)
                return 0;
        }
    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in lexical analyzer.");
    }
    return 0;
}
