#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main()
{
    #pragma omp parallel for collapse(2)
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            printf("(%d, %d) ", i, j);
        }
    }

    return 0;
}