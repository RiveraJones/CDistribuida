// Listado 3.8 - mult de matrices con bucles colapsados

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int **a, **b, **c;

int main (int argc, char *argv[]) {
  struct timeval ts, tf;
  int i, j;

  if (argc!=2) {printf ("USO: %s <dim-matrices>\n", argv[0]); exit (1);}
  int n = atoi (argv[1]);

  if ((a = malloc (n * sizeof (int *)))==NULL) {printf ("malloc\n"); exit (1);}
  if ((b = malloc (n * sizeof (int *)))==NULL) {printf ("malloc\n"); exit (1);}
  if ((c = malloc (n * sizeof (int *)))==NULL) {printf ("malloc\n"); exit (1);}

  for (i=0; i<n; i++) {
    if ((a[i] = malloc (n*sizeof (int)))==NULL) {printf ("malloc\n"); exit (1);}
    if ((b[i] = malloc (n*sizeof (int)))==NULL) {printf ("malloc\n"); exit (1);}
    if ((c[i] = malloc (n*sizeof (int)))==NULL) {printf ("malloc\n"); exit (1);}
  }

  srandom (613);
  for (i=0; i<n; i++) {
    for (j=0; i<n; i++) {
      a[i][j] = random() % 1000;
      b[i][j] = random() % 1000;
    }
  }

  gettimeofday (&ts, NULL);
  #pragma omp parallel for collapse (2)
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      c[i][j] = 0.0;
      for (int k = 0; k < n; k++)
        c[i][j] = c[i][j] + a[i][k] * b[k][j];
    }
  gettimeofday (&tf, NULL);

  printf ("Time: %f secs\n",  
        ((tf.tv_sec - ts.tv_sec)*1000000u + tf.tv_usec - ts.tv_usec)/ 1.e6);
  exit (0);


}
