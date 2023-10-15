/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:55:30 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/14 14:26:50 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	t_open_fd_out(t_struct *temp_list)
{
	int	fd_out;

	while (temp_list && temp_list->next && temp_list->next->type != PIPE)
	{
		change_outfile(&temp_list, &fd_out);
		if (fd_out < 0)
			perror(temp_list->str);
		if (!temp_list->next || temp_list->next->type == PIPE)
		{
			dup2(fd_out, STDOUT_FILENO);
			close (fd_out);
			return (fd_out);
		}
		else
		{
			close (fd_out);
			temp_list = temp_list->next;
		}
	}
	return (0);
}

int	t_change_stdout(t_struct *temp_list, int fd)
{
	if (temp_list->type == REDIRECTION)
	{
		temp_list = temp_list->next;
		temp_list = temp_list->next;
	}
	while (temp_list->next && temp_list->type != REDIRECTION
		&& temp_list->type != PIPE)
	{
		temp_list = temp_list->next;
	}
	if (temp_list->type == REDIRECTION)
		return (t_open_fd_out(temp_list));
	else if (temp_list->type == PIPE)
	{
		dup2(fd, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

t_struct	*to_cmd(t_struct *lst)
{
	t_struct	*cmd;

	while (lst && lst->type != CMD)
		lst = lst->next;
	cmd = lst;
	while (lst && lst->next && lst->next->type != PIPE)
	{
		if (lst->next->type == REDIRECTION)
			lst->next = lst->next->next->next;
		else
			lst = lst->next;
	}
	return (cmd);
}

int	t_exec_cmd(t_struct *temp_list, t_exec *exec, t_fd tfd)
{
	int		fd[2];
	int		pid;
	char	**clean_cmd;

	clean_cmd = t_get_clean_cmd(temp_list, exec);
	if (exec->nb_cmds == 1
		&& is_builtin_alone(clean_cmd, exec) == 1)
	{
		free_tab(clean_cmd);
		return (0);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			free_exec_struct(exec);
			free_tab(clean_cmd);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			change_std(&tfd, temp_list, fd[1]);
			close(fd[1]);
			free_tab(clean_cmd);
			clean_cmd = t_get_clean_cmd(to_cmd(temp_list), exec);
			is_builtin_fork(clean_cmd, exec);
			free_tab(clean_cmd);
			t_apply_exec(to_cmd(temp_list), exec, tfd);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			free_tab(clean_cmd);
			return (pid);
		}
	}
}
