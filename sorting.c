#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Print the sorted array in the format given in the document.
// Input Parameters
// A: uint32_t *: Sorted Array
// arr_size: uint32_t: Size of the array
// num_elements: uint32_t: Number of elements to print
// Return: void
void print_sorted_array(uint32_t *A, uint32_t arr_size, uint32_t num_elements) {
    uint32_t size_to_print = (arr_size < num_elements) ? arr_size : num_elements;

    for (uint32_t i = 0; i < size_to_print;) {
        for (uint32_t j = 0; j < 5; j++) {
            printf("%d\t", A[i]);
            i++;
        }
        printf("\n");
    }
    return;
}

// Print the usage message.
// Input Parameters
// exec_name: char *: The executable name
// Return: void
void usage(char *exec_name) {
    printf("USAGE: %s -[abhiq] -p <print_size> -n <num_to_sort> -r <seed> -H\n", exec_name);
    printf("Sort integers using different sorting algorithms and collect data\n");
    printf(" on the number of moves and compares in each case\n");
    printf("-a: Use all 4 algorithms\n");
    printf("-b: Use batcher sort\n");
    printf("-h: Use heap sort\n");
    printf("-i: Use insertion sort\n");
    printf("-q: Use quick sort\n");
    printf("-H: Print this message\n");
    printf("-p <print_size>: Print at most specified number of elements\n");
    printf("-n <num_to_sort>: The number of elements to sort. Default is 100\n");
    printf("-r <seed>: Set the seed for the pseudo random numbers. Default is 13371453\n");
}

// The main function
int main(int argc, char **argv) {
    uint32_t arr_size = 100;
    uint32_t *A, *B;
    Stats stats;
    uint32_t num_elements = 0xFFFFFFFF;
    uint32_t seed = 13371453;
    int opt;
    Set input_options = empty_set();

    // Parse the input options. Store the sorting options in a set.
    while ((opt = getopt(argc, argv, "ahbiqr:n:p:H")) != -1) {
        switch (opt) {
        case ('a'):
            input_options = insert_set('b', input_options);
            input_options = insert_set('h', input_options);
            input_options = insert_set('i', input_options);
            input_options = insert_set('q', input_options);
            break;
        case ('b'): input_options = insert_set('b', input_options); break;
        case ('h'): input_options = insert_set('h', input_options); break;
        case ('i'): input_options = insert_set('i', input_options); break;
        case ('n'): arr_size = strtoul(optarg, NULL, 10); break;
        case ('p'): num_elements = strtoul(optarg, NULL, 10); break;
        case ('q'): input_options = insert_set('q', input_options); break;
        case ('r'): seed = strtoul(optarg, NULL, 10); break;
        default: usage(argv[0]); exit(EXIT_FAILURE);
        }
    }

    // Set the seed.
    srandom(seed);

    // Allocate memory for A. Use another array to copy the unsorted array
    // to ensure correct statistics if multiple sorting options are given.
    A = (uint32_t *) malloc(arr_size * sizeof(uint32_t));

    for (uint32_t i = 0; i < arr_size; i++) {
        A[i] = (uint32_t) random() & 0x3FFFFFFF;
    }

    B = (uint32_t *) malloc(arr_size * sizeof(uint32_t));
    // In each case, copy the original unsorted array to ensure
    // proper statistics.
    if (member_set('b', input_options)) {
        for (uint32_t i = 0; i < arr_size; i++) {
            B[i] = A[i];
        }
        batcher_sort(&stats, B, arr_size);
        // https://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c
        printf("Batcher Sort, %d elements, ", arr_size);
        printf("%" PRIu64 " moves, ", stats.moves);
        printf("%" PRIu64 " compares\n", stats.compares);
        print_sorted_array(B, arr_size, num_elements);
    }

    if (member_set('h', input_options)) {
        for (uint32_t i = 0; i < arr_size; i++) {
            B[i] = A[i];
        }
        heap_sort(&stats, B, arr_size);
        printf("Heap Sort, %d elements, ", arr_size);
        printf("%" PRIu64 " moves, ", stats.moves);
        printf("%" PRIu64 " compares\n", stats.compares);
        print_sorted_array(B, arr_size, num_elements);
    }

    if (member_set('i', input_options)) {
        for (uint32_t i = 0; i < arr_size; i++) {
            B[i] = A[i];
        }
        insertion_sort(&stats, B, arr_size);
        printf("Insertion Sort, %d elements, ", arr_size);
        printf("%" PRIu64 " moves, ", stats.moves);
        printf("%" PRIu64 " compares\n", stats.compares);
        print_sorted_array(B, arr_size, num_elements);
    }

    if (member_set('q', input_options)) {
        for (uint32_t i = 0; i < arr_size; i++) {
            B[i] = A[i];
        }
        quick_sort(&stats, B, arr_size);
        printf("Quick Sort, %d elements, ", arr_size);
        printf("%" PRIu64 " moves, ", stats.moves);
        printf("%" PRIu64 " compares\n", stats.compares);
        print_sorted_array(B, arr_size, num_elements);
    }

    // Free the memory allocated.
    free(A);
    free(B);
}
