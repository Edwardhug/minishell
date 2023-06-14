/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:29:33 by lgabet            #+#    #+#             */
/*   Updated: 2023/01/31 16:00:46 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printaddress_value(unsigned long long address)
{
	if (address >= 16)
	{
		ft_printaddress_value(address / 16);
		ft_printaddress_value(address % 16);
	}
	else
	{
		if (address <= 9)
			ft_printchar(address + '0');
		else
			ft_printchar(address - 10 + 'a');
	}
}

int	ft_countaddress_size(unsigned long long address)
{
	int	lenght;

	lenght = 1;
	while (address >= 16)
	{
		address /= 16;
		lenght ++;
	}
	return (lenght);
}

int	ft_printaddress(unsigned long long address)
{
	int	lenght;

	if (address == 0)
	{
		lenght = ft_printstr("(nil)");
		return (lenght);
	}
	lenght = 2;
	if (write(1, "0x", 2) == -1)
		return (-1);
	ft_printaddress_value(address);
	lenght += ft_countaddress_size(address);
	return (lenght);
}
