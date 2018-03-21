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

void single_master()
{
	#pragma omp parallel
	{
		#pragma omp single
		printf("imagine we are gathering some input bdefore we can start parallel work: %d\n", omp_get_thread_num());

		//doing things in parallel 
		printf("imagine we are doing some tasks in parallel, thread: %d\n", omp_get_thread_num());

		#pragma omp master
		printf("use master thread to output thte result, on thread: %d\n", omp_get_thread_num());
	}
}

int main()
{

	//hello_openmp();
	//sections();  



	return 0;
}