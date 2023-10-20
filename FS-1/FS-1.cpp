#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>


int main(int argc,char** argv)
{
	if(argc<2)
	{
		std::cerr<<"File path was not found";
		exit(-1);
	}

	char *path = argv[1];
	int f = open(path, O_RDONLY);
	if(f < 0)
	{
		std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
		exit(errno);
	}

	char* buffer = new char[21];
	int rbytes = read(f,buffer,20);
	while(rbytes != 0)
	{
		if(rbytes < 0)
		{
			std::cerr << strerror(errno) << std::endl;
		}
		buffer[rbytes] = '\0';
		std::cout << buffer;
		rbytes = read(f,buffer,20);
	}
	int closing_code = close(f);
	if(closing_code < 0)
	{
		std::cerr << errno << strerror(errno) << std::endl;
		exit(errno);
	}

	delete[] buffer;
	return 0;
}
