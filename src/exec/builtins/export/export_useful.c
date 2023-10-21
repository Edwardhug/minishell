/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_useful.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:42:38 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 05:02:29 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

size_t	size_without_quotes(char *arg)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
			nb--;
		nb++;
		i++;
	}
	return (nb);
}

char	*fill_cmd_without_quotes(t_exec *exec, char **cmd,
	char **clean_cmd, size_t i)
{
	size_t	j;
	size_t	k;

	clean_cmd[i] = malloc(sizeof(char) * (size_without_quotes(cmd[i]) + 1));
	if (!clean_cmd[i])
	{
		while (--i >= 0)
			free(clean_cmd[i]);
		free(clean_cmd);
		free_tab(cmd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	j = 0;
	k = 0;
	while (cmd[i][k])
	{
		if (cmd[i][k] != '\"' && cmd[i][k] != '\'')
		{
			clean_cmd[i][j] = cmd[i][k];
			j++;
		}
		k++;
	}
	clean_cmd[i][j] = '\0';
	return (clean_cmd[i]);
}

char	**delete_quotation_mark(char **cmd, t_exec *exec, int nb_args)
{
	char	**clean_cmd;
	size_t	i;

	i = 0;
	clean_cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!clean_cmd)
	{
		free_tab(cmd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	while (cmd[i])
	{
		clean_cmd[i] = fill_cmd_without_quotes(exec, cmd, clean_cmd, i);
		i++;
	}
	clean_cmd[i] = NULL;
	return (clean_cmd);
}

int	is_valid_name(char *cmd_name, t_env *args_tmp)
{
	int		i;
	t_env	*tmp;

	tmp = args_tmp;
	while (tmp)
	{
		if (tmp->name[0] >= '0' && tmp->name[0] <= '9')
		{
			ft_error_message_arg(cmd_name, tmp->name,
				": not a valid identifier\n");
			return (1);
		}
		i = 0;
		while (tmp->name[i])
		{
			if (check_char_name(tmp->name, i, cmd_name) == 1)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
