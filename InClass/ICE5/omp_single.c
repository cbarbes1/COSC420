#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        // Inside 'single' code is executed by a single thread
        #pragma omp single
        {
            printf("Hello from thread %d\n", omp_get_thread_num());
        }

        // Now outside single, so this is executed by all threads
        printf("Hi I'm thread %d doing this line outside of single\n", omp_get_thread_num());
    }
    printf("\n");
    #pragma omp parallel
    {
        // Inside 'single' code is executed by a single thread
        #pragma omp single nowait
        {
            printf("Hello from thread %d\n", omp_get_thread_num());
        }

        // Now outside single, so this is executed by all threads
        printf("Hi I'm thread %d doing this line outside of single\n", omp_get_thread_num());
    }
    return 0;
}