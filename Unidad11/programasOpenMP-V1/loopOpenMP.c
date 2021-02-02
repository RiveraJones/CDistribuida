#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(void) {

// shared variable
int sum_shared = 0;
//#pragma omp parallel
#pragma omp parallel num_threads(4)
{
    int n = omp_get_num_threads();
    int id  = omp_get_thread_num();
    printf("\nHilo numero %d de %d hilos usados\n", id, n); // sum is indeterminate here
    // private variables (one for each thread)
    int sum_local = 0;
    //#pragma omp for nowait
    #pragma omp for nowait
    for (int i = 0; i < 10; ++i) {
        sum_local += i;
        printf("Sum local del hilo %d = %d\n", id, sum_local);
    }

    //actualizacion de datos globales
    //openMP esperara a que todos los hilos hayan finalizado para entrar en la zona critica
    //#pragma omp critical
    //{
        //printf("Sum local del hilo %d = %d\n", id, sum_local);
        printf("//%d\n", sum_shared);
        sum_shared += sum_local;
        //printf("Sum shared del hilo %d = %d\n", id, sum_shared);
        printf("%d\n", sum_shared);
    //}
}
//print(sum_shared);
//report the result
 printf("---------------%d\n\n", sum_shared); // sum is indeterminate here

/* code */
return 0;
}
