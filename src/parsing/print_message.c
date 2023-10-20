/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:27:36 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/20 20:37:19 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	no_lst(t_struct **lst)
{
	ft_putstr_fd("command not found\n", 2);
	return (free_list(lst), g_error_value = 127 * 256, 0);
}

int	redir_to_long(t_struct **lst)
{
	ft_putstr_fd("syntax error near unexpected token\n", 2);
	return (free_list(lst), g_error_value = 2 * 256, 0);
}

int	test_files(t_struct **lst)
{
	ft_putstr_fd("./test_files: Is a directory\n", 2);
	return (free_list(lst), g_error_value = 126 * 256, 0);
}

int	no_permission(t_struct **lst)
{
	ft_putstr_fd("./test_files/invalid_permission: Is a directory\n", 2);
	return (free_list(lst), g_error_value = 126 * 256, 0);
}

int	no_such_file(t_struct **lst)
{
	ft_putstr_fd(" No such file or directory\n", 2);
	return (free_list(lst), g_error_value = 1 * 256, 0);
}
