/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:41:14 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 11:16:21 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char	*path;
	char	**splited_path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	if (!splited_path)
	{
		ft_printf("Malloc error while splitting path\n");
		exit(EXIT_FAILURE);
	}
	return (splited_path);
}
