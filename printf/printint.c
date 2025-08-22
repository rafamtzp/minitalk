/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:27:40 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/20 14:14:38 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sizecalc(int n)
{
	int				size;
	unsigned int	temp_n;

	if (n < 0)
		temp_n = -n;
	else if (n > 0)
		temp_n = n;
	else
		return (1);
	size = 0;
	while (temp_n > 0)
	{
		temp_n = temp_n / 10;
		size++;
	}
	return (size);
}

static int	isnegative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	int				size;
	int				i;
	int				isneg;
	unsigned int	num;

	size = sizecalc(n);
	isneg = isnegative(n);
	if (isneg == 1)
		write(fd, "-", 1);
	while (size > 0)
	{
		if (isneg == 1)
			num = -n;
		else
			num = n;
		i = size - 1;
		while (i--)
			num = num / 10;
		num = num % 10 + '0';
		write(fd, &num, 1);
		size--;
	}
}

int	printint(int n)
{
	int				size;

	size = sizecalc(n);
	if (n < 0)
		size++;
	ft_putnbr_fd(n, 1);
	return (size);
}
