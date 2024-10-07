/*
 * File: allgather.c
 * Description: A simple MPI program that demonstrates the use of MPI_Allgather to gather data from all processes and distribute it to all processes.
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./allgather
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

    // For all processes, gather the ranks to all processes
    int number[size];
    MPI_Allgather(&rank, 1, MPI_INT, number, 1, MPI_INT, MPI_COMM_WORLD);
        
    // Print the gathered ranks
    printf("Rank: %d received: ", rank);
    for(int i = 0; i < size; i++){
        printf("%d ", number[i]);
    }
    printf("\n");

    // Finalize the MPI environment
    MPI_Finalize();
}