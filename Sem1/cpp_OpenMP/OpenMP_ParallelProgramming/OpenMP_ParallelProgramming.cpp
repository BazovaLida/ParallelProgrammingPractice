#include <iostream>
#include "Data.h"
#include <omp.h>

void Func1();
void Func2();
void Func3();
int c = 1;
static const int n = 100;
Data data = Data(n);

int main()
{
    std::cout << "\nThread with main function is started" << std::endl;

    omp_set_num_threads(3);
#pragma omp parallel
    {
#pragma omp sections
        {
                Func1();
                Func2();
                Func3();
        }
    }

    std::cout << "\nThread with main function is finished" << std::endl;
    return 0;
}

//F1: d = (A * ((B + C) * (MA * ME)))
void Func1() {
    std::cout << "Thread 1 is started\nF1: d = (A * ((B + C) * (MA * ME)))" << std::endl;

    data.F1_input(c);
    data.F1_calc();
    int d = data.F1_result();
    //    Thread.Yield();

    std::cout << "Result F1:\nd = " << d << std::endl;
    data.F1_clean();
    std::cout << "Thread 1 is finished" << std::endl;
}

//F2: MG = SORT(MF) * MK + ML
void Func2()
{
    std::cout << "Thread 2 is started\nF2: MG = SORT(MF) * MK + ML" << std::endl;

    data.F2_input(c);
    data.F2_calc();
    int** MG = data.F2_result();

    std::cout << "Result F2: MG = {" << std::endl;
    data.print_matrix(MG);
    data.F2_clean();
    std::cout << "Thread 2 is finished" << std::endl;
}

//F3: O = SORT(R + S) * (MT * MP)
void Func3()
{
    std::cout << "Thread 3 is started\nF3: O = SORT(R + S) * (MT * MP)" << std::endl;

    data.F3_input(c);
    data.F3_calc();
    int* O = data.F3_result();

    std::cout << "Result F3: O = {";
    data.print_vector(O);
    data.F3_clean();
    std::cout << "Thread 3 is finished" << std::endl;
}
