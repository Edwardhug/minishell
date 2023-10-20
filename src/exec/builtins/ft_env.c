/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:04:48 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 13:04:52 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_env(t_exec *exec)
{
	int		i;
	char	**char_env;

	char_env = env_lst_into_double_char(exec->env, exec);
	i = 0;
	while (char_env[i])
	{
		ft_printf("%s\n", char_env[i]);
		i++;
	}
	free_tab(char_env);
	free_exec_fork(exec);
	exit(0);
	return (0);
}
