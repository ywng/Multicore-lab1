#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello_openmp()
{
	#pragma omp parallel
	prinf("Hello, OpenMP ");
}

int main()
{
	hellp_openmp();

	return 0;
}