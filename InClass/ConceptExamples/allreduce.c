/*
 * File: allreduce.c
 * Description: A simple MPI program that demonstrates the use of MPI_Allreduce to perform a reduction operation and distribute the result to all processes.
 * Author: Cole Barbes
 * Date: 10/7/2024
 * Usage: mpirun -np <number_of_processes> ./allreduce
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
        
        // Perform the all-reduce operation to find the maximum number and distribute the result to all processes
        MPI_Allreduce(&num_to_send, &number, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
        printf("The max of the list of numbers is : %d\n", number);
    } else {
        
        int number;
        int num_to_send_child = rand() % 100 + 1;
        printf("Rank: %d has %d\n", rank, num_to_send_child);
        
        // Perform the all-reduce operation to find the maximum number and distribute the result to all processes
        MPI_Allreduce(&num_to_send_child, &number, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
        printf("The max of the list of numbers is : %d\n", number);
      }

    // Finalize the MPI environment
    MPI_Finalize();
}
