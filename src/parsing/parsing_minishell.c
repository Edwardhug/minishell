/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:50:18 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/19 13:50:29 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// int	change_stdin(char **splited_line, t_struct *to_send, int i)
// {
// 	if (splited_line[i][0] == '<' && ft_strlen(splited_line[i]) == 1)
// 	{
// 		i++;
// 		to_send->stdin = open(splited_line[1], O_RDONLY);
// 	}
// 	else if (splited_line[i][0] == '<' && splited_line[i][1] == '<'
// 		&& ft_strlen(splited_line[i]) == 2)
// 	{
// 		ft_here_doc(splited_line[i + 1]);
// 		i++;
// 	}
// 	return (i);
// }

// int	fill_node(char **splited_line, t_struct *node, int i)
// {
// 	int	j;

// 	j = 0;
// 	node->cmd = splited_line[i];
// 	i++;
// 	while (splited_line[i])
// 	{
// 		if (access(splited_line[i], F_OK) != -1)
// 		{
// 			node->flags[j] = NULL;
// 			node->target = splited_line[i];
// 			return (++i);
// 		}
// 		node->flags[j] = splited_line[i];
// 		i++;
// 		j++;
// 	}
// 	return (i);
// }

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

	j = 0;
	(*i)++;
	while (line[(*i) + j] && line[(*i) + j] != '"')
		j++;
	if (!line[j + (*i)])
		return (NULL);
	word = calloc((j + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (line[(*i) + j] != '"')
	{
		word[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j + 1;
	return (word);
}

void	parsing_minishell(char **path, char *line, char **env)
{
	// t_struct	to_send;
	char		*word;
	int			i;

	word = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			word = find_second_quote(line, &i);
		else
			word = find_end_of_the_word(line, &i);
		if (line[i] == ' ')
			i++;
		ft_printf("%s\n", word);
		free(word);
	}
	(void)path;
	(void)env;
}