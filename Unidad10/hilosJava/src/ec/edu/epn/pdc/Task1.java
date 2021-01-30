package ec.edu.epn.pdc;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;

public class Task1 {
    public static void main (String args[]) throws InterruptedException {
        Runnable task = () -> {//defino la tarea, y segun mafla la ejecuta el hilo principal
            sleep(1);
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        };
        task.run();
        Thread thread0 = new Thread(task);//se crea un hilo pa que ejecute la tarea creada
        Thread thread1 = new Thread(task);
        thread0.start();//se ejecutan dos hilos en este punto, el segundo hilo ejecuta la tarea nuevamente
        //thread0.join();//el principal espera a que el que ha creado haya terminado su tarea, se respeta el orden. Podriamos correrlo en linux haciendo un loop pa ver si el orden
        thread1.start();
        //thread1.join();
        System.out.println("Done!");
        System.exit(1);//termina la ejecucion del proceso. No le dio tiempo a terminar dde ejecutarse al hilo hijo 0
    }
}
