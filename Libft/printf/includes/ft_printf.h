/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:34:23 by lgabet            #+#    #+#             */
/*   Updated: 2023/01/31 15:56:02 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printchar(int c);
int		ft_printf(const char *str, ...);
int		ft_printstr(char *str);
int		ft_printaddress(unsigned long long address);
int		ft_printnbr(int nbr);
int		ft_print_unsigned(unsigned int nbr);
int		ft_print_hexa(unsigned int nbr, char c);
void	ft_putchar(int n);
int		ft_putstr(char *str);
int		ft_lenght_size(int nbr);
char	*ft_itoa(int n);
char	*ft_itoa_u(unsigned int n);
char	*ft_itoa_x(unsigned int n, char x);
int		ft_lenght_size_u(unsigned int nbr);

#endif
