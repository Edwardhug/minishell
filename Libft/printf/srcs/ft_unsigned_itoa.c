/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:23:52 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 14:54:26 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_size_u(unsigned int n)
{
	int	i;

	if (n != 0)
		i = 1;
	else
		i = 0;
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	ft_fill_u(char *str, unsigned int n)
{
	int	i;
	int	m;

	m = n;
	i = 0;
	while (ft_size_u(m) - i != 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
}

void	ft_return_u(char *str, unsigned int n)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = ft_size_u(n) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa_u(unsigned int n)
{
	char	*str;

	if (n == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * ft_size_u(n) + 1);
	if (!str)
		return (NULL);
	ft_fill_u(str, n);
	ft_return_u(str, n);
	return (str);
}
