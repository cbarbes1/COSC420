/*
 * File: scan.c
 * Description: A simple MPI program that demonstrates the use of MPI_Scan to perform a prefix reduction operation.
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./scan
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

    // Seed the random number generator with a different seed for each process
    srand(time(NULL) + rank);
      if(rank == 0) {
        int number;
        int num_to_send = rand() % 100 + 1;
        printf("Rank: %d has %d\n", rank, num_to_send);	
        
        // Perform the scan operation to compute the prefix sum
        MPI_Scan(&num_to_send, &number, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        printf("At Rank: %d My Sum is : %d\n", rank, number);
    } else {
        int number;
        int num_to_send_child = rand() % 100 + 1;
        printf("Rank: %d has %d\n", rank, num_to_send_child);
        
        // Perform the scan operation to compute the prefix sum
        MPI_Scan(&num_to_send_child, &number, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        printf("At Rank: %d My Sum is : %d\n", rank, number);
      }

    // Finalize the MPI environment
    MPI_Finalize();
}