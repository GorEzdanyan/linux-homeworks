#include <iostream>
#include <pthread.h>
#include "parallel_scheduler.h"

void* Task_Function(void* arg)
{
	int* n = (int*)arg;
	std::cout << *n << std::endl;
	return 0;
}

int main()
{
	parallel_scheduler thread_pool(10);
	for(int i = 0; i < 20; ++i)
	{
		thread_pool.run(Task_Function, &i);
	}
	return 0;
}

