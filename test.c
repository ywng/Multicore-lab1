#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello_openmp()
{
	#pragma omp parallel
	printf("Hello, OpenMP ");
}

int main()
{
	omp_set_num_threads(8);
	
	hello_openmp();

	return 0;
}