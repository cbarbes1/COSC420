#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


double *rowMatrixMult(double vect[], double *matrix[], int size)
{
	double *output = (double *)malloc(sizeof(double)*size);

	for(int i = 0; i<size; i++)
	{
		for(int j = 0; j<size; j++)
		{
			output[i] += vect[j]*matrix[j][i];
		}
		
	}
	return output;
}	

int main(int argc, char **argv)
{
	if(argc < 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	int size = atoi(argv[1]);
	double *arr = (double *)malloc(sizeof(double)*size);
	double **matrix = (double **)malloc(sizeof(double *)*size);
	double total = 0;
	for(int i = 0; i<size; i++)
	{
		arr[i] = (double)rand() / RAND_MAX;
		total+= arr[i];
		matrix[i] = (double *)malloc(sizeof(double)*size);
		for(int j = 0; j<size; j++){
			matrix[i][j] = (double)rand() / RAND_MAX;
		}
	}

	double timing = omp_get_wtime();

	double *result = rowMatrixMult(arr, matrix, size);

	timing = omp_get_wtime() - timing;

	printf("Matrix Multiplication took: %fs\n", timing);

	if(argc > 2){
		if(argv[2][0] == '-' && argv[2][1] == 'v'){
			printf("Resulting vector\n");
			for(int i = 0; i<size; i++){
				if(i < size-1){
					printf("%f, ", result[i]);
				}else{
					printf("%f", result[i]);
				}
			}

			printf("\n\n\nMatrix:\n");
			for(int i = 0; i<size; i++){
				for(int j = 0; j<size; j++){
					printf("%f\t", matrix[i][j]);
				}
				printf("\n");
			}
			printf("\n");

			printf("Original Vector:\n");
			for(int i = 0; i<size; i++){
				if(i < size-1){
					printf("%f, ", arr[i]);
				}else{
					printf("%f", arr[i]);
				}
			}
			printf("\n");
		}
	}
	free(result);

	for(int i = 0; i<size; i++){
		free(matrix[i]);
	}
	free(matrix);
	return 0;

}
