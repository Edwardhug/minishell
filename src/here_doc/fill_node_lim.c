/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_lim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:47:03 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 08:15:22 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_loop_here_doc(int fd, char *to_ret, char **tmp, char *lim)
{
	ft_putstr_fd(to_ret, fd);
	free((*tmp));
	free(to_ret);
	// free(lim);
	(void)lim;
	close(fd);
}

char	*find_lim(char *line, int *i, t_exec *exec)
{
	int		j;
	int		k;
	char	*ret;

	j = 0;
	k = 0;
	while (line[j + (*i)] && line[j + (*i)] != ' ')
		j++;
	ret = ft_calloc(j + 1, sizeof(char));
	if (!ret)
		return (free_stuff_error(exec, NULL, "Malloc error\n", -1), NULL);
	while (k != j)
	{
		ret[k] = line[(*i) + k];
		k++;
	}
	(*i) = (*i) + k;
	return (ret);
}

int	get_s_expand(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->name))
			return (ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

char	*fill_expand(char *str, int i, t_env *env)
{
	char	*to_ret;
	int		j;
	int		k;

	j = 0;
	k = 0;
	to_ret = ft_calloc(get_s_expand(str + i, env) + ft_strlen(str) + 1,
			sizeof(char));
	if (!to_ret)
		return (NULL);
	while (str[j] != '$')
	{
		to_ret[j] = str[j];
		j++;
	}
	while (env && ft_strcmp((str + j + 1), env->name))
		env = env->next;
	if (!env)
		return (to_ret);
	while (env->value[k])
	{
		to_ret[j + k] = env->value[k];
		k++;
	}
	return (to_ret);
}

char	*expand_heredoc(char *str, t_env *env)
{
	char	*to_ret;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\n')
		{
			to_ret = fill_expand(str, i, env);
			if (!to_ret)
				return (str);
			free(str);
			return (to_ret);
		}
		i++;
	}
	return (str);
}
