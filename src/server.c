#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minitalk.h"

void term_handler(int sig)
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
	}
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
	sa.sa_handler = term_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, 0) != 0)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) != 0)
		return (1);
	term_handler(0);
	printf("%i\n", getpid());
	while(1)
		pause();
	return (0);
}
