/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_useful.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:42:38 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 16:45:06 by jrenault         ###   ########lyon.fr   */
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
		if (arg[i] == '\"')
			nb--;
		nb++;
		i++;
	}
	return (nb);
}

char	**delete_quotation_mark(char **cmd, t_exec *exec, int nb_args)
{
	char	**clean_cmd;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	clean_cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!clean_cmd)
	{
		free_tab(cmd);
		free_exec_struct(exec);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (cmd[i])
	{
		clean_cmd[i] = malloc(sizeof(char) * (size_without_quotes(cmd[i]) + 1));
		if (!clean_cmd[i])
		{
			perror("malloc");
			while (--i >= 0)
				free(clean_cmd[i]);
			free(clean_cmd);
			free_tab(cmd);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
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