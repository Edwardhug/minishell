/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:50:18 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/28 13:33:02 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_list(t_struct *list)
{
	int	i = 0;

	while (list)
	{
		ft_printf("node n%d\n	-str = %s\n	-type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
}

void fill_node(t_struct **list_word, char *word)
{
	t_struct	*tmp;
	t_enum		type;

	if (!word)
		return ;
	tmp = *list_word;
	type = find_type_enum(tmp, word);		//currently working on this
	word = remove_quotes(word);
	add_node_back(list_word, new_node(word, type));
}

char	*find_end_of_the_word(char *line, int *i)
{
	int		j;
	char	*word;

	j = 0;
	while (line[(*i) + j] && line[(*i) + j] != ' ')
		j++;
	word = calloc((j + 1), sizeof(char));
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

char	*find_second_quote(char *line, int *i)
{
	int		j;
	char	*word;

	j = 1;
	while (line[(*i) + j] && line[(*i) + j] != '"')
		j++;
	if (!line[j + (*i)])		// only one double quote
		return ((*i)++, find_end_of_the_word(line, i));
	word = calloc((j + 2), sizeof(char));
	if (!word)
		return (NULL);
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

void	parsing_minishell(char **path, char *line, char **env)
{
	int			i;
	t_struct	*list_word;

	if (line[0] == 0)
		return ;
	list_word = new_node(NULL, ENUM_NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			fill_node(&list_word, find_second_quote(line, &i));
		else
			fill_node(&list_word, find_end_of_the_word(line, &i));
		if (line[i] == ' ')
			i++;
	}
	delete_node(&list_word);
	// print_list(list_word);
	begin_execution(path, env, list_word);
	free_list(&list_word);
}
