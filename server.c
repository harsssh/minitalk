/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:33:13 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 02:01:12 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define CHAR_BIT_LEN 8

void	handle_request(int signum, siginfo_t *info, void *context)
{
	static char		c;
	static int		bits_received;
	static pid_t	client_pid;

	(void)context;
	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1;
	bits_received++;
	if (bits_received == CHAR_BIT_LEN)
	{
		write(STDOUT_FILENO, &c, 1);
		bits_received = 0;
		c = 0;
	}
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (kill(client_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("Error: failed to send signal", STDERR_FILENO);
		exit(1);
	}
}

int	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_request;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_dprintf(STDOUT_FILENO, "Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
