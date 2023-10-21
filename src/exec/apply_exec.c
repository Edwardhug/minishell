/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:12 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 03:53:23 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**t_get_clean_cmd(t_struct *temp_list, t_exec *exec, int i)
{
	char	**str;

	if (temp_list->type == REDIRECTION)
	{
		temp_list = temp_list->next;
		temp_list = temp_list->next;
	}
	i++;
	str = malloc(sizeof(char *) * (t_size_cmd(temp_list) + 1));
	if (!str)
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	while (temp_list && temp_list->type != REDIRECTION
		&& temp_list->type != PIPE)
	{
		str[i] = ft_strdup(temp_list->str);
		if (!str[i])
			free_dup_str(str, exec, i);
		i++;
		temp_list = temp_list->next;
	}
	str[i] = NULL;
	return (str);
}

static char	*cmd_slash(char *path_cmd, char **splited,
	char **all_path, t_exec *exec)
{
	path_cmd = ft_strdup(splited[0]);
	if (!path_cmd)
	{
		free_tab(all_path);
		free_tab(splited);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	if (access(path_cmd, F_OK | X_OK) == -1)
	{
		free_tab(all_path);
		free_tab(splited);
		free(path_cmd);
		free_stuff_error(exec,
			"access", ": no such file or directory\n", 127);
	}
	return (free_tab(all_path), path_cmd);
}

char	*t_get_path_cmd(char **all_path, char **splited,
	struct stat info, t_exec *exec)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (splited[0][0] == '/')
	{
		path_cmd = NULL;
		return (cmd_slash(path_cmd, splited, all_path, exec));
	}
	while (all_path[i])
	{
		tmp = join_tmp_and_secure(all_path, i, exec);
		path_cmd = ft_strjoin(tmp, splited[0]);
		if (!path_cmd)
			free_stuff_error(exec, NULL, "malloc error\n", -1);
		if (access(path_cmd, F_OK | X_OK) != -1)
			return (free(tmp), path_cmd);
		free(path_cmd);
		free(tmp);
		i++;
	}
	print_error(splited, all_path, 1);
	get_right_return_value(splited, info, exec);
	return (NULL);
}

char	*t_get_cmd(char **env, char **splited_cmd, t_exec *exec)
{
	int			i;
	char		*path;
	char		**all_path;
	struct stat	info;

	i = 0;
	path = NULL;
	if (ft_strncmp(splited_cmd[0], "./", 2) == 0
		|| ft_strncmp(splited_cmd[0], "/", 1) == 0)
		return (ft_strdup(splited_cmd[0]));
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	if (!path)
		return (free_tab(splited_cmd), free_tab(env), NULL);
	path = path + 5;
	all_path = ft_split(path, ':');
	if (!all_path)
		return (free_tab(splited_cmd), free_tab(env), NULL);
	exec->i_stat = stat(splited_cmd[0], &info);
	return (t_get_path_cmd(all_path, splited_cmd, info, exec));
}

void	t_apply_exec(t_struct *temp_list, t_exec *exec)
{
	char		*path_cmd;
	char		**splited_cmd;

	splited_cmd = t_get_clean_cmd(temp_list, exec, -1);
	if (!splited_cmd)
		return ;
	exec->char_env = env_lst_into_double_char(exec->env, exec);
	path_cmd = t_get_cmd(exec->char_env, splited_cmd, exec);
	if (!path_cmd)
		free_stuff_error(exec, temp_list->str, ": no path found\n", 127);
	if (ft_strcmp("./minishell", path_cmd) == 0)
		shlvl(exec, 0, 1);
	execute_execve(splited_cmd, exec, temp_list, path_cmd);
}
