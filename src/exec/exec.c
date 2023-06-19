/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:51:14 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/19 14:05:41 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_command(t_struct *lst, t_exec *exec, char **args)
{
	execve(exec->true_path, args, exec->env);
	//
}

void	access_path(t_struct *lst, t_exec *exec, char **args, int i)
{
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) != NULL)
	{
		exec->true_path = ft_strdup(args[0]);
		if (!exec->true_path)
		{
			//
		}
	}
	else
	{
		exec->tmp = ft_strjoin(exec->path[i], "/");
		if (!exec->tmp)
		{
			//
		}
		exec->true_path = ft_strjoin(exec->tmp, args[0]);
		if (!exec->true_path)
		{
			//
		}
		free(exec->tmp);
	}
	if (access(exec->true_path, R_OK) != -1)
		execute_command(lst, exec, args);
	free(exec->true_path);
	exec->true_path = NULL;
	free_tab(args);
}

void	path_and_access(t_struct *lst, t_exec *exec, pid_t *pids)
{
	int		i;
	char	**args;

	if (!exec->path)
	{
		args = ft_split(lst->cmd, ' ');
		if (!args)
		{
			//secure
		}
		access_path(lst, exec, args, i);
	}
	i = -1;
	while (exec->path[++i])
	{
		args = ft_split(lst->cmd, ' ');
		if (!args)
		{
			//secure
		}
		if (!args[0])
		{
			free_tab(args);
			break ;
		}
		access_path(lst, exec, args, i);
	}
	command_not_found(lst, exec, pids);
}

void	run_command(t_struct *lst, t_exec *exec, pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] == -1)
		return ;
	else if (pids[i] == 0)
	{
		path_and_access(lst, exec, pids);
	}
}

void	execute(t_struct *lst, t_exec *exec)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!pids)
		return ;
	i = 1;
	while (i < exec->nb_cmds)
	{
		exec->infile_fd = exec->pipes[i - 1][0];
		exec->outfile_fd = exec->pipes[i][1];
		run_command(lst, exec, pids, i);
	}
}

int	do_builtin(t_struct *lst)
{
	if (ft_strcmp(lst->cmd, "cd") == 0)
		return (ft_cd(), 1);
	else if (ft_strcmp(lst->cmd, "echo") == 0)
		return (ft_echo(), 1);
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (ft_exit(), 1);
	else if (ft_strcmp(lst->cmd, "env") == 0)
		return (ft_env(), 1);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		return (ft_unset(), 1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		return (ft_export(), 1);
	return (0);
}

void	exec(t_struct *lst, t_exec *exec)
{
	init_params();
	find_all_path();
	if (do_builtin(lst) == 0)
		execute(lst, exec);
}
