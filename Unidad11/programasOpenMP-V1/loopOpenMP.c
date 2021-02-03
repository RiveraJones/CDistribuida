#include <stdio.h>
#include <omp.h>

#include <time.h>
#include <unistd.h>

int main(void) {

// shared variable
int sum_shared = 0;
//#pragma omp parallel
clock_t t;
t = clock();
#pragma omp parallel num_threads(8)
{
    int n = omp_get_num_threads();
    int id  = omp_get_thread_num();
    //printf("\nHilo numero %d de %d hilos usados\n", id, n); // sum is indeterminate here
    // private variables (one for each thread)
    int sum_local = 0;
    //#pragma omp for nowait
    #pragma omp for nowait
    for (int i = 0; i < 100000; ++i) {
        sum_local += i;
        //printf("Sum local del hilo %d = %d\n", id, sum_local);
        //if(id=1){
          //sleep(5);
        //}
    }//no hay barrera implicita

    //actualizacion de datos globales
    //openMP esperara a que todos los hilos hayan finalizado para entrar en la zona critica
    //en la zona critica se garantiza una esclusividad mutua
    //#pragma omp critical
    //{
        //printf("//%d\n", sum_shared);
        sum_shared += sum_local;
        //printf("Sum shared del hilo %d = %d\n", id, sum_shared);
        //printf("%d\n", sum_shared);
    //}
}//BARRERA IMPLICITA
//report the result
t = clock() - t;
double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000);
printf("\ntiempo %f mss \n", time_taken);
printf("---------------%d\n\n", sum_shared); // sum is indeterminate here

return 0;
}
