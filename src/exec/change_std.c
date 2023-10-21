/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_std.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:16:55 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 06:23:01 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_fd_in_(t_struct *lst, t_exec *exec, int fd)
{
	int	fd_in;

	fd_in = open(lst->str, O_RDONLY);
	if (fd_in < 0)
	{
		close(fd);
		free_stuff_error(exec, lst->str, ": No such file or directory\n", 1);
	}
	return (fd_in);
}

static int	open_fd_out(t_struct *lst)
{
	int	fd_out;

	fd_out = 1;
	if (!ft_strcmp(lst->str, ">>"))
	{
		lst = lst->next;
		fd_out = open(lst->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strcmp(lst->str, ">"))
	{
		lst = lst->next;
		fd_out = open(lst->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd_out < 0)
	{
		perror(lst->str);
		exit(1);
	}
	return (fd_out);
}

static void	dup_function(t_struct *lst, int fd, t_fd cfd)
{
	if (lst && lst->type == PIPE)
	{
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	if (cfd.fd_out != 1)
	{
		dup2(cfd.fd_out, STDOUT_FILENO);
		close (cfd.fd_out);
	}
	if (cfd.fd_in != 0)
	{
		dup2(cfd.fd_in, STDIN_FILENO);
		close (cfd.fd_in);
	}
}

void	change_std(t_struct *lst, int fd, t_exec *exec)
{
	t_fd	cfd;

	cfd.fd_in = 0;
	cfd.fd_out = 1;
	while (lst && lst->next && lst->type != PIPE)
	{
		if (lst->type == REDIRECTION
			&& ft_strncmp(lst->next->str, "$", 1) == 0)
		{
			close(fd);				
			free_stuff_error(exec, lst->next->str, ": ambiguous redirect\n", -1);
		}
		if (ft_strcmp(lst->str, "<") == 0)
		{
			cfd.fd_in = open_fd_in_(lst->next, exec, fd);
			lst = lst->next;
		}
		else if (ft_strcmp(lst->str, ">") == 0
			|| ft_strcmp(lst->str, ">>") == 0)
		{
			cfd.fd_out = open_fd_out(lst);
			lst = lst->next;
		}
		lst = lst->next;
	}
	dup_function(lst, fd, cfd);
}
