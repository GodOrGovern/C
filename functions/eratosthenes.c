#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void eratosthenes(int max, bool prime[]);

int main(int argc, char* argv[])
{
    int max = 0;

    if (argc == 2)
        max = atoi(argv[1]);

    else
    {
        printf("Usage: ./program max\n");
        return 1;
    }

    bool prime[max+1];
    memset(prime, true, sizeof(prime));

    eratosthenes(max, prime);

    for (int i = 0; i < max; i++)
        if (prime[i] == true)
            printf("%i\n", i);

    return 0;
}

void eratosthenes(int max, bool prime[])
{
    prime[0] = false;
    prime[1] = false;

    int cur = 2;
    int test = 0;
    while (cur*cur <= max)
    {
        test = cur*cur;
        while (test <= max)
        {
            prime[test] = false;
            test += cur;
        }

        do
            cur += 1;
        while (!(prime[cur]));
    }
}
