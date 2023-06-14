/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:12:11 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 14:49:28 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_lenght_size_x(unsigned int nbr)
{
	int	lenght;

	lenght = 1;
	while (nbr >= 16)
	{
		nbr /= 16;
		lenght++;
	}
	return (lenght);
}

int	ft_print_hexa(unsigned int nbr, char c)
{
	int		lenght;
	char	*str;

	str = ft_itoa_x(nbr, c);
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	lenght = ft_lenght_size_x(nbr);
	free(str);
	return (lenght);
}
