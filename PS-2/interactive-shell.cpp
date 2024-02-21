#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <bits/stdc++.h>
#include <limits.h>

void do_command(char** argv)
{

	pid_t my_process = fork();
	if(my_process < 0)
	{
		std::cout << strerror(errno) << std::endl;
		exit(errno);
	}

	if(my_process == 0)
	{
		int execvp_code = execvp(argv[0], argv);
		if(execvp_code == -1)
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
	}

}

int main()
{
	char* command[100];
	for(int i = 0; i < 100; i++)
	{
		command[i] = new char[20];
	}
	int index;
	bool index_is_used;
	std::string str;
	while(true)
	{
		index_is_used = false;
		index = 0;
		std::getline(std::cin,str);
		for(int i = 0,j = 0; str[j] != 0; j++)
		{
			if(str[j] == ' ')
			{
				if(index_is_used)
				{
					command[index][i] = 0;
					index++;
					i = 0;
					index_is_used = false;
				}
				continue;
			}
			index_is_used = true;
			command[index][i] = str[j];	
			i++;	
		}
		char* tmp = command[index+1];
		command[index+1] = nullptr;
		do_command(command);
		command[index+1] = tmp;
	}
	for(int i = 0; i < 100; i++)
	{
		delete[] command[i];
	}
	return 0;
}
