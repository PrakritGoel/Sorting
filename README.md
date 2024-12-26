# Assignment 3 - Sorting Algorithms

This program creates an array of a given size, fills it with pseudorandom integers through a given seed, and sorts it using a specified algorithm. The user has the option of sorting the array via heap sort, batcher sort, insertion sort, quicksort, or any combination of them. 

If the user opts not to provide a size or seed, they will default to the values, 100 and 13371453, respectively. The user also has the option of specifying how many elements of the entire array (once sorted) will be printed in the final output. In the case that the specified or default array size is less than the given number of elements to be printed, the program must print out the entire array and nothing more.

In the final output, before the sorted array is printed, the program must also specify what sorting method was used, the number of elements printed, as well as the number of moves and comparisons made when sorting. If the user uses all the algorithms, each of those specifications must be provided for each sorted array printed.


## Building

Run the following to build the `sorting` program.

```
$ make all
```

## Running

Use the following command to run the program.

```
$ ./sorting <executable_name> -[abhiq] -p <print_size> -n <num_to_sort> -r <seed> -H
```
