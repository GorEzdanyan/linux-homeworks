#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unistd.h>

void initialize(int argc, char** argv)
{
	  if(argc < 2)
	  {
	  	std::cerr << "No argument given" << std::endl;
	  	exit(-1);
	  }
	  int f  = open(argv[1], O_RDWR);
	  if(f < 0)
	  {
	  	std::cerr << strerror(errno) << std::endl;
		exit(errno);
	  }
	  int dup_return = dup2(f,0);
	  if(dup_return < 0)
	  {
	  	std::cerr << strerror(errno) << std::endl;
		exit(errno);
	  }
	  int closing_code = close(f);
	  if(closing_code < 0)
	  {
	  	std::cerr << strerror(errno) << std::endl;
		exit(errno);
	  }
}

int main(int argc, char** argv)
{

  // initialize the program based on the requirements
  initialize(argc, argv);

  // read the string 
  std::string input;
  std::cin >> input;
  
  // logic to get the reversed string
  reverse(input.begin(), input.end()); 

  // print to the console
  std::cout << input << std::endl;

  return 0;
}

