/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:51 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/21 16:02:10 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static int	printformat(va_list args, char const *str)
{
	int	bytecount;

	bytecount = 0;
	if (*(str + 1) == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (*(str + 1) == '%')
		ft_putchar_fd('%', 1);
	else if (*(str + 1) == 's')
		bytecount += printstr(va_arg(args, char *)) - 1;
	else if (*(str + 1) == 'p')
		bytecount += printaddress(va_arg(args, void *)) - 1;
	else if (*(str + 1) == 'i' || *(str + 1) == 'd')
		bytecount += printint(va_arg(args, int)) - 1;
	else if (*(str + 1) == 'u')
		bytecount += printunsigned(va_arg(args, unsigned int)) - 1;
	else if (*(str + 1) == 'x')
		bytecount += printhex(va_arg(args, unsigned int), 'x') - 1;
	else if (*(str + 1) == 'X')
		bytecount += printhex(va_arg(args, unsigned int), 'X') - 1;
	return (++bytecount);
}

int	ft_printf(char const *str, ...)
{
	int		bytecount;
	va_list	args;

	va_start(args, str);
	bytecount = 0;
	while (*str)
	{
		if (*str == '%')
		{
			bytecount += printformat(args, str);
			str++;
		}
		else
		{
			ft_putchar_fd(*str, 1);
			if (*str == '\b')
				bytecount--;
			else
				bytecount++;
		}
		str++;
	}
	va_end(args);
	return (bytecount);
}
/*
#include <stdio.h>

int	main(void)
{
	int count = 0;
	unsigned int n = -100;
	unsigned int *ptr = &n;
	count = ft_printf("hello, %p\n", ptr);
	printf("%i\n", count);
	count = printf("hello, %p\n", ptr);
	printf("%i\n", count);
}
*/
