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
	int pipe_fd[2];
	int pipe_created = pipe(pipe_fd);
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
		
		read(pipe_fd[0], &m, sizeof(int));
		std::cout << "[Child] Calculating " << m << "-th prime number..." << std::endl;
		
		int tmp = m;
		int i = 2;
		while(tmp != 0)
		{
			tmp -= isprime(i++);
		}
		--i;
		
		std::cout << "[Child] Sending calculation result of prime(" << m << ")..." << std::endl; 
		write(pipe_fd[1], &i, sizeof(int));
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	else
	{
		int result;
		std::cout << "[Parent] Please enter the number: ";
		std::cin >> m;
		std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
		write(pipe_fd[1], &m, sizeof(int));
		
		std::cout<< "[Parent] Waiting for the response from the child process..." << std::endl;
		wait(NULL);
		read(pipe_fd[0], &result, sizeof(int));
		std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << std::endl; 
		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	
	return 0;
}
