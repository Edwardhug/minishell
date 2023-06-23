/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:51:14 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/23 15:50:36 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_command(t_struct *lst, t_exec *exec, char **args)
{
	execve(exec->true_path, args, exec->env);
	//
}

void	access_path(t_struct *lst, t_exec *exec, char **args, int i)
{
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) != NULL)
	{
		exec->true_path = ft_strdup(args[0]);
		if (!exec->true_path)
		{
			//
		}
	}
	else
	{
		exec->tmp = ft_strjoin(exec->path[i], "/");
		if (!exec->tmp)
		{
			//
		}
		exec->true_path = ft_strjoin(exec->tmp, args[0]);
		if (!exec->true_path)
		{
			//
		}
		free(exec->tmp);
	}
	if (access(exec->true_path, R_OK) != -1)
		execute_command(lst, exec, args);
	free(exec->true_path);
	exec->true_path = NULL;
	free_tab(args);
}

void	path_and_access(t_struct *lst, t_exec *exec, pid_t *pids)
{
	int		i;
	char	**args;

	if (!exec->path)
	{
		args = ft_split(lst->str, ' ');
		if (!args)
		{
			//secure
		}
		access_path(lst, exec, args, i);
	}
	i = -1;
	while (exec->path[++i])
	{
		args = ft_split(lst->str, ' ');
		if (!args)
		{
			//secure
		}
		if (!args[0])
		{
			free_tab(args);
			break ;
		}
		access_path(lst, exec, args, i);
	}
	command_not_found(lst, exec, pids);
}

void	run_command(t_struct *lst, t_exec *exec, pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] == -1)
		return ;
	else if (pids[i] == 0)
	{
		path_and_access(lst, exec, pids);
	}
}

void	execute(t_struct *lst, t_exec *exec)
{
	pid_t	*pids;
	int		i;

	init_params();
	find_all_path();
	pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!pids)
		return ;
	i = 1;
	while (i < exec->nb_cmds)
	{
		exec->infile_fd = exec->pipes[i - 1][0];
		exec->outfile_fd = exec->pipes[i][1];
		run_command(lst, exec, pids, i);
		i++;
	}
}
static int	do_builtin(t_struct *lst)
{
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

void	exec(char **path, char **env, t_struct *lst)
{
	//On crée un char ** args.
	//On compte le nbr de pipes
	//si 0 pipe on execve juste
	//si pipe on fork et tout le bordel.
	//et donc la séparation de la liste en args et compagnie on va le faire dans une boucle, et on va conserver où on est dans la liste
	//pour traiter la suite.
	//on fait ça pour chaque pipe du coup

	//normalement on est bon pour les cas normaux
	t_exec	exec;

	if (do_builtin(lst) == 0)
		execute(lst, &exec);
}

//fonction qui parcourt la liste chaînée et compte le nombre de pipes, puis le met dans exec->nb_pipes
//si le noeud est une commande, on check si builtin sinon dans execve
//check si la suite est une option/argument pour le prendre avec
//on fout tout dans un char **
//on pipex le bordel