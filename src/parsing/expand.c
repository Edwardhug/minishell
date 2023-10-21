/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 06:00:38 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 06:14:03 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_var(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, str) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void expand_pars(t_struct **list, t_env *env)
{
	t_struct	*copy;
	t_struct	*start;
	char		*var;

	copy = (*list);
	start = copy;
	while (copy)
	{
		if (copy->str[0] == '$')
		{
			var = find_var(copy->str + 1, env);
			if (var)
			{
				free(copy->str);
				copy->str = ft_strdup(var);	
			}
		}
		copy = copy->next;
	}
	(*list) = start;
}