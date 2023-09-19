/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:27:24 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 14:22:27 by lezard           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_enum
{
	ENUM_NULL,
	CMD,
	OPT,
	ARG,
	PIPE,
	REDIRECTION,
	FILES,
}			t_enum;

typedef struct s_struct
{
	char				*str;
	t_enum				type;
	struct s_struct		*next;
}			t_struct;

typedef struct s_exec
{
	int		nb_cmds;
	int		nb_pipes;
	int		**pipes;
	int		fd_in;
	int		fd_out;
	char	**path;
	char	**env;
	char	*true_path;
	char	**cmd;
	pid_t	*pids;
}				t_exec;

char		**get_path(char **env);
//void		free_tab(char **tab);
void		parsing_minishell(char **path, char *line, char **env);
t_struct	*new_node(char *content, t_enum type);
t_struct	*get_last_node(t_struct *lst);
void		add_node_back(t_struct **list, t_struct *new_node);
t_enum		find_type_enum(t_struct *tmp, char *word);
char		*remove_quotes(char *str);
void		delete_node(t_struct **lst);
void		free_list(t_struct **lst);

void		print_list(t_struct *list);

//exec

void		exec_start(char **path, char **env, t_struct *list_word);
char		**get_cmd(t_exec *exec, t_struct *temp_word);

//builtins

int			ft_cd(t_exec *exec, t_struct *temp_word);

// utils

size_t		t_struct_strlen(t_struct *list_word);

#endif
