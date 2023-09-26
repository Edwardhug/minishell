/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:56:45 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/26 22:59:22 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_here_doc(t_struct *temp_list, int *fd)
{
	char	*tmp;

	close(fd[0]);
	temp_list = temp_list->next;
	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			close(fd[1]);
			exit(3);
		}
		if ((ft_strncmp(tmp, temp_list->str, ft_strlen(temp_list->str)) == 0)
			&& (ft_strlen(temp_list->str) == ft_strlen(tmp)))
		{
			free(tmp);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
}

int	here_doc(t_struct *temp_list)
{
	int	fd[2];
	int	pid;
	int	status;

	if (!temp_list->next)						// verifie qu'il n'y a pas juste marque ( << )
		return (ft_printf("syntax error near unexpected token `newline'\n", NULL));
	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		ft_child_here_doc(temp_list, fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(&status);
		signals();
		temp_list = temp_list->next;
		if (temp_list->next && status == EXIT_SUCCESS)
			return(1);
		else if (status == 768)
		{
			dup2(0, STDIN_FILENO);
			return(1);
		}
		else
			return(0);
	}
	return (1);
}
