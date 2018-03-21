#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello_openmp()
{
	#pragma omp parallel
	{

		printf("Hello, OpenMP %d / %d", omp_get_thread_num(), omp_get_num_threads());
	}
}

void sections()
{
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for(int i=0; i<10; i++) {
				printf("%d ", i);
			}
		}
		#pragma omp section
		{
			for(int i=-10; i<0; i++) {
				printf("%d ", i);
			}
		}
	}
}

int main()
{

	//hello_openmp();

	sections();  

	return 0;
}