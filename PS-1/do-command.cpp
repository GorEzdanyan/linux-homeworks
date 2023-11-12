#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <bits/stdc++.h>
#include <chrono>


void do_command(char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
	pid_t my_process = fork();
	if(my_process < 0)
	{
		std::cout << strerror(errno) << std::endl;
		exit(errno);
	}

	if(my_process == 0)
	{
		const char *pathname = argv[1];
		int exelp_code = execvp(pathname, &argv[1]);
		if(exelp_code == -1)
		{
			std::cout << strerror(errno) << std::endl;
			exit(errno);
		}
	}
	else
	{
		int exit_status;
		int wait_code = waitpid(my_process, &exit_status, 0);
		if(wait_code == -1)
		{
			std::cout << strerror(errno) << std::endl;
			exit(errno);	
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Executed in " << duration.count() << " microseconds" << std::endl;
		if(WIFEXITED(exit_status))
		{
			std::cout << "Exit status " << WEXITSTATUS(exit_status) << std::endl;
		}
	}

}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cout << "No command given" << std::endl;
		return -1;
	}
	
	do_command(argv);
	return 0;
}
