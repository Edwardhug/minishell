/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:51:14 by jrenault          #+#    #+#             */
/*   Updated: 2023/09/18 14:07:54 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_command(t_exec *exec, char **args)
{
	execve(exec->true_path, args, exec->env);
	//
}

static int	do_builtin(t_struct *lst, char **path, char **env)
{
	(void)lst;
	(void)path;
	(void)env;
	return (0);
	if (ft_strcmp(lst->str, "cd") == 0)
		return (ft_cd(), 1);
	else if (ft_strcmp(lst->str, "echo") == 0)
		return (ft_echo(), 1);
	else if (ft_strcmp(lst->str, "exit") == 0)
		return (ft_exit(), 1);
	else if (ft_strcmp(lst->str, "env") == 0)
		return (ft_env(), 1);
	else if (ft_strcmp(lst->str, "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(lst->str, "unset") == 0)
		return (ft_unset(), 1);
	else if (ft_strcmp(lst->str, "export") == 0)
		return (ft_export(), 1);
	return (0);
}

static void	access_cmd(t_exec *exec, char **args, int i)
{
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) != NULL)
	{
		exec->true_path = ft_strdup(args[0]);
//		if (!exec->true_path)
//			exit_failure_access(exec, args, 1);
	}
	else
	{
		exec->tmp = ft_strjoin(exec->path[i], "/");
//		if (!exec->tmp)
//			exit_failure_access(exec, args, 0);
		exec->true_path = ft_strjoin(exec->tmp, args[0]);
//		if (!exec->true_path)
//			exit_failure_access(exec, args, 0);
		free(exec->tmp);
	}
	if (access(exec->true_path, R_OK) != -1)
		execute_command(exec, args);
	free(exec->true_path);
	exec->true_path = NULL;
	free_tab(args);
}

void	exec_simple(t_exec *exec, t_struct *lst)
{
	char	**args;
	int		i;

	if (!exec->path)
	{
		args = take_full_cmd(lst);
//		if (!args)
//			exit_failure_access(exec, args, 2);
		access_cmd(exec, args, -1);
	}
	i = -1;
	while (exec->path[++i])
	{
//on récupère la commande en entier en prenant cmd, opt, arg
		args = take_full_cmd(lst);
//		if (!args)
//			exit_failure_access(exec, args, 2);
		if (!args[0])
		{
			free_tab(args);
			break ;
		}
		access_cmd(exec, args, i);
	}
}

void	exec(char **path, char **env, t_struct *lst)
{
	t_exec	exec;

	exec.env = env;
	exec.path = path;
	exec.nb_cmds = what_exec(lst);
}
	//on compte les pipes dès le début sinon et si y'en a pas on s'en branle
	//si y'en a et que c'est juste des commandes on fait exec sans infiles outfile
	//si y'en a et qu'il y a infile outfile on fait exec normal
	// if (!exec.pids)
	// 	return ;
	// if (do_builtin(lst, path, env) == 0)
	// {
	// 	//
	// }
	// i = 1;
	// while (i < exec.nb_cmds)
	// {
	// 	exec.infile_fd = exec.pipes[i - 1][0];
	// 	exec.outfile_fd = exec.pipes[i][1];
	// 	run_command(lst, &exec, i);
	// 	i++;
	// }


	//normalement on est bon pour les cas normaux
//fonction qui parcourt la liste chaînée et compte le nombre de pipes, puis le met dans exec->nb_pipes
//si le noeud est une commande, on check si builtin sinon dans execve
//check si la suite est une option/argument pour le prendre avec
//on fout tout dans un char **
//on exec le bordel

/*

*/
