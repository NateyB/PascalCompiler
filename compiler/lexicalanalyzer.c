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

void copyFile(FILE *sourceFile) {
    int ln = 1;
    int c = 0;
    while ((c = fgetc(sourceFile)) != EOF) {
        printf("%c", c);
        if (c == '\n')
        {
            printf("%6d    ", ln++);
        }
    }
}

int main() {
    FILE *sourceFile = fopen("tests/fib.pas", "r");
    if (sourceFile != NULL)
    {
        copyFile(sourceFile);
        fclose(sourceFile);
    } else
    {
        printf("%s\n", "It was null?");
    }
    printf("\n");

    printf("%d\n", fib(12));
    return 0;
}
