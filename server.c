/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:33:13 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/30 09:46:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <locale.h>
#include <signal.h>
#include <unistd.h>

#define CHAR_BIT_LEN 8

void	handle_signal_with_info(int signum, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bits_received = 0;

	ft_printf("arrived! (%d)\n", info->si_pid);
	(void)c;
	(void)context;
	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1;
	bits_received++;
	if (bits_received == CHAR_BIT_LEN)
	{
		//write(STDOUT_FILENO, &c, 1);
		bits_received = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handle_signal_with_info;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
