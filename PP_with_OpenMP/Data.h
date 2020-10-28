#pragma once

class Data {
public:
    Data(int n_given);
    void F1_input(int c);
    void F1_calc();
    int F1_result();
    void F1_clean();

    void F2_input(int c);
    void F2_calc();
    int** F2_result();
    void F2_clean();

    void F3_input(int c);
    void F3_calc();
    int* F3_result();
    void F3_clean();

    void print_matrix(int** MM);
    void print_vector(int* V);

private:
    int n;
    int d;          //result
    int* A;
    int* B;
    int* C;
    int** MA;
    int** ME;
    int** MF;
    int** MK;
    int** ML;
    int** MG;
    int* R;
    int* S;
    int* O;
    int** MT;
    int** MP;

    int** multiply_matrix(int** MA, int** MB);
    int* multiply_vec_matr(int* V, int** MA);
    int scalar_multiply_vec(int* A, int* B);

    int* sum_vec(int* A, int* B);
    int** sum_matrix(int** MA, int** MB);

    int** sort_matrix(int** MA);
    int* sort_vec(int* V);

    int* get_vec_with(int c);
    int** get_matrix_with(int c);
};
