/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:05 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/20 13:46:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	usizecalc(unsigned int n)
{
	int				size;

	if (n == 0)
		return (1);
	size = 0;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

int	printunsigned(unsigned int n)
{
	int				size;
	int				i;
	int				count;
	unsigned int	num;

	size = usizecalc(n);
	if (n == 0)
	{
		write(1, "0", 1);
		return (size);
	}
	count = 0;
	while (size--)
	{
		num = n;
		i = size;
		while (i--)
			num = num / 10;
		num = num % 10 + '0';
		write(1, &num, 1);
		count++;
	}
	return (count);
}
