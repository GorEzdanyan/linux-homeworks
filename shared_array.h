#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

class shared_array
{
	private:
		int* arr;
		int fd;
		int size;
	public:
		shared_array(char*, unsigned);
		~shared_array();
		int& operator[](int);
		
};

#endif


