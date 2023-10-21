/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:04:59 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 08:56:31 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_not_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9') && (arg[i] != '+' && arg[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

static int	exit_not_number(char **cmd, t_exec *exec, int are_pipes)
{
	ft_error_message_arg(cmd[0], cmd[1],
		": numeric argument required\n");
	shlvl(exec, 0, 0);
	if (are_pipes)
		free_exec_fork(exec);
	else
		free_exec_struct(exec);
	free_tab(cmd);
	exit(2);
}

static int	if_one_command(char **cmd, t_exec *exec, int are_pipes)
{
	long long	status;

	status = 0;
	if (cmd[2])
	{
		ft_error_message(cmd[0], ": too many arguments\n");
		g_error_value = -1;
		return (1);
	}
	if (is_not_number(cmd[1]) == 1)
		exit_not_number(cmd, exec, are_pipes);
	status = ft_atoi(cmd[1]) % 256;
	if (are_pipes)
		free_exec_fork(exec);
	else
		free_exec_struct(exec);
	if (cmd)
		free_tab(cmd);
	exit(status);
	return (0);
}

int	ft_exit(char **cmd, t_exec *exec, int are_pipes)
{
	if (!are_pipes)
		ft_putstr_fd("exit\n", 1);
	if (cmd[1])
		if (if_one_command(cmd, exec, are_pipes) == 1)
			return (1);
	shlvl(exec, 0, 0);
	if (are_pipes)
		free_exec_fork(exec);
	else
		free_exec_struct(exec);
	free_tab(cmd);
	close(exec->fd_stand);
	exit(g_error_value / 256);
	return (0);
}
