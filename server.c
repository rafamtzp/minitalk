/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:08:21 by ramarti2          #+#    #+#             */
/*   Updated: 2025/08/26 15:08:23 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int		lastsignal;

void	sighandler(int signum)
{
	lastsignal = signum;
}

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

int	main(void)
{
	int		pid;
	char	c;
	int		i;

	pid = getpid();
	ft_printf("%i\n", pid);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	while (1)
	{
		i = 0;
		c = 0;
		while (i < 8)
		{
			pause();
			if (lastsignal == SIGUSR1)
				c += power(2, 7 - i);
			i++;
		}
		if (c != 0)
			write(1, &c, 1);
	}
}
