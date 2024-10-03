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
		int recv[size];
		printf("Before all to all Rank: %d\n", rank);
		for(int i = 0; i<size; i++){
			number[i] = rank*size+i;
			printf("%d ", number[i]);
		}
		MPI_Alltoall(number,1, MPI_INT, recv, 1, MPI_INT, MPI_COMM_WORLD);
		printf("After all to all Rank: %d\n", rank);
		for(int i = 0; i<size; i++){
			printf("%d ", i, recv[i]);
			if(i%4 == 0){
				printf("\n");
			}
		}
		printf("\n");
	} else {
		int number[size];
		int recv[size];
		printf("Before all to all Rank: %d\n", rank);
		for(int i = 0; i < size; i++){
			number[i] = rank*size+i;
			printf("%d ", number[i-rank]);
		}
		MPI_Alltoall(number, 1, MPI_INT, recv, 1, MPI_INT, MPI_COMM_WORLD);
		printf("After all to all Rank: %d\n", rank);
		for(int i = 0; i<size; i++){
			printf("%d ", i, recv[i]);
			if(i%4 == 0){
				printf("\n");
			}
		}
		printf("\n");
  	}

	MPI_Finalize();
}
