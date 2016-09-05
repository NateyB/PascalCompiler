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

// Returns 0 on failure, 1 on success.
int init() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    FILE *listingFile = fopen("out/listing.txt", "w+");
    if (sourceFile != NULL)
    {
        copyFile(sourceFile, listingFile);
        fclose(sourceFile);
    } else
    {
        printf("%s\n", "It was null?");
        return 0;
    }
    fclose(listingFile);

    return 1;
}

int main() {
    if (init()) {

    } else {
        return 1;
    }
    return 0;
}
