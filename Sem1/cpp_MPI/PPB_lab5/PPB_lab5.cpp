#include <iostream>
#include "Data.h"
#include <mpi.h>
#include <windows.h>

void Func1();
void Func2();
void Func3();

  int c = 1;
static const int n = 100;
Data data = Data(n);

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv); //ініціалізація паралельної частини програми
    
    int rank;               //ідентифікатор задачі
    int size;               //кількість задач, що буде розміщена в комунікаторі

    MPI_Comm_size(MPI_COMM_WORLD, &size);//MPI_COMM_WORLD - стартовий комуныкатор
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);//отримання ідентифікатору задачі

    if (rank == 0) {
        std::cout << "\nThread with main function is started.\nRank = "<< rank << std::endl;
        std::cout << "Number of tasks in this communicator = "<< size << std::endl;
    }
    else if (rank == 1) {
        std::cout << "Thread 1 is started\nF1: d = (A * ((B + C) * (MA * ME))).\nRank = " << rank << std::endl;
        Func1();
    }
    else if (rank == 2) {
        std::cout << "Thread 2 is started\nF2: MG = SORT(MF) * MK + ML\nRank = " << rank << std::endl;
        Func2();
    }
    else if (rank == 3) {
        std::cout << "Thread 3 is started\nF3: O = SORT(R + S) * (MT * MP)\nRank = " << rank << std::endl;
        Func3();
    }

    MPI_Finalize();

    return 0;
}

//F1: d = (A * ((B + C) * (MA * ME)))
void Func1() {
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
    data.F3_input(c);
    data.F3_calc();
    int* O = data.F3_result();

    std::cout << "Result F3: O = {";
    data.print_vector(O);
    data.F3_clean();
    std::cout << "Thread 3 is finished" << std::endl;
}
