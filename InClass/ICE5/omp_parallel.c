#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    #pragma omp parallel
    {
        srand(time(0));
        int this_thread = omp_get_thread_num();
        printf("Hello from thread %d\n", this_thread);
    }
    return 0;
}