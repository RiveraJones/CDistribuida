// Listado 3.24 - summation of integers by using a fixed number of tasks.

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc , char *argv []) {
  if (argc!=3) {printf ("USO: %s <n> <#tareas>\n", argv[0]); exit (1);}//num vector, tareas
  int max= atoi(argv[1]);
  int tasks= atoi(argv[2]);
  if (max % tasks != 0) return 1;
  int sum = 0;
  #pragma omp parallel num_threads(4)
  {
    #pragma omp single
      for (int t = 0; t < tasks; t++) {//un hilo crea las tareas, luego se pondria a disposicion de realizar esas tareas
        #pragma omp task
        {
          int local_sum = 0;
          int lo = (max / tasks) * (t + 0) + 1;//suma el indice inferio, 1 ,26, 51 a 75, 76 a 100
          int hi = (max / tasks) * (t + 1) + 0;
          // printf ("%d: %d..%d\n", omp_get_thread_num (), lo, hi);
          for (int i = lo; i <= hi; i++)//cada hilo sumara sus datos
            local_sum = local_sum + i;
          #pragma omp atomic
          sum = sum + local_sum;
        }
      }
  }
  printf ("%d\n", sum);//suma correspondiente
  return 0;
}
