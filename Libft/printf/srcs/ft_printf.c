/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:26:52 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 12:25:21 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_choose(char c, va_list argument)
{
	int	lenght;

	if (c == 'c')
		lenght = ft_printchar(va_arg(argument, int));
	if (c == 's')
		lenght = ft_printstr(va_arg(argument, char *));
	if (c == 'p')
		lenght = ft_printaddress(va_arg(argument, unsigned long long));
	if (c == 'd' || c == 'i')
		lenght = ft_printnbr(va_arg(argument, int));
	if (c == 'u')
		lenght = ft_print_unsigned(va_arg(argument, unsigned int));
	if (c == 'x' || c == 'X')
		lenght = ft_print_hexa(va_arg(argument, unsigned int), c);
	if (c == '%')
		lenght = write(1, "%", 1);
	return (lenght);
}

int	ft_read(const char *str, va_list argument, int i)
{
	int	length_printf;
	int	tamp;

	length_printf = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			tamp = ft_choose(str[i + 1], argument);
			if (tamp == -1)
				return (tamp);
			length_printf += tamp;
			i++;
		}
		else
		{
			tamp = ft_printchar(str[i]);
			if (tamp == -1)
				return (tamp);
			length_printf += tamp;
		}
		i++;
	}
	return (length_printf);
}

int	ft_printf(const char *str, ...)
{
	va_list	argument;
	int		length_printf;
	int		i;

	i = 0;
	va_start(argument, str);
	length_printf = ft_read(str, argument, i);
	va_end(argument);
	return (length_printf);
}
