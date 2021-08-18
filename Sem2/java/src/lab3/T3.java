package lab3;//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.T3.java file

import lab3.Lab3;
import lab3.Resources_Monitor;
import lab3.Synchronisation_Monitor;

public class T3 extends Thread{
    private final Synchronisation_Monitor mS;
    private final Resources_Monitor mR;
    private final int H;

    public T3(Synchronisation_Monitor synch_m, Resources_Monitor res_m){
        mS = synch_m;
        mR = res_m;
        H = Lab3.H;
    }

    @Override
    public void run(){
        System.out.println("Process lab3.T3 is started!");
//1   Введення B
        Lab3.B = Lab3.getNewVector();
//2   Сигнал задачам Т1, Т2, Т4 про введення Z
        mS.signal_In();
//3   Введення MR
        Lab3.MR = Lab3.getNewMatrix();
//4   Чекати на введення Z у задачі Т2
        mS.wait_In();
//5   Обчислення а3 = (BH * ZH)
        int a3 = 0;
        for (int i = H * 2; i < H * 3; i++)
            a3 += Lab3.B[i] * Lab3.Z[i];
//6   Обчислення a = a + a3
        mS.put_a(a3);
//7   Сигнал про завершення обчислень а задачам Т1, Т2, Т4
        mS.signal_a();
//8   Чекати на завершення обчислень а в задачах Т1, Т2, Т4
        mS.wait_a();
//9   Копіювання MO3 = MO
        int[][] MO3 = mR.get_MO();
//10      Копіювання R3 = R
        int[] R3 = mR.get_R();
//11      Копіювання d3 = d
        int d3 = mR.get_d();
//12      Копіювання a3 = a
        a3 = mS.get_a();
//13      Обчислення XH = a3*(d3*ZH + R3*(MO3*MRH))
        Lab3.function(H * 2, a3, d3, R3, MO3);
//14      Сигнал задачі Т4 про завершення обчислень X
        mS.signal_Out();
        System.out.println("Process lab3.T3 is finished!");
    }
}
