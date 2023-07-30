#include "ft_stdio.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

#define CHAR_BIT_LEN 8

volatile sig_atomic_t	received_ack = 0;

void	handle_ack(int signum)
{
	(void)signum;
	received_ack = 1;
}

void	send_character(pid_t pid, char c)
{
	unsigned int	bit;

	bit = CHAR_BIT_LEN;
	while (bit--)
	{
		ft_printf("send!\n");
		if (c & (1 << bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		if (!received_ack)
			pause();
		received_ack = 0;
	}
}

void	send_message(pid_t pid, const char *message)
{
	while (*message)
		send_character(pid, *message++);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	pid_t				server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = (pid_t)atoi(argv[1]);
	act.sa_handler = handle_ack;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	send_message(server_pid, argv[2]);
	return (0);
}
