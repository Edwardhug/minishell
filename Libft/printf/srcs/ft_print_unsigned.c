/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:04:31 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 14:49:44 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_lenght_size_u(unsigned int nbr)
{
	int	lenght;

	lenght = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		lenght++;
	}
	return (lenght);
}

int	ft_print_unsigned(unsigned int nbr)
{
	int		lenght;
	char	*str;

	str = ft_itoa_u(nbr);
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	lenght = ft_lenght_size_u(nbr);
	free(str);
	return (lenght);
}
