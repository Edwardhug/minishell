/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:56:45 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 13:14:40 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_here_doc(t_struct *temp_list, int *fd)
{
	char	*tmp;

	close(fd[0]);
	temp_list = temp_list->next;
	while (1)
	{
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, temp_list->str, ft_strlen(temp_list->str)) == 0)		//probleme si jamais le limiter est plus long comnme dans pipex
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
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
	return (1);
}
// heredoc branch