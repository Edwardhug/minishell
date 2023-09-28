/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:27:24 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/28 13:33:11 by lgabet           ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>

extern int	g_error_value;

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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_struct
{
	char				*str;
	t_enum				type;
	struct s_struct		*next;
}			t_struct;

typedef struct s_exec
{
	int		nb_cmds;
	char	**char_env;
	t_env	*lst_env;
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
void		signal_main_loop(void);
void		handle_sigint_main_loop(int signal);
void		exit_and_write_it(char **path, int fd_standart);

void		print_list(t_struct *list);

//exec

void		begin_execution(char **path, char **env, t_struct *list_word);
int			open_fd_in(t_struct *temp_list);
int			change_stdin(t_struct *list_word, t_struct *temp_list);
int			is_end(t_struct *temp_list);
void		find_correct_path(t_exec *exec);
void		access_cmd(t_exec *exec, int i);

void		t_open_fd_out(t_struct *temp_list);
void		t_change_stdout(t_struct *temp_list, int fd);
int			t_exec_cmd(t_struct *temp_list, t_exec *exec);
int			t_size_cmd(t_struct *temp_list);
char		**t_get_clean_cmd(t_struct *temp_list);
char		*t_get_path_cmd(char **all_path, char **splited);
char		*t_get_cmd(char **env, char **splited_cmd);
void		t_apply_exec(t_struct *temp_list, t_exec *exec);
void		print_error(char **splited_cmd, char **all_path, int i);
int			is_builtin(char	**cmd, t_exec *exec);

//builtins

int			ft_cd(char **cmd, t_exec *exec);
int			ft_pwd(t_exec *exec);
int			ft_echo(char **cmd, t_exec *exec);
int			ft_exit(char **cmd, t_exec *exec);
int			ft_unset(char **cmd, t_exec *exec);
int			ft_export(t_exec *exec);
int			ft_env(t_exec *exec);

// utils

size_t		t_struct_strlen(t_struct *list_word);
size_t		t_env_strlen(t_env *env);
char		**env_lst_into_double_char(t_env *env);
t_env		*env_double_char_into_lst(char **c_env);

//here doc

int			here_doc(t_struct *temp_list);

// signals


void	sigint_handler(int sig);
void	signals(void);
void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);
void 	sigint_handler_heredoc(int sig);
void	no_line_return(int sig);

// return value

void	print_return_value(t_struct *lst);
int	print_clean_return_value(char *str);
#endif
