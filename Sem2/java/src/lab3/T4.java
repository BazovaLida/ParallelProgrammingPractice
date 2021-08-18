package lab3;//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.T4.java file

import lab3.Lab3;
import lab3.Resources_Monitor;
import lab3.Synchronisation_Monitor;

public class T4 extends Thread{
    private final Synchronisation_Monitor mS;
    private final Resources_Monitor mR;
    private final int H;

    public T4(Synchronisation_Monitor synch_m, Resources_Monitor res_m){
        mS = synch_m;
        mR = res_m;
        H = Lab3.H;
    }

    @Override
    public void run(){
        System.out.println("Process lab3.T4 is started!");
//1  	Введення d
        mR.set_d(Lab3.c);
//2  	Чекати на введення B у задачі Т3 та Z у задачі Т2
        mS.wait_In();
//3  	Обчислення а4 = (BH * ZH)
        int a4 = 0;
        for (int i = H * 3; i < H * 4; i++)
            a4 += Lab3.B[i] * Lab3.Z[i];
//4  	Обчислення a = a + a4
        mS.put_a(a4);
//5  	Сигнал про завершення обчислень а задачам Т1, Т2, Т3
        mS.signal_a();
//6  	Чекати на завершення обчислень а в задачах Т1, Т2, Т3
        mS.wait_a();
//7  	Копіювання MO4 = MO
        int[][] MO4 = mR.get_MO();
//8  	Копіювання R4 = R
        int[] R4 = mR.get_R();
//9  	Копіювання d4 = d
        int d4 = mR.get_d();
//10  	Копіювання a4 = a
        a4 = mS.get_a();
//11  	Обчислення XH = a4*(d4*ZH + R4*(MO4*MRH))
        Lab3.function(H * 3, a4, d4, R4, MO4);
//12  	Чекати на завершення обчислень А в задачах Т1, Т2, Т3
        mS.wait_Out();
//13  	Виведення результату X
        System.out.print("Х = {");
        for (int item :Lab3.X)
            System.out.printf(item + " ");
        System.out.print("}\nProcess lab3.T4 is finished!");
    }
}
