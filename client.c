/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:08:28 by ramarti2          #+#    #+#             */
/*   Updated: 2025/09/02 15:43:12 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int			g_received;

static void	handler(int signum)
{
	if (signum == SIGUSR1)
		g_received = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf(">>> ✅ Message sent succesfully. ✅ <<<\n");
		exit(EXIT_SUCCESS);
	}
	return ;
}

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

static void	chartobin(unsigned char c, int server_pid)
{
	int	num;
	int	i;

	num = (int)c;
	i = 7;
	while (i >= 0)
	{
		g_received = 0;
		if (num >= power(2, i))
		{
			num = num - power(2, i);
			kill(server_pid, SIGUSR1);
		}
		else
			kill(server_pid, SIGUSR2);
		while (g_received == 0)
			usleep(1);
		i--;
	}
}

static int	handle_err(int err)
{
	if (err == 0)
		ft_printf("Error\nUsage: ./client [PID] \"[MESSAGE]\"\n");
	else if (err == 1)
		ft_printf("Error\nPID does not exist.\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	action;
	int					i;

	if (argc != 3)
		handle_err(0);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || (kill(server_pid, 0) == -1 && errno == ESRCH))
		handle_err(1);
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	i = 0;
	while (argv[2][i])
	{
		chartobin(argv[2][i], server_pid);
		i++;
	}
	chartobin('\0', server_pid);
}
