#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <queue>
#include <vector>
#include <pthread.h>

typedef void* (*pool_function_t)(void*);

struct function_call
{
	pool_function_t function;
	void* arg;
};


class parallel_scheduler
{
	private:
		int capacity;
		pthread_mutex_t* mutex;
		std::queue<function_call> functions;
		std::vector<pthread_t> threads;
		void create_threads();
		static void* execute(void* arg);
	public:
		parallel_scheduler(int capacity);
		~parallel_scheduler();
		void run(pool_function_t function, void* arg);
};

#endif
