/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/utils/exit_fonctions.c
/*   Created: 2023/09/19 17:13:13 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 17:16:22 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_and_write_it(char **path)
{
	ft_printf("exit\n");
	rl_clear_history();
	free_tab(path);
	exit(EXIT_SUCCESS);				// verifier si c'est bien exit success
}
=======
/*   Created: 2022/11/07 16:20:24 by jrenault          #+#    #+#             */
/*   Updated: 2022/11/12 11:47:11 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *memo, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)memo)[i] = '\0';
		i++;
	}
	return (memo);
}
>>>>>>> origin/exec:libft/ft_bzero.c
