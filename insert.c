#include "insert.h"

#include <inttypes.h>
#include <stdio.h>

// Sort the given input array A using insertion sort. Save the number of
// comparisons and moves done to achieve this in the stats data structure.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Unsorted array, which is sorted in the function.
// n: Number of elements in A
//
// Returns: void
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t i, j, temp;

    reset(stats);
    for (i = 1; i < n; i++) {
        j = i;
        temp = move(stats, A[i]);

        while (j > 0 && cmp(stats, temp, A[j - 1]) == -1) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
    return;
}
