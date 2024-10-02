#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char **argv) {
	if (argc != 2) {
	  fprintf(stderr, "Usage: %s <message>\n", argv[0]);
	  return 1;
	}
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  	if(rank == 0) {
		int number = atoi(argv[1]);
		MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
		int number;
		MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Rank: %d Multiplying myself to the number %d\n", rank, rank*number);
  	}

  	return 0;
}
