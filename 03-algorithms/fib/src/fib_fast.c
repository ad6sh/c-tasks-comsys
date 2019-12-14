#include "fib.h"

uint32_t fib_fast(uint32_t n)
{
    uint32_t fib_fast_recursion(uint32_t, uint32_t, uint32_t);
    return fib_fast_recursion(n, 0, 1);
}

uint32_t fib_fast_recursion(uint32_t n, uint32_t a, uint32_t b)
{
    switch(n)
    {
        case 0:
            return a;
        case 1:
            return b;
        default:
            return fib_fast_recursion(n-1, b, a+b);
	}
}