#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void term_handler (int i, siginfo_t *info, void *vo)
{
	if (info->si_value.sival_int == 0)
		write (1, "\n", 1);
	else
		write (1, &(info->si_value.sival_int), 1);
	//kill(info->si_pid, SIGUSR2);
}

int main (int argc, char ** argv)
{
	struct sigaction	sa;
	sigset_t			newset;



	sigemptyset(&newset);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = term_handler;

	sigaction(SIGUSR1, &sa, 0);
	printf("%i\n", getpid());
	while(1)
	{
		pause();
		//sleep(1);
	}
	return (0);
}
