package ec.edu.epn.pdc;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class InvokeAny {
    static Callable<String> callable(String res, long sleepSeconds) {
        return () -> {
            TimeUnit.SECONDS.sleep(sleepSeconds);
            return res;
        };
    }
    public static void main (String argvs[]) throws ExecutionException, InterruptedException {
        ExecutorService executor = Executors.newWorkStealingPool();
        List<Callable<String>> callables = Arrays.asList(
                //tengo 3 tareas ejecutandose con concurrencia. Si tengo solo 2 cores, de los 3 hilos solo 2 al mismo tiempo, concurrentes.
            callable("task1", 2),//luego este
            callable("task2", 1),//el futuro mas cercano, este primero. Este tarea termina primera, este future esta disponible antes.
            callable("task3", 3));//finalmente este
        String result = executor.invokeAny(callables);
        System.out.println(result);
    }
}
