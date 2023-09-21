/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_enum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:15:26 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 16:07:50 by lezard           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_redirection(char *str)
{
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

int	is_a_pipe(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

t_enum	find_type_enum(t_struct *tmp, char *word)
{
	t_enum	type;

	type = ENUM_NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (is_a_pipe(word))
		type = PIPE;
	else if (is_a_redirection(word))
		type = REDIRECTION;
	else if (tmp->type == ENUM_NULL || tmp->type == FILES || tmp->type == PIPE)
		type = CMD;
	else if ((tmp->type == CMD || tmp->type == OPT) && word[0] == '-')
		type = OPT;
	else if (((tmp->type == CMD || tmp->type == OPT) && word[0] != '-') || tmp->type == ARG)
		type = ARG;
	else if (tmp->type == REDIRECTION)
		type = FILES;
	return (type);
}
