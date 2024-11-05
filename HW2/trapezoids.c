/* Author: Cole James Barbes
 * Creation Data: 10-15-2024
 * Last Edited: 10-20-2024
 * Purpose: To estimate the integral of x^2 from a to b over n trapezoids
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

/* Purpose: Square a double 
 * Params: double x 
 * Return x * x
 */
double square(double x)
{
	return x*x;
}

/* Purpose: calculate the trapezoidal rule for a ==> b using n trapezoids
 * Params: a value, b value, n trapezoids
 * Return: the estimation of the integral
 */
double trapezoid(double a, double b, int n){
	double result = (square(a) + square(b))/2;
	double dx = ( b - a ) / n;
	for(int i = 1; i<n; i++){
		double subx = a + i*dx;
		result = result + square(subx);
	}
	
	return dx*result;
}


// main
int main(int argc, char **argv)
{
	if(argc < 4){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	
	// convert the arguments to numbers from c string
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	int n = atoi(argv[3]);
	double min, max, avg;
	double final_result = 0;
	// init mpi
	MPI_Init(&argc, &argv);

	// get the size and ranks for each 
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// get the start time
	double start_time = MPI_Wtime();

	// get the range size
	double range_size = (b-a)/size;

	// get the processes a value	
	double local_a = a + (rank*range_size);
	
	// get the processes b value
	double local_b = local_a + range_size;

	int local_n = n/size;
	// get the result of the local trapezoidal rule estimation
	double result = trapezoid(local_a, local_b, local_n);

	//MPI_Gather(&result, 1, MPI_DOUBLE, res_list, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Reduce(&result, &final_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	// get the end time
	double end_time = MPI_Wtime();

	// runtime
	double runtime = end_time - start_time;
	MPI_Reduce(&runtime, &min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&runtime, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&runtime, &avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0){
		// get the exponent for 10^x
		int exp = log(final_result)/log(10);

		// compute the result with divided out multiples of 10
		final_result = final_result / pow(10, exp);

		// print result
		printf("With n = %d, The total of the estimate of the integral of x^2 on the interval\nfrom %.2f to %.2f = %.5fe+%02d\n", n, a, b, final_result, exp);

		// print runtime stats
		avg = avg / size;
		printf("Among %d processes, the runtime statistics are :\nMin: %fs Max: %fs Avg: %fs\n", size, min, max, avg);
			
		FILE *file;

		file = fopen("output.txt", "a");

		if(file == NULL){
			printf("Error opening the file\n");
		}else{
			fprintf(file, "%d %f %f %f\n", size, min, max, avg);
			fclose(file);
		}
	}

	MPI_Finalize();
}
