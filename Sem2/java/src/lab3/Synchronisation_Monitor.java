package lab3;
//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.Synchronisation_Monitor.java file

public class Synchronisation_Monitor {
    private int a = 0;

    private int F1 = 0; //max: 2 (for B and Z)
    private int F2 = 0; //max: 4 (for a)
    private int F3 = 0; //max: 3 (for X)

    public synchronized void wait_In(){
        try {
            if (F1 != 2)
                wait();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }
    public synchronized  void wait_a(){
        try {
            if (F2 != 4)
                wait();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }
    public synchronized  void wait_Out(){
        try {
            if (F3 != 3)
                wait();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }

    public synchronized void signal_In(){
        F1 = F1 + 1;
        if(F1 == 2)
            notifyAll();
    }
    public synchronized void signal_Out(){
        F3 = F3 + 1;
        if(F3 == 3)
            notify();
    }

    public synchronized void put_a(int x){
        a = a + x;
    }
    public synchronized void signal_a(){
        F2 = F2 + 1;
        if(F2 == 4)
            notifyAll();
    }
    public synchronized int get_a() {
        return a;
    }
}
