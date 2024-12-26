#include "batcher.h"

#include <inttypes.h>
#include <stdio.h>

// Return the bit length of the input number.
// Input Parameters
// n: uint32_t: Input number
// Return: uint32_t: Bit length of the input number
uint32_t bit_length(uint32_t n) {
    uint32_t len = 0;

    while (n != 0) {
        len++;
        n /= 2;
    }
    return len;
}

// Compare two elements of an array, and swap if required.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Unsorted array
// x, y: Indices that need to be compared
//
// Returns: void
void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
    return;
}

// Sort the given input array A using batcher sort. Save the number of
// comparisons and moves done to achieve this in the stats data structure.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Unsorted array, which is sorted in the function.
// n: Number of elements in A
//
// Returns: void
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t t, p, q, r, d;

    reset(stats);
    if (n == 0) {
        return;
    }

    t = bit_length(n);
    p = 1 << (t - 1);

    while (p > 0) {
        q = 1 << (t - 1);
        r = 0;
        d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
    return;
}
