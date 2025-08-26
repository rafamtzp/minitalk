/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:08:28 by ramarti2          #+#    #+#             */
/*   Updated: 2025/08/26 15:08:36 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	power(int num, int exp)
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

void	chartobin(unsigned char c, int server_pid)
{
	int	num;
	int	i;

	num = (int)c;
	i = 7;
	while (i >= 0)
	{
		if (num >= power(2, i))
		{
			num = num - power(2, i);
			kill(server_pid, SIGUSR1);
		}
		else
			kill(server_pid, SIGUSR2);
		i--;
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	if (argc != 3)
		return (-1);
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 && errno == ESRCH)
		return (-1);
	if (argv[2][0] == '\0')
		return (-1);
	i = 0;
	while (argv[2][i])
	{
		chartobin(argv[2][i], server_pid);
		i++;
	}
	return (0);
}
