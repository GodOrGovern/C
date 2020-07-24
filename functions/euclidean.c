#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int r0 = 0, r1 = 0;

    if (argc == 3)
        r0 = atoi(argv[1]), r1 = atoi(argv[2]);

    else
    {
        printf("Usage: ./program x y\n");
        return 0;
    }

    int s0 = 1, s1 = 0, t0 = 0, t1 = 1;
    int rNext = r0, sNext = s0, tNext = t0;
    int q = 0;

    while (r1 != 0)
    {
        q = r0 / r1;
        rNext = r0 - r1*q;
        sNext = s0 - s1*q;
        tNext = t0 - t1*q;

        r0 = r1, r1 = rNext;
        s0 = s1, s1 = sNext;
        t0 = t1, t1 = tNext;
    }

    printf("Quotient: %i\nBezout coefficients: %i, %i\n", q, s0, t0);

    return 0;
}
