#include<stdio.h>

int fib(int n) {
    int sum = 0;
    int last = 1;
    int placeholder = 0;
    for (int i = 0; i < n; i++) {
        placeholder = sum;
        sum += last;
        last = placeholder;
    }
    return sum;
}

void copyFile(FILE *sourceFile, FILE *outputFile) {
    int ln = 1;
    int c = 0;
    fprintf(outputFile, "%6d    ", ln++);
    while ((c = fgetc(sourceFile)) != EOF) {
        fprintf(outputFile, "%c", c);
        if (c == '\n')
        {
            fprintf(outputFile, "%6d    ", ln++);
        }
    }
}

int main() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    FILE *outputFile = fopen("out/copy.txt", "w+");
    if (sourceFile != NULL)
    {
        copyFile(sourceFile, outputFile);
        fclose(sourceFile);
    } else
    {
        printf("%s\n", "It was null?");
    }
    fclose(outputFile);
    printf("\n");

    printf("%d\n", fib(12));
    return 0;
}
