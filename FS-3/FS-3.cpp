#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
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
	int f = open(path, O_WRONLY);
	
	if(f < 0)
	{
		std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
		exit(errno);
	}
	int seek = lseek(f, 0, SEEK_SET); 
	if(seek < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	char* zeros = new char[21];
	for(int i = 0;i<21;i++)
	{
		zeros[i] = '\0';
	}
	struct stat st;
	fstat(f,&st);
	int fsize = st.st_size;
	int written = 0;
	while(written < fsize)
	{
		int wc = write(f,zeros,21);
		if(wc < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(errno);
		}
		written += wc;
	}
	int removing_code = unlink(path);
	if(removing_code < 0)
	{
		std::cerr << errno << strerror(errno) << std::endl;
		exit(errno);
	}

	delete[] zeros;
	return 0;
}
