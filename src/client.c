#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "minitalk.h"

void	set_nl(int pid)
{
	unsigned char	i;

	i = 128;
	while (i >= 1)
	{
		kill(pid, SIGUSR2);
		i /= 2;
		usleep(200);
	}
}

void	set_space(int pid)
{
	unsigned char	i;

	i = 128;
	while (i >= 1)
	{
		if (' ' & i)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i /= 2;
		usleep(200);
	}
}

void	set_string(int pid, char *s)
{
	unsigned char	i;

	while (*s)
	{
		i = 128;
		while (i >= 1)
		{
			if (*s & i)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i /= 2;
			usleep(200);
		}
		s++;
	}
}

void	exec(int pid, char **argv)
{
	unsigned char	i;
	char			*s;
	int				j;

	j = 2;
	while (argv[j])
	{
		if (j != 2)
			set_space(pid);
		set_string(pid, argv[j]);
		j++;
	}
	set_nl(pid);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc < 3)
		return (0);
	//check value argv[1]
	pid = ft_atoi(argv[1]);
	exec(pid, argv);
	return (0);
}
