#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"

volatile bool received_confirmation = false;

void	handle_ack(int signum)
{
	(void)signum;
	received_confirmation = true;
}

void	send_character(pid_t pid, char c)
{
	for (int bit = sizeof(char) * 8 - 1; bit >= 0; --bit)
	{
		kill(pid, (c & (1 << bit)) ? SIGUSR2 : SIGUSR1);
		if (!received_confirmation)
			pause();
		received_confirmation = false;
	}
}

void	send_message(pid_t pid, const char *message)
{
	for (const char *ch = message; *ch != '\0'; ++ch)
		send_character(pid, *ch);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	pid_t 				server_pid;

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
