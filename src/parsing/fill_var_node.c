/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:52:42 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/20 22:20:06 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isequal(int n)
{
	if (n == '=')
		return (1);
	return (0);
}

void	fill_var_node(t_struct **list_word, char *word, t_exec *exec)
{
	t_struct	*tmp;
	t_enum		type;
	char		*str;
	int			i;

	if (!word)
		return ;
	i = 0;
	while (word[i])
	{
		str = get_node(word, &i);
		if (!str)
		{
			free_list(list_word);
			free(word);
			free_stuff_error(exec, NULL, "malloc error\n", -1);
		}
		tmp = *list_word;
		type = find_type_enum(tmp, str);
		add_node_back(list_word, new_node(str, type));
	}
	free(word);
}

int	get_len_var(char *line, int *i, t_struct **list_word, t_exec *exec)
{
	int	j;
	int	quotes;
	int	equal;
	int	copy;

	j = 0;
	quotes = 0;
	equal = 0;
	copy = (*i);
	while (line[copy] && (quotes + equal) < 3)
	{
		if (line[copy] == '=')
			equal++;
		else if (line[copy] == '\"')
			quotes++;
		else if (line[copy] == ' ' && quotes < 1)
			return (j);
		j++;
		copy++;
	}
	if ((quotes + equal) < 3)
		return (fill_node(list_word, find_end_of_the_word(line, i), exec), 0);
	return (j);
}

char	*find_end_var(char *line, int *i, t_struct **list_word, t_exec *exec)
{
	int		len;
	char	*word;
	int		j;

	len = get_len_var(line, i, list_word, exec);
	if (len == 0)
		return (NULL);
	word = ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j;
	return (word);
}
