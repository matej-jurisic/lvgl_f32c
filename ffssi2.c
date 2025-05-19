#include "ffssi2.h"

int __ffssi2(int x)
{
    if (x == 0)
        return 0;

    int pos = 0;
    while ((x & 1) == 0)
    {
        x >>= 1;
        pos++;
    }
    return pos;
}