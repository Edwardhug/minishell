/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:28:19 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 03:16:23 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	malloc_oldpwd_var(t_exec *exec, char *actual_pwd)
{
	exec->arg = ft_calloc(2, sizeof(char *));
	if (!exec->arg)
	{
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	exec->arg_pwd = ft_calloc(2, sizeof(char *));
	if (!exec->arg_pwd)
	{
		free(exec->arg);
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	exec->tmp = getcwd(NULL, 0);
	if (!exec->tmp)
	{
		free(exec->arg);
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
}

int	no_oldpwd(t_exec *exec, char *home)
{
	ft_putstr_fd("Can't go to this dir, moved to home\n", 2);
	if (home)
		chdir(home);
	else
		free_stuff_error(exec, NULL, "Couldn't find home\nexit\n", -1);
	change_pwd(exec);
	g_error_value = -1;
	return (0);
}

void	free_arg_oldpwd(char *arg, char *actual_pwd, t_exec *exec)
{
	free(arg);
	free(actual_pwd);
	free_stuff_error(exec, NULL, "malloc error\n", -1);
}
