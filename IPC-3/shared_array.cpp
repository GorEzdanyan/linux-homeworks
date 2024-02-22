#include "shared_array.h"


shared_array::shared_array(char *name, unsigned size) : size(size)
{
	fd = shm_open(name,O_RDWR | O_CREAT, 0666);
	if(fd == - 1)
	{
		std::cerr << "Error-" << strerror(errno) << std::endl;
		exit(errno);
	}
	
	int trunc_code = ftruncate(fd, size);
	if(trunc_code == - 1)
	{
		std::cerr << "Error-" << strerror(errno) << std::endl;
		exit(errno);
	}
	
	void* map_code = mmap(NULL, size, PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
	
	if(map_code == MAP_FAILED)
	{
		std::cerr << "Error-" << strerror(errno) << std::endl;
		exit(errno);
	}
	
	arr = (int*)map_code;
	
}

shared_array::~shared_array()
{
	int unmap_code = munmap((void*)arr, size);
	if(unmap_code == - 1)
	{
		std::cerr << "Error-" << strerror(errno) << std::endl;
		exit(errno);
	}
	
	int file_closed = close(fd);
	if(file_closed == - 1)
	{
		std::cerr << "Error-" << strerror(errno) << std::endl;
		exit(errno);
	}
}

int& shared_array::operator[](int index)
{
    if (index >= size) {
        std::cerr << "Array index out of bound" << std::endl;
        exit(-1);
    }
    return arr[index];
}
