/*
 * File: gather.c
 * Description: A simple MPI program that demonstrates gathering the rank to the root process
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./gather
 * Example: mpirun -np 4 ./gather
 */
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char **argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int rank, size;
    
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      if(rank == 0) {
        // If the process is rank 0, prepare an array to gather the ranks
        int number[size];
        
        // Gather the ranks from all processes to the root process
        MPI_Gather(&rank, 1, MPI_INT, number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        // Print the gathered ranks
        for(int i = 0; i < size; i++){
            printf("Gathered rank %d\n", number[i]);
        }
    } else {
        // For all other processes, gather the ranks to the root process
        MPI_Gather(&rank, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
      }

    // Finalize the MPI environment
    MPI_Finalize();
}