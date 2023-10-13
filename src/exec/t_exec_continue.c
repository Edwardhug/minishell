/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:55:30 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/13 19:22:49 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	t_open_fd_out(t_struct *temp_list)
{
	int	fd_out;

	while (temp_list && temp_list->next && temp_list->next->type != PIPE)
	{
		if (!ft_strcmp(temp_list->str, ">>"))
		{
			temp_list = temp_list->next;
			fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strcmp(temp_list->str, ">"))
		{
			temp_list = temp_list->next;
			fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (fd_out < 0)
			perror(temp_list->str);
		// ft_printf("temp_list->str = %s\ntemp_list->next = %s\n\n", temp_list->next->type, temp_list->next);
			// ft_printf("%d\n", fd_out);
		if (!temp_list->next || temp_list->next->type == PIPE)
		{
			// ft_putstr_fd("pass\n", 2);
			dup2(fd_out, STDOUT_FILENO);
			close (fd_out);
			return (fd_out);
		}
		else
		{
			// ft_putstr_fd("pass\n", 2);
			close (fd_out);
			temp_list = temp_list->next;
		}
	}
	return (0);
}

// void	t_open_fd_out(t_struct *temp_list)
// {
// 	int	fd_out;

// 	if (!ft_strcmp(temp_list->str, ">>"))
// 	{
// 		temp_list = temp_list->next;
// 		fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// 	else
// 	{
// 		temp_list = temp_list->next;
// 		fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	}
// 	if (fd_out < 0)
// 	{
// 		perror(temp_list->str);
// 		exit(1);
// 	}
// 	dup2(fd_out, STDOUT_FILENO);
// 	close (fd_out);
	
// }

int	t_change_stdout(t_struct *temp_list, int fd)
{
	if (temp_list->type == REDIRECTION) // on avance dans la liste chainee en cas de redirection 2 fois pour passer la redirection et le fichier
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
		return (t_open_fd_out(temp_list));		//peut etre que des fd resterons open a cause de ca
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
	// print_list(cmd);
	return (cmd);
}

int	t_exec_cmd(t_struct *temp_list, t_exec *exec, t_fd tfd)
{
	int		fd[2];
	int		pid;

	if (exec->nb_cmds == 1 && is_builtin_alone(t_get_clean_cmd(temp_list), exec) == 1)
		return (0);
	else
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			// if (tfd.fd_in == -1)
			// 	exit(1);
			// tfd.fd_out = t_change_stdout(temp_list, fd[1]);
			change_std(&tfd, temp_list, fd[1]);
			close(fd[1]);
			is_builtin_fork(t_get_clean_cmd(to_cmd(temp_list)), exec); 	//garder ca
			// ft_putstr_fd("yooo\n", 2);
			// ft_printf("%s\n", to_cmd(temp_list)->str);
			t_apply_exec(to_cmd(temp_list), exec, tfd);			// garder ca 
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			return (pid);
		}
	}
}
