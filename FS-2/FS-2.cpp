#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>


int main(int argc,char** argv)
{
	if(argc<3)
	{
		std::cerr<<"Not enough arguments";
		exit(-1);
	}

	char *path1 = argv[1];
	char *path2 = argv[2];
	int f1 = open(path1, O_RDONLY);
	int f2 = open(path2, O_WRONLY | O_CREAT | O_TRUNC);
	if(f1 < 0 || f2 < 0)
	{
		std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
		exit(errno);
	}

	char* buffer = new char[21];
	int rbytes = read(f1,buffer,20);
	while(rbytes != 0)
	{
		if(rbytes < 0)
		{
			std::cerr << strerror(errno) << std::endl;
		}
		buffer[rbytes] = '\0';
		write(f2,buffer,rbytes);
		rbytes = read(f1,buffer,20);
	}
	int closing_code1 = close(f1);
	int closing_code2 = close(f2);
	if(closing_code1 < 0 || closing_code2 < 0)
	{
		std::cerr << errno << strerror(errno) << std::endl;
		exit(errno);
	}

	delete[] buffer;
	return 0;
}

