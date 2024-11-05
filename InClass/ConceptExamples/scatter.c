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
#include <time.h>


int main(int argc, char **argv) {
    	srand(time(NULL));
	int SIZE = atoi(argv[1]);
	int matrix[SIZE][SIZE];

	for(int i = 0; i<SIZE; i++){
		for(int j = 0; j<SIZE; j++){
			matrix[i][j] = rand() % 100;
		}
	}

	// Initialize the MPI environment
    	MPI_Init(&argc, &argv);
    	int rank, size;
    
    	// Get the number of processes
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    	// Get the rank of the process
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(SIZE == size){

      		int number[SIZE];
    		// Gather the ranks from all processes to the root process
    		MPI_Scatter(matrix, SIZE, MPI_INT, number, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Process: %d \n", rank);
		for(int i = 0; i<SIZE; i++){
			printf("%d ", number[i]);
		}
		printf("\n");
	}
    		// Finalize the MPI environment
    	MPI_Finalize();
}
