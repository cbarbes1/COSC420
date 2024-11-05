/* Author: Cole Barbes
 * Purpose: sum from 1 to N using 4 threads and using the reduce
 * Creation date: 10/29/2024
 * Last edited: 10/29/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char **argv)
{
	// validate the arguments
	if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	int N = atoi(argv[1]);
	// make sure N is 2000 or above
	if(N < 2000){
		printf("N must be over 2000\n", N);
		exit(2);
	}

	long int sum = 0;
	double start_time = omp_get_wtime(); // get start time
	// use omp parallel for to divide the for loop evenly accross 8 threads
	#pragma omp parallel for reduction(+:sum) num_threads(8)
	for(int i = 1; i<=N; i++){
		sum = sum + i;
	}
	double total_time = omp_get_wtime() - start_time; // end time
	// print the results
	printf("Summation result: %d Runtime: %f\n", sum, total_time);
	return 0;
}
