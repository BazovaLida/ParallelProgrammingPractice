package lab3;//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.T1.java file

import lab3.Lab3;
import lab3.Resources_Monitor;
import lab3.Synchronisation_Monitor;

public class T1 extends Thread{
    private final Synchronisation_Monitor mS;
    private final Resources_Monitor mR;

    public T1(Synchronisation_Monitor synch_m, Resources_Monitor res_m){
        mS = synch_m;
        mR = res_m;
    }

    @Override
    public void run(){
        System.out.println("Process lab3.T1 is started!");
// 1	Введення MO
        mR.set_MO(Lab3.getNewMatrix());
// 2  	Чекати на введення B у задачі Т3 та Z у задачі Т2
        mS.wait_In();
// 3  	Обчислення а1 = (BH * ZH)
        int a1 = 0;
        for (int i = 0; i < Lab3.H; i++)
            a1 += Lab3.B[i] * Lab3.Z[i];
// 4  	Обчислення a = a + a1
        mS.put_a(a1);
// 5  	Сигнал про завершення обчислень а задачам Т2, Т3, Т4
        mS.signal_a();
// 6  	Чекати на завершення обчислень а в задачах Т2, Т3, Т4
        mS.wait_a();
// 7  	Копіювання MO1 = MO
        int[][] MO1 = mR.get_MO();
// 8  	Копіювання R1 = R
        int[] r1 = mR.get_R();
// 9  	Копіювання d1 = d
        int d1 = mR.get_d();
// 10  	Копіювання a1 = a
        a1 = mS.get_a();
// 11  	Обчислення XH = a1*(d1*ZH + R1*(MO1*MRH))
        Lab3.function(0, a1, d1, r1, MO1);
// 12  	Сигнал задачі Т4 про завершення обчислень X
        mS.signal_Out();
        System.out.println("Process lab3.T1 is finished!");
    }
}
