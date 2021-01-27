package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;
import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class LocksMethods {
    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newFixedThreadPool(2);//pool de 2 hilos. Tenemos 3 entonces, recuerda el principal.
        ReentrantLock lock = new ReentrantLock();

        executor.submit(() -> {
            sleep(1);
            lock.lock();
            try {
                sleep(1);//obtengo el lock y fuermo 3 seg. Luego lo liber.
            } finally {
                lock.unlock();
            }
        });
        executor.submit(() -> {
            System.out.println("Locked: " + lock.isLocked());//el hilo ejecuta la segunda taarea
            System.out.println("Held by me: " + lock.isHeldByCurrentThread());//si el hilo esta ejecutando esa tarea
            boolean locked = lock.tryLock();//aqui ttrato de obtener . Falso si todavia esta lock, ese lock esta ocupado aun.
            System.out.println("Lock acquired: " + locked);//esta tarea avergiua si esa tarea, ese hilo gano
            System.out.println("Held by me: " + lock.isHeldByCurrentThread());//si el hilo esta ejecutando esa tarea
        });
        stop(executor);

        //ASUMO QUE HAY DOS CORES PA MIS DOS THREADS
        //Locked: true, esta ocupado, gana el hilo 1
        //Held by me: false, el lock esta a nombre del hilo 1
        //Intenta pillar el lock
        //Lock acquired: false, el otro hilo ya me gano en el lock, por eso false

        //con sleep 1
        //Locked: false
        //Held by me: false, el lock no esta a nombre
        //intenta pillar el lock
        //Lock acquired: true, porque el hilo 2 si obtiene el lock
        //Held by me: true, el lock esta a nombre del hilo 2
    }
}
