/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:51 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/16 17:04:20 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_here_doc(char *limiter, int *fd)
{
	char	*tmp;

	close(fd[0]);
	while (1)
	{
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) == 0)
		{
			free(tmp);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
}

void	ft_here_doc(char *limiter)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_child_here_doc(limiter, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}