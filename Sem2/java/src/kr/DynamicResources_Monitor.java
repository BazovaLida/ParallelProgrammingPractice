package kr;
//Parallel and distributed computing
//ПРГ1
//Variant 29
//d   = ( (A*MB)*(B* (MZ*MR) ) + max (Z)
//Bazova Lida
//IV-81
//Date: 23.03.2020
//DynamicResources_Monitor.java file

public class DynamicResources_Monitor {
    private int a = 0;
    private int b = Integer.MIN_VALUE;

    public synchronized void put_a(int x){
        a = a + x;
    }
    public synchronized void put_b(int x){
        if(b < x)
            b = x;
    }

    public synchronized int get_a() {
        return a;
    }
    public synchronized int get_b() {
        return b;
    }
}
