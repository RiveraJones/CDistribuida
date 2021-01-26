// barrera.c - uso de barreras

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t   barrier;

void *thread1 (void *not_used) {
  time_t  now;
  char  buf [27];

  time (&now);
  printf ("thread1 inicia a las %s", ctime_r (&now, buf));

  sleep (5); // simular computacion
  pthread_barrier_wait (&barrier);//los 3 hilos se esperan mutuamente para desplegar
  time (&now);//el tiempo
  printf ("barrera en thread1() finaliza a las  %s", ctime_r (&now, buf));
}

void *thread2 (void *not_used) {
  time_t  now;
  char  buf [27];

  time (&now);
  printf ("thread2 inicia a las %s", ctime_r (&now, buf));

  sleep (10);
  pthread_barrier_wait (&barrier);
  time (&now);
  printf ("barrera en thread2() finaliza a las  %s", ctime_r (&now, buf));
}

int main (int argc, char *argv[]) {
  pthread_t th1, th2;
  time_t  now;
  char  buf [27];

  // crear barrera con cuenta = 3
  pthread_barrier_init (&barrier, NULL, 3);//3 hilos ejecutan esta funcion, una vez terminado pueden seguir con lo que les corresponde
  printf ("MAX THs: %d\n", _SC_THREAD_THREADS_MAX);

  // iniciar hilos, thread1 y thread2
  pthread_create (&th1, NULL, thread1, NULL);
  pthread_create (&th2, NULL, thread2, NULL);

  // en este momento, los hilos thread1 y thread2 estan ejecutandose, y el PRINCIPAL
  //si tenemos 3 cores, cada core ejecuta cada hilo no sabemos que orden

  // now wait for completion, la barrera espera
  time (&now);
  printf ("Hilo main() esperando en la barrera a las %s", ctime_r (&now, buf));
  pthread_barrier_wait (&barrier);//los 3 hilos, el principal y los 2 hijos han terminado despliego el tiempo

  time (&now);
  printf ("barrera en main() finaliza a las  %s", ctime_r (&now, buf));
}
