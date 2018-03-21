#include <iostream>
#include <chrono>
using namespace std;

#include <omp.h>

void hello_openmp()
{
	#pragma omp parallel
	cout<< "Hello, OpenMP ";
}

int main()
{
	hellp_openmp();
	
	getchar();
	return 0;
}