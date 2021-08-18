package kr;
//Parallel and distributed computing
//ПРГ1
//Variant 29
//d   = ( (A*MB)*(B* (MZ*MR) ) + max (Z)
//Bazova Lida
//IV-81
//Date: 23.03.2020
//Synchron_Monitor.java file

public class Synchron_Monitor {
    //Синхронізація вводу даних для обчислення першої формули
    private int F1 = 0; //max: 2

    //Синхронізація завершення обчислень b та a для виведення результату
    private int F2 = 0; //max: P-1

    public synchronized void wait_In(){
        try {
            if (F1 != 2)
                wait();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }

    public synchronized void wait_a_b(){
        try {
            if (F2 != (PRG1.P - 1))
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

    public synchronized void signal_a_b(){
        F2 = F2 + 1;
        if(F2 == (PRG1.P - 1))
            notify();
    }
}
