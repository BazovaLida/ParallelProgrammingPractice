import java.util.Arrays;

public class Thread_F2 extends Thread {
    public void run(){
        System.out.printf("Thread 2 is started with name %s, priority %d%n", getName(), getPriority());

        int n = 10;
        int c = 1;
        Data data = new Data(n);
        data.F2_input(c);

        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        data.F2_calc();

        int[][] MG = data.F2_result();
        System.out.println("\nThread 2 is finished. Result: MG = \n" + Arrays.deepToString(MG));
    }
}