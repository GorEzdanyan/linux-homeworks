#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>


bool isprime(int n)
{
	for(int i = 2; i <= sqrt(n); ++i)
	{
		if(n % i == 0)
		{
			return false;
		}
	}
	
	return true;
}

int main()
{
	int pipe_fd1[2],pipe_fd2[2];
	int pipe_created = pipe(pipe_fd1);
	if(pipe_created == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(errno);	
	}
	
	pipe_created = pipe(pipe_fd2);
	if(pipe_created == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(errno);	
	}
	
	pid_t pid = fork();
	if(pid == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	
	int m;
	
	if(pid == 0)
	{
		close(pipe_fd1[1]);
		close(pipe_fd2[0]);
		while(true)
		{
			read(pipe_fd1[0], &m, sizeof(int));
			std::cout << "[Child] Calculating " << m << "-th prime number..." << std::endl;
			
			int tmp = m;
			int i = 2;
			while(tmp != 0)
			{
				tmp -= isprime(i++);
			}
			--i;
			
			std::cout << "[Child] Sending calculation result of prime(" << m << ")..." << std::endl; 
			write(pipe_fd2[1], &i, sizeof(int));
		}
		
		close(pipe_fd1[0]);
		close(pipe_fd2[1]);
	}
	else
	{
		close(pipe_fd1[0]);
		close(pipe_fd2[1]);
	
		int result;
		std::string _input;
		
		while(true)
		{
			std::cout << "[Parent] Please enter the number: ";
			std::cin >> _input;
			if(_input == "exit")
			{
				kill(pid, SIGKILL);
				exit(0);
			}
			
			m = std::stoi(_input);
			std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
			write(pipe_fd1[1], &m, sizeof(int));
			std::cout<< "[Parent] Waiting for the response from the child process..." << std::endl;
			read(pipe_fd2[0], &result, sizeof(int));
			std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << std::endl; 
		}
		
		close(pipe_fd1[1]);
		close(pipe_fd2[0]);
	}
	
	return 0;
}
