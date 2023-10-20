/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:50:27 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 20:22:50 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_splited_and_exit(char **splited, int error_value)
{
	free_tab(splited);
	exit(error_value);
}

void	get_right_return_value(char **splited, struct stat info, t_exec *exec)
{
	free_exec_struct(exec);
	if (exec->char_env)
		free_tab(exec->char_env);
	if (access(splited[0], F_OK) != -1)
	{
		if (splited[0][0] == '.' && splited[0][1] == '/')
			free_splited_and_exit(splited, 126);
		else
		{
			free_splited_and_exit(splited, 127);
		}
	}
	if (exec->i_stat == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			free_tab(splited);
			exit(128);
		}
	}
	free_tab(splited);
	exit(127);
}

void	print_return_value(void)
{
	ft_putnbr_fd(g_error_value / 256, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	print_clean_return_value(char *str)
{
	if ((ft_strncmp("$?", str, 2) == 0))
	{
		ft_putnbr_fd(g_error_value / 256, 1);
		return (1);
	}
	return (0);
}
