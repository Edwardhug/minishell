/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:01:46 by lgabet            #+#    #+#             */
/*   Updated: 2022/11/10 17:18:27 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int		i;
	int		a;
	int		r;

	i = ft_whitespace((char *)s);
	a = 1;
	r = 0;
	if (s[i] == '-' || s[i] == '+')
	{	
		if (s[i] == '-')
			a = a * (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		r = (s[i] - '0') + r * 10;
		i++;
	}
	r = r * a;
	return (r);
}
