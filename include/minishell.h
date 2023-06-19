/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:27:24 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/19 14:09:53 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum s_enum
{
	CMD,
	FLAG,
	ARG,
	PIPE,
	INFILE,
	OUTFILE,
	FILE,
}			t_enum;

typedef struct s_struct
{
	int				stdin;
	int				stdout;
	char			*cmd;
	char			**flags;
	char			*target;
	struct s_struct	*next;
}			t_struct;

typedef struct s_exec
{
	int		nb_cmds;
	int		**pipes;
	int		infile_fd;
	int		outfile_fd;
	char	*true_path;
	char	*tmp;
	char	**cmds;
	char	**env;
	char	**path;
}				t_exec;

char	**get_path(char **env);
void	free_tab(char **tab);
void	parsing_minishell(char **path, char *line, char **env);
// void	ft_here_doc(char *limiter);

#endif
