/*
 * File: reducescatter.c
 * Description: A simple MPI program that demonstrates the use of MPI_Reduce_scatter to perform a reduction operation and scatter the results.
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./reducescatter
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int rank, size;
    
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays for counts and numbers
    int counts[size];
    int number[size];
    
    // Fill the arrays with values based on the rank and size
    for(int i = 0; i < size; i++){
        number[i] = rank * size + i;
        counts[i] = 1;
    }
    
    // Variable to store the result of the reduction operation
    int result;
    
    // Perform the reduce-scatter operation
    MPI_Reduce_scatter(number, &result, counts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    // Print the result of the reduction operation for each process
    printf("The sum of Column %d of the matrix: %d\n", rank, result);

    // Finalize the MPI environment
    MPI_Finalize();
}
