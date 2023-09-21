/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_beging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:49:06 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/22 00:07:12 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	t_open_fd_out(t_struct *temp_list)
{
	int	fd_out;

	if (!ft_strncmp(temp_list->str, ">>", 2))
	{
		temp_list = temp_list->next;
		fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		temp_list = temp_list->next;
		fd_out = open(temp_list->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd_out < 0)
	{
		perror(temp_list->str);
	}
	dup2(fd_out, STDOUT_FILENO);
	// close (fd_out);
}

void	t_change_stdout(t_struct *temp_list, int fd)
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
		t_open_fd_out(temp_list);		//peut etre que des fd resterons open a cause de ca
	else if (temp_list->type == PIPE)
		dup2(fd, STDOUT_FILENO);
}

void	t_exec_cmd(t_struct *temp_list, char **env)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		t_change_stdout(temp_list, fd[1]);
		// dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		t_apply_exec(temp_list, env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(0, NULL, WUNTRACED);
	}
}
