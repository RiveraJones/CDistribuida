package ec.edu.epn.pdc;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class ScheduledFuturo {
    public static void main (String argvs[]) throws InterruptedException {
        ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);//se crea una pool con 1 hilo
        Runnable task = () -> {
            try {
                TimeUnit.MILLISECONDS.sleep(1337);//quiero que la tarea dure 1337
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Scheduling: " + System.nanoTime());//luego despliegue la hora en ns
        };
        //ScheduledFuture<?> future = executor.schedule(task, 3, TimeUnit.SECONDS);//planificamos y dentro de 3 segundos, con el hilo task
        int initialDelay = 0; int period = 1;//el principal inicializa las var
        //ScheduledFuture<?> future = executor.scheduleAtFixedRate(task, initialDelay, period, TimeUnit.SECONDS);//duerme un numero de ms, luego despliega la hora. COn el hilo del pool
        //TimeUnit.MILLISECONDS.sleep(1337);
        //long remainingDelay = future.getDelay(TimeUnit.MILLISECONDS);//el reloj sigue corriendo, ahora ya no hay solo 3 segundos. Hanpasado 2999 ns desde que planifico con el hilo del pool
        //System.out.printf("Remaining Delay: %sms\n", remainingDelay);//el hilo principal despliega el t para su ejecucion
        Runnable task1 = () -> {
            try {
                TimeUnit.SECONDS.sleep(2);
                System.out.println("Scheduling: " + System.nanoTime());
            }
            catch (InterruptedException e) {
                System.err.println("task interrupted");
            }
        };
        executor.scheduleWithFixedDelay(task1, 0, 1, TimeUnit.SECONDS);//desde el final
        //despues de terminar la tarea, demoramos un delay de 3 segundo para la ejecucion de la sigueinte tarea.
        //executor.schedule(new runable){

        //}
    }
}

