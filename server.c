/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:33:13 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/29 02:33:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <wchar.h>

pid_t	handle_pid_signal(int signum)
{
	static pid_t	client_pid = 0;
	static int		received_bits = 0;
	static int		pid_bit_length = sizeof(pid_t) * 8;

	if (signum == SIGUSR1)
		client_pid = (client_pid << 1);
	else if (signum == SIGUSR2)
		client_pid = (client_pid << 1) | 1;
	received_bits++;
	if (received_bits == pid_bit_length)
	{
		printf("Received client PID: %d\n", client_pid);
		received_bits = 0;
		return (client_pid);
	}
	return (0);
}

bool	handle_character_signal(int signum, pid_t client_pid)
{
	static wchar_t	character = 0;
	static int		bits_received = 0;
	static int		character_bit_length = sizeof(wchar_t) * 8;

	if (signum == SIGUSR1)
		character = character << 1;
	else if (signum == SIGUSR2)
		character = (character << 1) | 1;
	bits_received++;
	if (bits_received == character_bit_length)
	{
		bits_received = 0;
		if (character == (wchar_t)(-1))
		{
			character = 0;
			return (true);
		}
		wprintf(L"%lc", character);
		character = 0;
	}
	kill(client_pid, SIGUSR1);
	return (false);
}

void	handle_signal(int signum)
{
	static bool		receiving_pid = true;
	static pid_t	client_pid = 0;
	pid_t			received_pid;

	if (receiving_pid)
	{
		received_pid = handle_pid_signal(signum);
		if (received_pid != 0)
		{
			client_pid = received_pid;
			receiving_pid = false;
		}
	}
	else
		receiving_pid = handle_character_signal(signum, client_pid);
}

int	main(void)
{
	struct sigaction	act;

	printf("Server PID: %d\n", getpid());
	act.sa_handler = handle_signal;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
