/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:08:21 by ramarti2          #+#    #+#             */
/*   Updated: 2026/04/01 17:11:30 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

static int	power(int num, int exp)
{
	int	factor;

	factor = 1;
	while (exp > 0)
	{
		factor = factor * num;
		exp--;
	}
	return (factor);
}

static void	confirm_eom(int *msg_printed, int *i, siginfo_t *info)
{
	*i = 0;
	*msg_printed = 0;
	write(1, "\n", 1);
	kill(info->si_pid, SIGUSR2);
}

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	static int				msg_printed = 0;

	(void)context;
	if (msg_printed == 0)
		ft_printf("Client: ");
	msg_printed = 1;
	if (i < 8)
	{
		if (signum == SIGUSR1)
			c += power(2, 7 - i);
		i++;
	}
	if (c != 0 && i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
	if (c == 0 && i == 8)
		confirm_eom(&msg_printed, &i, info);
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	action.sa_sigaction = sighandler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf("Server PID: %i\n", pid);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		sleep(1);
	}
}
