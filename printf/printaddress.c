/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printaddress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:35 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/21 15:56:23 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ulsizecalc(unsigned long n)
{
	int	size;

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

static int	writeaddress(int count, char *arr, void *ptr)
{
	int	i;

	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	i = count;
	write(1, "0x", 2);
	while (i > 0)
		write(1, &arr[i--], 1);
	return (0);
}

int	printaddress(void *ptr)
{
	unsigned long	num;
	int				count;
	char			*arr;

	if (ptr == 0)
		return (writeaddress(0, 0, 0));
	num = (unsigned long)ptr;
	arr = malloc(ulsizecalc(num) + 1);
	if (arr == 0)
		return (0);
	arr[0] = '\0';
	count = 1;
	while (num != 0)
	{
		if (num % 16 <= 9)
			arr[count++] = num % 16 + '0';
		else
			arr[count++] = 'a' + (num % 16 - 10);
		num = num / 16;
	}
	count--;
	writeaddress(count, arr, ptr);
	free(arr);
	return (count + 2);
}
