/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:25:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/30 17:30:36 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define CHAR_BIT_LEN 8
#define ACK_WAIT 10
#define ACK_TIMEOUT 1000000

volatile sig_atomic_t	g_received_ack = 0;

void	handle_ack(int sig)
{
	(void)sig;
	g_received_ack = 1;
}

void	wait_ack(void)
{
	unsigned int	wait_time;

	wait_time = 0;
	while (!g_received_ack)
	{
		usleep(ACK_WAIT);
		wait_time += ACK_WAIT;
		if (wait_time > ACK_TIMEOUT)
		{
			ft_putendl_fd("timeout", STDERR_FILENO);
			exit(1);
		}
	}
	g_received_ack = 0;
}

void	send_message(pid_t pid, const char *message)
{
	unsigned int	bit;
	char			c;

	while (*message)
	{
		c = *message++;
		bit = CHAR_BIT_LEN;
		while (bit--)
		{
			if (c & (1 << bit))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			wait_ack();
		}
	}
}

pid_t	parse_pid(const char *pid_str)
{
	unsigned int	i;
	pid_t			pid;

	i = 0;
	while (pid_str[i])
	{
		if (!ft_isdigit(pid_str[i]))
			return (-1);
		++i;
	}
	pid = ft_atoi(pid_str);
	if (pid <= 0)
		return (-1);
	return (pid);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putendl_fd(" <server_pid> <message>", STDERR_FILENO);
		return (1);
	}
	server_pid = parse_pid(argv[1]);
	if (server_pid == -1)
	{
		ft_putendl_fd("invalid pid", STDERR_FILENO);
		return (1);
	}
	signal(SIGUSR1, handle_ack);
	send_message(server_pid, argv[2]);
	return (0);
}
