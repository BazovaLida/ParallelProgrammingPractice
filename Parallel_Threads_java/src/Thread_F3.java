import java.util.Arrays;

public class Thread_F3 extends Thread {
    public void run(){
        System.out.printf("Thread 3 is started with name %s, priority %d%n", getName(), getPriority());

        int n = 10;
        int c = 1;
        
        Data data = new Data(n);
        Thread.yield();
        data.F3_input(c);

        data.F3_calc();

        int[] O = data.F3_result();
        System.out.println("\nThread 3 is finished. Result: O = \n" + Arrays.toString(O));
    }
}