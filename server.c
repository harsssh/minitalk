/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:33:13 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/29 14:43:53 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include <signal.h>
#include <unistd.h>
#include "ft_stdio.h"

#define CHAR_BIT_LEN 8

void	handle_signal_with_info(int signum, siginfo_t *info, void *context)
{
	static char	character = 0;
	static int	bits_received = 0;

	(void)context;
	character <<= 1;
	if (signum == SIGUSR2)
		character |= 1;
	bits_received++;
	if (bits_received == CHAR_BIT_LEN) {
		write(STDOUT_FILENO, &character, 1);
		bits_received = 0;
		character = 0;
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
