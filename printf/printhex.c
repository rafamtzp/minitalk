/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:30:09 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/20 18:23:23 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	writeentries(unsigned int num, char *arr, int count)
{
	if (num == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (count--)
		write(1, &arr[count], 1);
	return (0);
}

int	printhex(unsigned int num, char format)
{
	int		count;
	char	*arr;

	if (num == 0)
		return (writeentries(0, 0, 0));
	arr = malloc(13);
	if (arr == 0)
		return (0);
	arr[0] = '\0';
	count = 0;
	while (num != 0)
	{
		if (num % 16 <= 9)
			arr[count++] = num % 16 + '0';
		else if (format == 'X')
			arr[count++] = 'A' + (num % 16 - 10);
		else if (format == 'x')
			arr[count++] = 'a' + (num % 16 - 10);
		num = num / 16;
	}
	writeentries(1, arr, count);
	free(arr);
	return (count);
}
