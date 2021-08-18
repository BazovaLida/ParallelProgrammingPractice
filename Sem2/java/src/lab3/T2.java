package lab3;//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.T2.java file

import lab3.Lab3;
import lab3.Resources_Monitor;
import lab3.Synchronisation_Monitor;

public class T2 extends Thread{

    private final Synchronisation_Monitor mS;
    private final Resources_Monitor mR;
    private final int H;

    public T2(Synchronisation_Monitor synch_m, Resources_Monitor res_m){
        mS = synch_m;
        mR = res_m;
        H = Lab3.H;
    }

    @Override
    public void run(){
        System.out.println("Process lab3.T2 is started!");
//1  	Введення Z
        Lab3.Z = Lab3.getNewVector();
//2  	Сигнал задачам Т1, Т3, Т4 про введення Z
        mS.signal_In();
//3  	Введення R
        mR.set_R(Lab3.getNewVector());
//4  	Чекати на введення B у задачі Т3
        mS.wait_In();
//5  	Обчислення а2 = (BH * ZH)
        int a2 = 0;
        for (int i = H; i < H * 2; i++)
            a2 += Lab3.B[i] * Lab3.Z[i];
//6  	Обчислення a = a + a2
        mS.put_a(a2);
//7  	Сигнал про завершення обчислень а задачам Т1, Т3, Т4
        mS.signal_a();
//8  	Чекати на завершення обчислень а в задачах Т1, Т3, Т4
        mS.wait_a();
//9  	Копіювання MO2 = MO
        int[][] MO2 = mR.get_MO();
//10  	Копіювання R2 = R
        int[] r2 = mR.get_R();
//11  	Копіювання d2 = d
        int d2 = mR.get_d();
//12  	Копіювання a2 = a
        a2 = mS.get_a();
//13  	Обчислення XH = a2*(d2*ZH + R2*(MO2*MRH))
        Lab3.function(H, a2, d2, r2, MO2);
//14  	Сигнал задачі Т4 про завершення обчислень X
        mS.signal_Out();
        System.out.println("Process lab3.T2 is finished!");
    }
}
