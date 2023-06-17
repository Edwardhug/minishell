/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:50:18 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/16 17:23:59 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_node(t_struct node)
{
	int	j = 0;
	ft_printf("stdin = %d\nstdout = %d\ncmd = %s\n", node.stdin, node.stdout, node.cmd);
	while (node.flags[j])
	{
		ft_printf("flags n°%d = %s\n", j, node.flags[j]);
		j++;
	}
	ft_printf("target = %s\n", node.target);
}

void	set_up_first_node(t_struct *node)
{
	node->stdin = 0;
	node->stdout = 1;
	node->target = NULL;
	node->cmd = NULL;
	node->flags = calloc(10000, sizeof(char *));
	node->next = NULL;
}

int	change_stdin(char **splited_line, t_struct *to_send, int i)
{
	if (splited_line[i][0] == '<' && ft_strlen(splited_line[i]) == 1)
	{
		i++;
		to_send->stdin = open(splited_line[1], O_RDONLY);
	}
	else if (splited_line[i][0] == '<' && splited_line[i][1] == '<'
		&& ft_strlen(splited_line[i]) == 2)
	{
		ft_here_doc(splited_line[i + 1]);
		i++;
	}
	return (i);
}

int	fill_node(char **splited_line, t_struct *node, int i)
{
	int	j;

	j = 0;
	node->cmd = splited_line[i];
	i++;
	while (splited_line[i])
	{
		if (access(splited_line[i], F_OK) != -1)
		{
			node->flags[j] = NULL;
			node->target = splited_line[i];
			return (++i);
		}
		node->flags[j] = splited_line[i];
		i++;
		j++;
	}
	return (i);
}

void	parsing_minishell(char **path, char *line, char **env)
{
	char		**splited_line;
	int 		i;
	t_struct	to_send;

	i = 0;
	if (line[0] == '\n')
		return ;
	set_up_first_node(&to_send);
	splited_line = ft_split(line, ' ');
	i = change_stdin(splited_line, &to_send, i);
	i = fill_node(splited_line, &to_send, i);
	// ft_putstr_fd("HEEEERE\n", 2);
	print_node(to_send);
	(void)path;
	(void)env;
}