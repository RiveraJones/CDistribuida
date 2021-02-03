// Listado 3.20 - Uso de scheduling definido at runtime

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <time.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <max-hilos>\n", argv[0]); exit (1);}
  int max = atoi (argv[1]);
  long int sum = 0;
  clock_t t;
  t = clock();
//static, chunk, divide en trozos de max y los va asignando
//dynamic, chunk, no hay patron de los trozos de max, una vez acabe requiere de otro
//distribuye dinámicamente las iteraciones durante el tiempo de ejecución.
//auto,
  #pragma omp parallel for reduction (+: sum) schedule(static, 3)
  for (int i = 1; i <= max; i++) {
    //printf ("%2d @ hilo = %d de %d\n", i, omp_get_thread_num (), omp_get_num_threads());
    //sleep (i < 4 ? i + 1 : 1);
    //sleep (i++);
    sum = sum + i;
  }
  t = clock() - t;
  double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000);
  printf("\n------tiempo %f mss \n", time_taken);
  printf ("%ld\n", sum);
  return 0;
}
