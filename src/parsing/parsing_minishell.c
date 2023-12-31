/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:50:18 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 08:50:11 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_node(t_struct **list_word, char *word, t_exec *exec)
{
	t_struct	*tmp;
	t_enum		type;
	char		*str;
	int			i;

	if (!word)
		return ;
	i = 0;
	word = remove_quotes(word, exec);
	while (word[i])
	{
		add_pipe(list_word);
		str = get_node(word, &i);
		if (!str)
		{
			free(word);
			free_list(list_word);
			free_stuff_error(exec, NULL, "malloc error\n", -1);
		}
		tmp = *list_word;
		type = find_type_enum(tmp, str);
		add_node_back(list_word, new_node(str, type));
	}
	free(word);
}

char	*find_end_of_the_word(char *line, int *i)
{
	int		j;
	char	*word;

	j = 0;
	if (check_quote_file(line, i, &word))
		return (word);
	while (line[(*i) + j] && line[(*i) + j] != ' ')
		j++;
	word = ft_calloc((j + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (line[(*i) + j] && line[(*i) + j] != ' ')
	{
		word[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j;
	return (word);
}

char	*find_second_quote(char *line, int *i, t_exec *exec)
{
	int		j;
	char	*word;

	j = 1;
	while (line[(*i) + j] && line[(*i) + j] != '"')
		j++;
	if (!line[j + (*i)])
		return ((*i)++, find_end_of_the_word(line, i));
	word = ft_calloc((j + 2), sizeof(char));
	if (!word)
	{
		free(line);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	j = 0;
	word[j] = line[(*i) + j];
	j++;
	while (line[(*i) + j] != '"')
	{
		word[j] = line[(*i) + j];
		j++;
	}
	word[j] = line[(*i) + j];
	(*i) = (*i) + j + 1;
	return (word);
}

void	parsing_minishell(char *line, t_exec *exec)
{
	t_struct	*list_word;

	if (line[0] == 0 || have_strange_cmd(line))
		return ;
	list_word = new_node(NULL, ENUM_NULL);
	loop_parsing(&list_word, line, exec);
	clean_redir_out(&list_word);
	if (!change_env_var(&list_word, exec))
	{
		free_list(&list_word);
		return ;
	}
	if (!delete_node(&list_word))
		return ;
	is_only_pipe(&list_word);
	transform_here_doc(&list_word, *exec);
	if (g_error_value != 130)
		begin_execution(exec, list_word, 0);
	else
		g_error_value = 130 * 256;
	free_list(&list_word);
}
