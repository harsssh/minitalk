/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:25:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 02:02:51 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define CHAR_BIT_LEN	8
#define ACK_WAIT 		10
#define ACK_TIMEOUT 	1000000
#define ERR_TIMEOUT 	"Error: timeout"
#define ERR_SEND 		"Error: failed to send signal"
#define ERR_PID 		"Error: invalid PID"
#define MSG_USAGE 		"Usage: client [server PID] [message]"

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
			ft_putendl_fd(ERR_TIMEOUT, STDERR_FILENO);
			exit(1);
		}
	}
	g_received_ack = 0;
}

void	send_message(pid_t pid, const char *message)
{
	unsigned int	bit;
	char			c;
	int				res;

	while (*message)
	{
		c = *message++;
		bit = CHAR_BIT_LEN;
		while (bit--)
		{
			if (c & (1 << bit))
				res = kill(pid, SIGUSR2);
			else
				res = kill(pid, SIGUSR1);
			if (res == -1)
			{
				ft_putendl_fd(ERR_SEND, STDERR_FILENO);
				exit(1);
			}
			wait_ack();
		}
	}
}

pid_t	parse_pid(const char *pid_str)
{
	pid_t	pid;

	if (*pid_str == '\0' || !ft_strall(pid_str, ft_isdigit))
		return (-1);
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
		ft_putendl_fd(MSG_USAGE, STDERR_FILENO);
		return (1);
	}
	server_pid = parse_pid(argv[1]);
	if (server_pid == -1)
	{
		ft_putendl_fd(ERR_PID, STDERR_FILENO);
		return (1);
	}
	signal(SIGUSR1, handle_ack);
	send_message(server_pid, argv[2]);
	return (0);
}
