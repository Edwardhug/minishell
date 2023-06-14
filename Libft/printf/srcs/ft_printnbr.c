/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:53:58 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 14:11:06 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar(int n)
{
	write(1, &n, 1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_lenght_size(int nbr)
{
	int	lenght;

	lenght = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		lenght += 1;
	}
	if (nbr == -2147483648)
		return (11);
	while (nbr >= 10)
	{
		nbr /= 10;
		lenght++;
	}
	return (lenght);
}

int	ft_printnbr(int nbr)
{
	int		lenght;
	char	*str;

	str = ft_itoa(nbr);
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	lenght = ft_lenght_size(nbr);
	free(str);
	return (lenght);
}
