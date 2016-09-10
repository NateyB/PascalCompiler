#include<stdio.h>
#include<stdlib.h>

enum ListingType {LNNUM, ERROR};

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

// Returns 1 on failure, 0 on success.
int init() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    FILE *listingFile = fopen("out/listing.txt", "w+");
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

int main() {
    if (init() == 0) {

    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in lexical analyzer.");
    }
    return 0;
}
