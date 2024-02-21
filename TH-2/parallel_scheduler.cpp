#include "parallel_scheduler.h"
#include <string.h>
#include <iostream>
#include <string.h>

parallel_scheduler::parallel_scheduler(int capacity) : capacity(capacity)
{
	pthread_mutex_init(mutex, nullptr);
	create_threads();
}
void parallel_scheduler::run(pool_function_t function, void* arg)
{
	pthread_mutex_lock(mutex);
	function_call fcall;
	fcall.function = function;
	fcall.arg = arg;
	functions.push(fcall);
	pthread_mutex_unlock(mutex);
}

void parallel_scheduler::create_threads()
{	
	for(int i = 0; i < capacity; ++i)
	{
		pthread_t thread;
		int creating_code = pthread_create(&thread, NULL, execute, this);
		if(creating_code != 0)
		{
			std::cerr << strerror(creating_code) << std::endl;
			exit(creating_code);
		}
		threads.push_back(thread);
	}

}

void* parallel_scheduler::execute(void* arg)
{
	parallel_scheduler* pl_arg = (parallel_scheduler*)arg;
	while(pl_arg->functions.size() != 0)
	{
		pthread_mutex_lock(pl_arg->mutex);
		pl_arg->functions.front().function(pl_arg->functions.front().arg);
		pl_arg->functions.pop();
		pthread_mutex_unlock(pl_arg->mutex);
	}
	return 0;
}

parallel_scheduler::~parallel_scheduler()
{
	for(int i = 0; i < threads.size(); ++i)
	{
		pthread_join(threads[i], nullptr);
	}
	pthread_mutex_destroy(mutex);
}


