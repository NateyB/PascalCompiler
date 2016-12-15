#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "dataStructures/linkedList/linkedlist.h"
#include "errorHandler/errorHandler.h"
#include "globals/globals.h"
#include "handler/handler.h"
#include "parser/parser.h"

// Global file constants
static const char TOKEN_PATH[] = "out/tokens.dat";
static const char LISTING_PATH[] = "out/listing.txt";
static const char MEM_PATH[] = "out/mem.txt";
static const char RESWORD_PATH[] = "compiler/data/reswords.dat";

// Returns 1 on failure, 0 on success.
int init(char* sourcePath) {
    return initializeGlobals() && initializeErrorHandler() &&
    initializeHandler(sourcePath, RESWORD_PATH, LISTING_PATH, TOKEN_PATH, MEM_PATH)
    ? 0 : 1;
}

int run()
{
    generateParseTree();

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", "Expected exactly one file to compile!");
    } else {
        if (init(argv[1]) == 0) {
            if (run() != 0)
                fprintf(stderr, "%s\n", "Run failed. Could not terminate properly.");
        } else {
            fprintf(stderr, "%s\n", "Initialization process failed in tokenizer.");
        }
    }
    return 0;
}
