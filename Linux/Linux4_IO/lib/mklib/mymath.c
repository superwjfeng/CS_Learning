#include "mymath.h"

extern int addToTarget(int from, int to)
{
    int sum = 0;
    for (int i = from; i <= to;  i ++)
        sum += i;
    return sum;
}
