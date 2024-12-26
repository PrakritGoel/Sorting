#include "heap.h"

#include <inttypes.h>
#include <stdio.h>

// Return the higher of the two children.
//
// Input Parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Input array
// first, last: uint32_t: First and last elements
//
// Return: uint32_t
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    if ((right <= last) && cmp(stats, A[right - 1], A[left - 1]) == 1) {
        return right;
    }
    return left;
}

// Fix the heap to ensure it obeys the constraints of a heap.
// Input Parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Input array
// first, last: uint32_t: First and last indices of the heap
//
// Return: void
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint8_t found = 0;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while ((mother <= last / 2) && !(found)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = 1;
        }
    }
    return;
}

// Build a heap from the given input array.
//
// Input Parameters
// stats: Stats *: Used to store the number of moves and compares.
//
// Return: void
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t father;

    for (father = last / 2; father > first - 1; father--) {
        fix_heap(stats, A, father, last);
    }
    return;
}

// Sort the given input array A using heap sort. Save the number of
// comparisons and moves done to achieve this in the stats data structure.
//
// Input parameters
// stats: Stats *: Used to store the number of moves and compares.
// A: uint32_t *: Unsorted array, which is sorted in the function.
// n: Number of elements in A
//
// Return: void
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;

    reset(stats);
    build_heap(stats, A, first, last);

    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}
