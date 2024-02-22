#include "shared_array.h"
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <cstdlib>

const char* semaphore = "IPC_SEM";

#define SEM_SIZE sizeof(sem_t)
int main()
{
	char* name = "arr";
	shared_array arr(name,10);
	sem_t* sem = sem_open(semaphore, O_CREAT, 0666, 1);
	
	int i = 0;
	while(true)
	{
		sem_wait(sem);
		if(i >= 10)
		{
			i = 0;
		}
		arr[i++] = rand();
		sem_post(sem);
	}

	sem_destroy(sem);

	return 0;
}
