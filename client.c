#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main (int argc, char ** argv)
{
	int				pid;
	union sigval	val;
	char			*s;
	int				i;
	sigset_t		newset;

	sigaddset(&newset, SIGUSR2);
	sigemptyset(&newset);

	i = 0;

	if (argc != 3)
		return (0);
	pid = atoi(argv[1]);
	s = argv[2];
	while (s[i])
	{
		val.sival_int = (int)s[i];
		sigqueue(pid, SIGUSR1, val);
		//pause();
		i++;
		sleep(1);
	}
	val.sival_int = (int)s[i];
	sigqueue(pid, SIGUSR1, val);
	sleep(1);
	return (0);
}
