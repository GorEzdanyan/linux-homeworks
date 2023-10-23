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
		std::cerr<<"File path was not found" << std::endl;
		exit(-1);
	}

	char *path = argv[1];
	int f = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(f < 0)
	{
		std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
		exit(errno);
	}
	int dup_f = dup(f);
	if(dup_f < 0)
	{
		std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
		exit(errno);
	}
	write(f,"First Line\n",11);
	write(dup_f, "Second Line\n",12);
	int closing_code = close(f);
	if(closing_code < 0)
	{
		std::cerr << errno << strerror(errno) << std::endl;
		exit(errno);
	}

	return 0;
}
