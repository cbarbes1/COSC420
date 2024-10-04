#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char **argv) {

	// Init mpi	
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  	// create the arrays
	int number[size];
	int recv[size];

	printf("Before all to all Rank: %d\n", rank);
	// fill with rank so you can visualize the all to all process
	for(int i = 0; i<size; i++){
		number[i] = rank*size + i;
		printf("%d ", number[i]);
	}
	printf("\n");
	
	// all to all send
	MPI_Alltoall(number,1, MPI_INT, recv, 1, MPI_INT, MPI_COMM_WORLD);

	// print the recieve array after all ranks are sent directly to each index in each process
	printf("After all to all Rank: %d\n", rank);
	for(int i = 0; i<size; i++){
		printf("%d ", recv[i]);
	}

	printf("\n");

	// finalize
	MPI_Finalize();

}
