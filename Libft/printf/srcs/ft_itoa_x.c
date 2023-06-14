/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:29:30 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/15 10:05:58 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_size_x(unsigned int n)
{
	int	i;

	if (n != 0)
		i = 1;
	else
		i = 0;
	while (n / 16 != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

void	ft_fill_x(char *str, unsigned int n, char x)
{
	int	i;
	int	m;

	m = n;
	i = 0;
	while (ft_size_x(m) > i)
	{
		if (n % 16 >= 10)
		{
			if (x == 'x')
				str[i] = (n % 16) + 'a' - 10;
			else
				str[i] = (n % 16) + 'A' - 10;
		}
		else
			str[i] = (n % 16) + '0';
		n = n / 16;
		i++;
	}
	str[i] = '\0';
}

void	ft_return_x(char *str, unsigned int n)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = ft_size_x(n) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa_x(unsigned int n, char x)
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
	str = malloc(sizeof(char) * ft_size_x(n) + 1);
	if (!str)
		return (NULL);
	ft_fill_x(str, n, x);
	ft_return_x(str, n);
	return (str);
}
