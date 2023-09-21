/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:41:14 by lgabet            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/19 11:36:47 by lgabet           ###   ########.fr       */
=======
/*   Updated: 2023/09/18 16:02:58 by lezard           ###   ########lyon.fr   */
>>>>>>> origin/exec
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
