#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char **argv) {
	
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  	if(rank == 0) {
		int number[size];
		MPI_Gather(&rank,1, MPI_INT, number, 1, MPI_INT, 0, MPI_COMM_WORLD);
		for(int i = 0; i<size; i++){
			printf("Gathered rank %d\n", number[i]);
		}
	} else {
		int number[size];
		MPI_Gather(&rank, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
  	}

	MPI_Finalize();
}
