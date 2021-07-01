#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minitalk.h"

void term_handler(int sig, siginfo_t *info, void *vo)
{
	static char				r;
	static unsigned char	c;

	if (sig == 0)
	{
		r = 0;
		c = 128;
	}
	else
	{
		if (sig == SIGUSR1)
			r += c;
		c /= 2;
		if (c < 1)
		{
			if (r == 0)
				write(1, "\n", 1);
			else
				write(1, &r, 1);
			r = 0;
			c = 128;
		}
		kill(info->si_pid, SIGUSR1);
	}
}

int	start(void)
{
	char	*pid;
	int		i;

	term_handler(0, 0, 0);
	pid = ft_itoa(getpid());
	if (!pid)
		return (0);
	i = -1;
	while (pid[++i])
		write(1, &pid[i], 1);
	write(1, "\n", 1);
	free(pid);
	return (1);
}

int main(void)
{
	struct sigaction	sa;
	sigset_t			newset;

	if (sigaddset(&newset, SIGUSR1) != 0)
		return (1);
	if (sigaddset(&newset, SIGUSR2) != 0)
		return (1);
	if (sigemptyset(&newset) != 0)
		return (1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = term_handler;
	//sa.sa_handler = term_handler;
	//sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, 0) != 0)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) != 0)
		return (1);
	if (!start())
		return (1);
	while(1)
		usleep(100);
	return (0);
}
