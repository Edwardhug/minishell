/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:51:14 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/24 17:58:52 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	execute_command(t_struct *lst, t_exec *exec, char **args)
// {
// 	execve(exec->true_path, args, exec->env);
// 	//
// }

// void	access_path(t_struct *lst, t_exec *exec, char **args, int i)
// {
// 	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) != NULL)
// 	{
// 		exec->true_path = ft_strdup(args[0]);
// 		if (!exec->true_path)
// 		{
// 			//
// 		}
// 	}
// 	else
// 	{
// 		exec->tmp = ft_strjoin(exec->path[i], "/");
// 		if (!exec->tmp)
// 		{
// 			//
// 		}
// 		exec->true_path = ft_strjoin(exec->tmp, args[0]);
// 		if (!exec->true_path)
// 		{
// 			//
// 		}
// 		free(exec->tmp);
// 	}
// 	if (access(exec->true_path, R_OK) != -1)
// 		execute_command(lst, exec, args);
// 	free(exec->true_path);
// 	exec->true_path = NULL;
// 	free_tab(args);
// }

// void	path_and_access(t_struct *lst, t_exec *exec, pid_t *pids)
// {
// 	int		i;
// 	char	**args;

// 	if (!exec->path)
// 	{
// 		args = ft_split(lst->str, ' ');
// 		if (!args)
// 		{
// 			//secure
// 		}
// 		access_path(lst, exec, args, i);
// 	}
// 	i = -1;
// 	while (exec->path[++i])
// 	{
// 		args = ft_split(lst->str, ' ');
// 		if (!args)
// 		{
// 			//secure
// 		}
// 		if (!args[0])
// 		{
// 			free_tab(args);
// 			break ;
// 		}
// 		access_path(lst, exec, args, i);
// 	}
// 	command_not_found(lst, exec, pids);
// }

// void	run_command(t_struct *lst, t_exec *exec, int i)
// {
// 	exec->pids[i] = fork();
// 	if (exec->pids[i] == -1)
// 		return ;
// 	else if (exec->pids[i] == 0)
// 	{
// 		path_and_access(lst, exec, exec->pids);
// 	}
// }

// static int	do_builtin(t_struct *lst, char **path, char **env)
// {
// 	(void)lst;
// 	(void)path;
// 	(void)env;
// 	if (ft_strcmp(lst->str, "cd") == 0)
// 		return (ft_cd(), 1);
// 	else if (ft_strcmp(lst->str, "echo") == 0)
// 		return (ft_echo(), 1);
// 	else if (ft_strcmp(lst->str, "exit") == 0)
// 		return (ft_exit(), 1);
// 	else if (ft_strcmp(lst->str, "env") == 0)
// 		return (ft_env(), 1);
// 	else if (ft_strcmp(lst->str, "pwd") == 0)
// 		return (ft_pwd(), 1);
// 	else if (ft_strcmp(lst->str, "unset") == 0)
// 		return (ft_unset(), 1);
// 	else if (ft_strcmp(lst->str, "export") == 0)
// 		return (ft_export(), 1);
// 	return (0);
// }

static void	exec_simple(t_exec *exec, t_struct *lst)
{
	char	**args;

	if (!exec->path)
	{
		args = take_full_cmd(lst);
		if (!args)
			exit_failure_access(param, args, pids, 2);
		access_path(param, args, pids, i);
	}
	while (exec->path[++i])
	{
		args = ft_split(cmd, ' ');
		if (!args)
			exit_failure_access(param, args, pids, 2);
		if (!args[0])
		{
			free_tab(args);
			break ;
		}
		access_path(param, args, pids, i);
	}
	command_not_found(param, pids, cmd);
}

void	exec(char **path, char **env, t_struct *lst)
{
	t_exec	exec;

//	int		i;
//	exec.env = env;
//	exec.path = path;
	(void)path;
	(void)env;
	exec.nb_pipes = what_exec(lst);
	if (exec.nb_pipes == 0)
	{
		exec_simple(&exec, lst);
	}
	else
	{
		ft_printf("exec with pipes!\n");
	}
	//on compte les pipes dès le début sinon et si y'en a pas on s'en branle
	//si y'en a et que c'est juste des commandes on fait pipex sans infiles outfile
	//si y'en a et qu'il y a infile outfile on fait pipex normal
	// exec.pids = malloc(sizeof(pid_t) * exec.nb_cmds);
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
}

	//On crée un char ** args.
	//On compte le nbr de pipes
	//si 0 pipe on execve juste
	//si pipe on fork et tout le bordel.
	//et donc la séparation de la liste en args et compagnie on va le faire dans une boucle, et on va conserver où on est dans la liste
	//pour traiter la suite.
	//on fait ça pour chaque pipe du coup

	//normalement on est bon pour les cas normaux
//fonction qui parcourt la liste chaînée et compte le nombre de pipes, puis le met dans exec->nb_pipes
//si le noeud est une commande, on check si builtin sinon dans execve
//check si la suite est une option/argument pour le prendre avec
//on fout tout dans un char **
//on pipex le bordel