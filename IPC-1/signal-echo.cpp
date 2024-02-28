#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <sys/ucontext.h>
#include <unistd.h>

void signal_handler(int sig_num, siginfo_t *info, void* ucontext)
{
	ucontext_t* _ucontext = (ucontext_t*)ucontext;
	
	long long rip = _ucontext->uc_mcontext.gregs[REG_RIP];
	long long rax = _ucontext->uc_mcontext.gregs[REG_RAX];
	long long rbx = _ucontext->uc_mcontext.gregs[REG_RBX];
	
	std::cout << "Received SIGUSR1 signal from process " << info->si_pid << " executed by " 
	<< info->si_uid << " (" << getpwuid(info->si_uid)->pw_name << ")" << " RIP = " 
	<< rip << ", RAX = " << rax << ", RBX = " << rbx << std::endl;
	
}

int main()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	
	int sigaction_result = sigaction(10, &action, NULL);
	
	std::cout<< "Process id is: " << getpid() << std::endl;
	
	if(sigaction_result < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	
	while(true)
	{
		sleep(5);	
	}
	
	return 0;
}
