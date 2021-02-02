#include <stdio.h>
#include <omp.h>

int main(void) {

// shared variable
int sum_shared = 0;
#pragma omp parallel
{
    // private variables (one for each thread)
    int sum_local = 0;
    #pragma omp for nowait
    //#pragma omp for
    for (int i = 0; i < 10; ++i) {
        sum_local += i;
    }
    //#pragma omp critical
    {
        sum_shared += sum_local;
    }
}
//print(sum_shared);
 printf("%d\n", sum_shared); // sum is indeterminate here

/* code */
return 0;
}
