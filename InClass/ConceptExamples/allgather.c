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
		MPI_Allgather(&rank,1, MPI_INT, number, 1, MPI_INT, MPI_COMM_WORLD);
		printf("Rank: %d recieved:", rank);
		for(int i = 0; i<size; i++){
			printf("A%d %d ", i, number[i]);
			if(i%4 == 0){
				printf("\n");
			}
		}
		printf("\n");
	} else {
		int number[size];
		MPI_Allgather(&rank, 1, MPI_INT, number, 1, MPI_INT, MPI_COMM_WORLD);
		printf("Rank: %d recieved:", rank);
		for(int i = 0; i<size; i++){
			printf("A%d %d ", i, number[i]);
			if(i%4 == 0){
				printf("\n");
			}
		}
		printf("\n");
  	}

	MPI_Finalize();
}
