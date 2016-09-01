#include<stdio.h>

// This function outputs a copy of the source file with line numbers to the
// output file.
void copyFile(FILE *sourceFile, FILE *outputFile) {
    int ln = 1;
    int c = 0;
    char buffer[72] = {0};

    while (fgets(buffer, 73, sourceFile)) {
        fprintf(outputFile, "%6d    ", ln++);
        fprintf(outputFile, "%s", buffer);
    }
}

int main() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    FILE *outputFile = fopen("out/listing.txt", "w+");
    if (sourceFile != NULL)
    {
        copyFile(sourceFile, outputFile);
        fclose(sourceFile);
    } else
    {
        printf("%s\n", "It was null?");
    }
    fclose(outputFile);

    return 0;
}
