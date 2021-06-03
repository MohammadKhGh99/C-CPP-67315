#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Error");
    }
    int arg = atoi(argv[1]);
    if (arg == 1)
        printf("Hello, Word!");
    else if (arg == 2)
    {
        printf("Welcome to C!\n");
    }
    else if (arg == 3)
    {
        printf("?\n");
    }
    return 0;
}

