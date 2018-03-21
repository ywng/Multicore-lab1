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
		#pragma omp single nowait
		{
			getchar();
			printf("imagine we are gathering some input bdefore we can start parallel work: %d\n", omp_get_thread_num());
		}
		

		//doing things in parallel 
		printf("imagine we are doing some tasks in parallel, thread: %d\n", omp_get_thread_num());

		#pragma omp barrier
		#pragma omp master
		printf("use master thread to output thte result, on thread: %d\n", omp_get_thread_num());
	}
}

void sync()
{
	printf("ORDERED\n");

	#pragma omp parallel for ordered
	for (int i = 0; i < 20; ++i)
	{
		//assume this is computation heavy... which worth to parallel
		int j = i*i;

		#pragma omp ordered
		printf("%d ", j);
	}
}

void data_sharing()
{
	int i=10;

	#pragma omp parallel for firstprivate(i)
	for(int a=0; a<10; a++) 
	{
		printf("thread %d i = %d\n", omp_get_thread_num(), i);
		i = 1000 + omp_get_thread_num();
	}

	printf("%d\n", i);

}

int main()
{

	//hello_openmp();
	//sections();  
	//single_master();
	//sync();
	data_sharing();

	return 0;
}