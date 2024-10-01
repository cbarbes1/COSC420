/* Author: Cole James Barbes
 * Purpose: Take parameter size for rating matrix and find the averages of the rating for each product
 * Parameters: 
 * 	m: number of products to be rated
 *	n: number of ratings for the product
 * Notes: This Program was written for COSC 420 an introductory course in distributed and parallel computing
 */
#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* 
 * Convert a string to an integer
 */
int strtoint(char *arg){
	int result = 0;
	int sign = 1;

	while(*arg == ' '){
		arg++;
	}

	// account for the sign, added this just to cover bases for maybe other assignments
	if(*arg == '-'){
		sign = -1;
		arg++;
	}
	else if(*arg == '+'){
		arg++;
	}

	// convert each digit and each extra digit becomes new place by multiplying it by 10
	while(*arg <='9' && *arg >= '0'){
		result = result*10 + (*arg - '0');
		arg++;
	}

	// account for the sign
	result=result*sign;

	// return the final result
	return result;
}

/*
 * Print a matrix in a "pretty" way
 */
void prettyprint(int **Array, int m, int n){
	printf("  ");
	for(int i = 0; i < n; i++){
		printf("____");
	}
	printf("_\n");

	for(int i = 0; i<m; i++){
        	printf("%d |", i+1);
		for(int j = 0; j<n; j++){
			printf(" %d |", Array[i][j]);
                }
                printf("\n");
        }
	printf("  ");
	for(int i = 0; i<n; i++){
        	printf("----");
        }
	printf("-\n");

}

/* Quicksort function
 * recursive function
 * Parameters:
 * 	float A: Array of floats 
 * 	left: int the left side of the sort
 * 	right: int the right side of the sort
 */
void quickSort(float A[], int left, int right) {
	int i = left;
	int j = right;
	int mid = (left + right) / 2;

	float pivot = A[mid];

	while (i <= j) {
		while (A[i] < pivot)
			i++;

		while (A[j] > pivot)
			j--;

		if (i <= j) {
			float tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
			j--;
		}
	}

	if (left < j)
		quickSort(A, left, j);

	if (i < right)
		quickSort(A, i, right);
}


// first call setup
void quickSortR(float A[], int size) {
	quickSort(A, 0, size - 1);
}

int main(int argc, char **argv) {
	
	// initialize MPI
	MPI_Init(&argc, &argv);

	
	// setup all needed vars
	int size, rank, m, n;
	double t1 = MPI_Wtime();
	MPI_Status status;

	// get the size and ranks in the world
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// convert input to integer with self made function
	m = strtoint(argv[1]);
	n = strtoint(argv[2]);
	
	// insufficient computational power error
	if(size <= m){
		if(rank == 0){
			printf("Insufficient Friends to Run the script. Please go ask Dr. Jing to help you find friends\n");
		}
		MPI_Abort(MPI_COMM_WORLD, 404);
	}

	srand(time(NULL));
	if(rank == 0){
		//t1 = MPI_Wtime();
		//
		// parent setup all children to get the average
	

		//int Ratings[m][n];
		// allocate the outer array
		
		int **Ratings = (int **)malloc(m * sizeof(int *));

		// allocate each of the inner arrays
		for(int i = 0; i < m; i++){
			Ratings[i] = (int *)malloc(n * sizeof(int *));
		}
		// set random numbers into each cell
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				Ratings[i][j] = rand()%5 + 1;
			}
		}

		// print the matrix in designed box
		prettyprint(Ratings, m, n);

		// send each array
		for(int i = 0; i<m; i++){
			MPI_Send(Ratings[i], n, MPI_INT, (i+1), 555, MPI_COMM_WORLD);
		}
		float rating_averages[m];

		// recieve each rating average
		for(int i = 0; i<m; i++){
			MPI_Recv(&rating_averages[i], 1, MPI_FLOAT, MPI_ANY_SOURCE, 77, MPI_COMM_WORLD, &status);
		}

		printf("\n");

		// print the averages
		printf("Before sort:\n");
		for(int i = 0; i<m; i++){
			printf("%.2f ", rating_averages[i]);
		}

		printf("\n");

		// sort the averages
		quickSortR(rating_averages, m);

		// print again
		printf("After sort:\n");
		for(int i = 0; i<m; i++){
			printf("%.2f ", rating_averages[i]);
		}
		printf("\n");

		// clear the array
		free(Ratings);
	}
	else if(rank <= m){

		int recv_count;


		int total = 0;
		
		// allocate the rating array
		int* Rating = (int *)malloc(n * sizeof(int));

		// recieve the rating array from the parenti
		MPI_Recv(Rating, n, MPI_INT, 0, 555, MPI_COMM_WORLD, &status);

		// GET THE COUNT
		MPI_Get_count(&status, MPI_INT, &recv_count);

		// get the total
		for(int i = 0; i< recv_count; i++){
			//printf("%d |", Rating[i]);	
			total = total + Rating[i];
		}

		// find the average
		float average = (float)total / n;

		// send the average
		MPI_Send(&average, 1, MPI_FLOAT, 0, 77, MPI_COMM_WORLD);
		
		// free the array
		free(Rating);
	}
	// only in the parent end the time, we dont want redundancy
	if(rank == 0){
		double t2 = MPI_Wtime();
		printf("MPI run time: %f\n", t2-t1);
	}

	// finalize
	MPI_Finalize();
	
}
