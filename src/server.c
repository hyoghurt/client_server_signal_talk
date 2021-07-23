/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:51:14 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/07/23 18:40:34 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
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
	if (sigaction(SIGUSR1, &sa, 0) != 0)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) != 0)
		return (1);
	if (!start())
		return (1);
	while (1)
		sleep(1);
	return (0);
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

void	term_handler(int sig, siginfo_t *info, void *v)
{
	static char				r;
	static unsigned char	c;

	if (sig == 0 && v == 0)
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
			if (!t_print(r, info->si_pid))
				exit (1);
			r = 0;
			c = 128;
		}
		usleep(50);
		if (kill(info->si_pid, SIGUSR1) == -1)
			exit (1);
	}
}

int	t_print(char r, pid_t pid)
{
	if (r == 0)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (0);
		write(1, "\n", 1);
	}
	else
		write(1, &r, 1);
	return (1);
}
