#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for seeding RNG

int main()
{
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", ((int)rand()) % 255);
    }  
    return 0;
}