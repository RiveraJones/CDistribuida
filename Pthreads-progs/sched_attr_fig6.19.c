#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *th_routine (void *arg) {return NULL;}

__thread int i;  //cada hilo obtiene su propia instancia de i (como TLS)

int main (int argc, char *argv[]) {
  pthread_t th_id;
  pthread_attr_t attr;
  struct sched_param param;
  int policy, min_prio, max_prio;

  pthread_attr_init (&attr);//el hilo oirginal crea atributos para los que se crean al final
  if (sysconf (_SC_THREAD_PRIORITY_SCHEDULING != -1)) {
    pthread_attr_getschedpolicy (&attr, &policy);//obtenemos los valores de la politica
    pthread_attr_getschedparam (&attr, &param);//obtenemos los los parametros bajo esa politica
    printf ("Policy %d, Prio %d\n", policy, param.sched_priority);//el parametro q me interesa es la prioridad pa saber que hilos se han creado
    pthread_attr_setschedpolicy (&attr, SCHED_RR);//cambio los atributos, con esa politica SCHED_RR en lugar de la de default
    pthread_attr_getschedpolicy (&attr, &policy);//obtenemos nuevamente la politica aver k pex
    pthread_attr_getschedparam (&attr, &param);//obtenemos los aprametros, pa ver la max y min prioridad con la que se pueden ejecutar los hilos dentro de esa nueva politica, 0 entre 199
    min_prio = sched_get_priority_min (SCHED_RR);//main
    max_prio = sched_get_priority_max (SCHED_RR);//max
    printf ("Policy %d, Prio %d, min_prio: %d, max_prio: %d\n", policy,
            param.sched_priority, min_prio, max_prio);
    param.sched_priority = (min_prio + max_prio)/2;
    pthread_attr_setschedparam (&attr, &param);
    pthread_attr_setinheritsched (&attr, PTHREAD_EXPLICIT_SCHED);
  }
  pthread_create (&th_id, &attr, th_routine, NULL);
  pthread_join (th_id, NULL);
  return 0;
}
