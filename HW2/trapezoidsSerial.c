/* Author: Cole Barbes
 * Purpose: Implement a serial trapezoidal rule integral estimation for n trapezoids
 * Creation Date: 10-15-2024
 * Last Edited: 10-20-2024
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

// square a number
double square(double x)
{
	return x*x;
}

// trapezoidal rule function
double trapezoid(double a, double b, int n){
	double result = (square(a) + square(b))/2;
	double dx = ( b - a ) / n;

	for(int i = 1; i<n; i++){
		double subx = a + i*dx;
		result = result + square(subx);
	}
	return dx*result;
}

// main program to set params and print result
int main(int argc, char **argv)
{
	if(argc != 4){
		printf("Insufficient Arguments\n");
		exit(1);
	}

	// get the cpu clock time currently
	clock_t time = clock();

	// convert needed vars
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	int n = atoi(argv[3]);

	// print the vars
	printf("a = %f, b = %f, n = %d\n", a, b, n);

	// get estimation
	double result = trapezoid(a, b, n);

	int exp = log(result)/log(10);

	result = result / pow(10, exp);	
	// print the estimate
	printf("My estimate of the Integral of x^2 on the interval\nfrom %.2f to %.2f = %.5fe+%02d\n", a, b, result, exp);

	// get the end clock time
	time = clock() - time;
	double run_time = ((double)time) / CLOCKS_PER_SEC;

	// print the runtime
	printf("The serial runtime for the trapezoid rule was %fs\n", run_time);

	FILE *file;

	file = fopen("output.txt", "a");

	if(file == NULL){
		printf("Error opening output file\n");
	}else{
		fprintf(file, "%f\n", run_time);
		fclose(file);
	}
	return 0;	
}
