#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_check_digit(char *s);
///server
int		start(void);
void	term_handler(int sig, siginfo_t *info, void *v);
int		t_print(char r, pid_t pid);
///client
void	term_handler_cl(int i);
void	set_string(int pid, char *s);
void	set_nl(int pid);

#endif
