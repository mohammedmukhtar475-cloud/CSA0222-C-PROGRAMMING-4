#include <stdio.h>

extern int shared_counter;

int next_token_static()
{
    static int token = 1000;
    return ++token;
}

int next_token_auto()
{
    int token = 1000;
    return ++token;
}

int main()
{
    int s1 = next_token_static();
    int s2 = next_token_static();
    int s3 = next_token_static();

    printf("Static: %d %d %d\n", s1, s2, s3);

    int a1 = next_token_auto();
    int a2 = next_token_auto();
    int a3 = next_token_auto();

    printf("Auto: %d %d %d\n", a1, a2, a3);

    int e1 = ++shared_counter;
    int e2 = ++shared_counter;
    int e3 = ++shared_counter;

    printf("Extern: %d %d %d\n", e1, e2, e3);

    printf("Register loop:\n");

    for (register int i = 1; i <= 3; i++) {
        printf("%d ", i);
    }

    printf("\n");

    return 0;
}
