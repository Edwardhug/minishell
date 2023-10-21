/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:26:45 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 05:00:26 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	loop_here_doc(char **tmp, char *to_ret, char *lim, int fd)
{
	(*tmp) = readline("> ");
	if (g_error_value == 130)
	{
		free(to_ret);
		free(lim);
		close(fd);
		return (1);
	}
	if (!(*tmp) && g_error_value != 130)
	{
		ft_putstr_fd(to_ret, fd);
		free(to_ret);
		free(lim);
		close(fd);
		ft_printf("warning : wanted `%s'\n", lim);
		g_error_value = 130 * 256;
		return (1);
	}
	if (ft_strcmp((*tmp), lim) == 0)
	{
		ft_putstr_fd(to_ret, fd);
		free((*tmp));
		free(to_ret);
		free(lim);
		close(fd);
		return (1);
	}
	return (0);
}

void	here_doc(char *lim, char *lim_st, t_exec exec)
{
	int		fd;
	char	*tmp;
	char	*to_ret;
	char	*copy;
	char	*tamp;

	to_ret = ft_calloc(1, sizeof(char));
	if (!to_ret)
		return ;
	tmp = NULL;
	fd = open(HERE_DOC, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, sigint_handler_heredoc);
	while (g_error_value != -89)
	{
		if (loop_here_doc(&tmp, to_ret, lim, fd))
			return ;
		if (ft_strcmp(lim, lim_st) == 0)
			tmp = expand_heredoc(tmp, exec.env);
		copy = ft_strjoin(tmp, "\n");
		tamp = ft_strjoin(to_ret, copy);
		free(to_ret);
		to_ret = tamp;
		free(copy);
		free(tmp);
	}
}

char	*get_lim(char *str)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i++;
		ret[j] = str[i];
		j++;
		i++;
	}
	return (ret);
}


void	transform_here_doc(t_struct **list, t_exec exec)
{
	t_struct	*copy;
	t_struct	*start;

	copy = (*list);
	start = copy;
	while (copy)
	{
		if (ft_strcmp(copy->str, "<<") == 0)
		{
			here_doc(get_lim(copy->next->str), copy->next->str, exec);
			free(copy->str);
			copy->str = ft_strdup("<");
			copy->type = REDIRECTION;
			copy = copy->next;
			free(copy->str);
			copy->str = ft_strdup(HERE_DOC);
			copy->type = FILES;
		}
		copy = copy->next;
	}
	signals();
	(*list) = start;
}
