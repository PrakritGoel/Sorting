#include "quick.h"

#include <inttypes.h>
#include <stdio.h>

// Partition the input array to separate all elements higher than a key
// on one side and lower than the key on the other. Return the index of
// key.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Array that needs to be partitioned
// lo: Lower index of the array
// hi: Higher index of the array
//
// Return: Index of the key.
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;

    for (uint32_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return (i + 1);
}

// Recursive function to partition the array
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Input array
// lo, hi: uint32_t: Indexes of the array to be used for partition.
//
// Return: void
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t p;

    // Continue till the list contains only one element
    if (lo < hi) {
        p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

// Sort the given input array A using quick sort. Save the number of
// comparisons and moves done to achieve this in the stats data structure.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Unsorted array, which is sorted in the function.
// n: Number of elements in A
//
// Return: void
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);
    quick_sorter(stats, A, 1, n);
    return;
}
