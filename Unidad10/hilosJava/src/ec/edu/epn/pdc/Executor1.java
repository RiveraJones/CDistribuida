package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Executor1 {

    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Future f = executor.submit(() -> {//enviamos la tarea al pool. El pool tiene 1 solo hilo.
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        });

        executor.shutdownNow();//si no terminamos el pool, si comento esto, no se va acabar
    }
}
