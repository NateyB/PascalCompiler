#include<stdio.h>

int fib(int n) {
    int sum = 0;
    int last = 1;
    int placeholder;
    for (int i = 0; i < n; i++) {
        placeholder = sum;
        sum += last;
        last = placeholder;
    }
    return sum;
}

int main() {
    printf("%s\n", "Love ya!");
    printf("%d\n", fib(12));
    return 0;
}
