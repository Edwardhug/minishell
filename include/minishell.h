/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:27:24 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/14 18:50:23 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/all_libft.h"
# include <fcntl.h>

typedef struct s_struct
{
	int				stdin;
	int 			stdout;
	char 			*cmd;
	char 			**flags;
	char			*target;
	struct s_struct	*next;
}			t_struct;

char	**get_path(char **env);
void	parsing_minishell(char **path, char *line, char **env);
void	free_tab(char **tab);

#endif
