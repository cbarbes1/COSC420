/*
 * File: broadcast.c
 * Description: A simple MPI program that demonstrates broadcasting a number from the root process to all other processes.
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./broadcast <number>
 * Example: mpirun -np 4 ./broadcast 5
 */

#include <stdlib.h>  // Standard library for memory allocation, process control, conversions, etc.
#include <stdio.h>   // Standard I/O library for input and output functions
#include "mpi.h"     // MPI library for parallel programming
#include <string.h>  // String library for handling string operations

int main(int argc, char **argv) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
      fprintf(stderr, "Usage: %s <message>\n", argv[0]);  // Print usage message
      return 1;  // Exit with error code
    }
    
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int rank, size;
    
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      if(rank == 0) {
        // If the process is rank 0, convert the argument to an integer
        int number = atoi(argv[1]);
        
        // Broadcast the number to all other processes
        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        int number;
        // Receive the broadcasted number
        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        // Print the rank and the result of multiplying the rank by the number
        printf("Rank: %d Multiplying myself to the number %d\n", rank, rank*number);
      }

      // Finalize the MPI environment
      return 0;
}