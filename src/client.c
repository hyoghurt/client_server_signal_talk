/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:51:06 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/07/09 19:51:08 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int		pid;
	int		j;

	signal(SIGUSR1, term_handler_cl);
	signal(SIGUSR2, term_handler_cl);
	if (argc < 3)
		return (1);
	if (ft_check_digit(argv[1]))
		return (1);
	pid = ft_atoi(argv[1]);
	j = 2;
	set_string(pid, argv[j]);
	set_nl(pid);
	return (0);
}

void	term_handler_cl(int i)
{
	if (i == SIGUSR1)
		return ;
	if (i == SIGUSR2)
		write(1, "\033[1;32;5;58mready\033[0m\n", 22);
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
			{
				if (kill(pid, SIGUSR1) == -1)
					exit (1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit (1);
			}
			pause();
			i /= 2;
			usleep(100);
		}
		s++;
	}
}

void	set_nl(int pid)
{
	unsigned char	i;

	i = 128;
	while (i >= 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit (1);
		pause();
		i /= 2;
		usleep(100);
	}
}
