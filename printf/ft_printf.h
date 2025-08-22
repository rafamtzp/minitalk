/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:49:43 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/21 15:00:27 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# define FT_PRINTF_H

int	printstr(char *s);
int	printint(int n);
int	printunsigned(unsigned int n);
int	printaddress(void *ptr);
int	printhex(unsigned int num, char format);
int	ft_printf(char const *str, ...);

#endif
