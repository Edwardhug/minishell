/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:06:34 by lgabet            #+#    #+#             */
/*   Updated: 2022/12/14 14:53:57 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_size(int n)
{
	int	i;

	if (n != 0)
		i = 1;
	else
		i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	ft_fill(char *str, int n)
{
	int	i;
	int	a;
	int	m;

	m = n;
	a = 1;
	if (n < 0)
	{
		a = -1;
		n = n * -1;
	}
	i = 0;
	while (ft_size(m) - i != 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	if (a == -1)
	{
		str[i - 1] = '-';
		str[i] = '\0';
	}
	else
		str[i] = '\0';
}

void	ft_return(char *str, int n)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = ft_size(n) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

void	ft_exception(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
}

char	*ft_itoa(int n)
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
	if (n == -2147483648)
	{
		str = malloc(sizeof(char) * 12);
		if (!str)
			return (NULL);
		ft_exception(str);
		return (str);
	}
	str = malloc(sizeof(char) * ft_size(n) + 1);
	if (!str)
		return (NULL);
	ft_fill(str, n);
	ft_return(str, n);
	return (str);
}
