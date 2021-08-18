#include <iostream>
#include "Data.h"
#include <windows.h>

Data data = Data(100);
void th_1();
void th_2();
void th_3();
int c = 1;

int main()
{
    DWORD th_dw1, th_dw2, th_dw3;

    HANDLE T1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)th_1, NULL, 0, &th_dw1);
    HANDLE T2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)th_2, NULL, 0, &th_dw2);
    HANDLE T3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)th_3, NULL, 0, &th_dw3);

    WaitForSingleObject(T1, INFINITE);
    WaitForSingleObject(T2, INFINITE);
    WaitForSingleObject(T3, INFINITE);

    CloseHandle(T1);
    CloseHandle(T2);
    CloseHandle(T3);

    std::cout << "\nThread with main function is finished"  << std::endl;
    return 0;
}

//F1: d = (A * ((B + C) * (MA * ME)))
void Func1(){
    std::cout << "Thread 1 is started\nF1: d = (A * ((B + C) * (MA * ME)))" << std::endl;

    data.F1_input(c);
    Sleep(5000);
    data.F1_calc();
    int d = data.F1_result();
//    Thread.Yield();
    Data.F1_clean;

    std::cout << "Result F1:\nd = " << d << std::endl;
    delete d;
    std::cout << "Thread 1 is finished" << std::endl;
}

//F2: MG = SORT(MF) * MK + ML
void Func2()
{
    std::cout << "Thread 2 is started\nF2: MG = SORT(MF) * MK + ML" << std::endl;

    data.F2_input(c);
    data.F2_calc();
    Sleep(1000);
    int** MG = data.F2_result();
    data.F2_clean;


    std::cout << "Result F2: MG = {" << std::endl;
    for (int i = 0; i < MG.length; ++i) {
        for (int j = 0; j < MG[i].length; ++j) {
            std::cout << MG[i][j] << " ";
        } std::cout << ";" << std::endl;
    } std::cout << "}" << std::endl;

    for (int i = 0; i < MG.length; ++i) {
        delete [] MG[i];
    } std::cout << "Thread 2 is finished" << std::endl;
}

//F3: O = SORT(R + S) * (MT * MP)
void Func3()
{
    std::cout << "Thread 3 is started\nF3: O = SORT(R + S) * (MT * MP)" << std::endl;

    data.F3_input(c);
    data.F3_calc();
    int* O = data.F3_result();
    data.F3_clean;

    std::cout << "Result F3: O = {";
    for (int i = 0; i < O.length; ++i) {
        std::cout << O[i] << " ";
    } std::cout << "}" << std::endl;

    delete[] O;
    std::cout << "Thread 3 is finished" << std::endl;
}
