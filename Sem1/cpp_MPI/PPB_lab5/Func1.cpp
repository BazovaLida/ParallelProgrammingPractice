#include "Func1.h"

Func1::Func1(int N) {
	this->N = N;
}

Vector* Func1::getResult() {
	return result;
}

DWORD WINAPI Func1::startThread(void* param) {
	F1* This = (F1*)param;
	return This->run();
}

DWORD Func1::run() {
	cout << "Task 1 start\n";
	long* e = new long(3);
	Vector* A = new Vector(N), * B = new Vector(N);
	Matrix* MA = new Matrix(N), * MC = new Matrix(N);
	result = A->sub((MA->multiply(MC))->multiply(B)->multiply(e));
	cout << "Task 1 end\n";
	delete A;
	delete B;
	delete e;
	delete MA;
	delete MC;
	return 0;
}
