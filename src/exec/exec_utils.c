/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:59:53 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/26 05:46:54 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	duplicate_file_fd(t_exec *exec)
{
	if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
	{
		// perror("dup2");
		// wait_and_clean(exec, 0, 1);
		exit(EXIT_FAILURE);
	}
	if (exec->infile_fd != -1)
		close(exec->infile_fd);
	if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
	{
		// perror("dup2");
		// wait_and_clean(exec, 0, 1);
		exit(EXIT_FAILURE);
	}
	if (exec->outfile_fd != -1)
		close(exec->outfile_fd);
}

void	create_fork(t_exec *exec, t_struct *lst, int i)
{
	exec->pids[i] = fork();
	// if (exec->pids[i] == -1)
	// {
	// 	perror("fork");
	// 	wait_and_clean(exec, 0, 1);
	// 	exit(EXIT_FAILURE);
	// }
//	else if (exec->pids[i] == 0)
	if (exec->pids[i] == 0)
	{
		duplicate_file_fd(exec);
		if (i > 0)
			close(exec->pipes[i - 1][1]);
		if (i < exec->nb_cmds - 1)
			close(exec->pipes[i][0]);
		exec_simple(exec, lst);
	}
	else
	{
		close(exec->infile_fd);
		if (i != exec->nb_cmds - 1)
			close(exec->outfile_fd);
		if (i > 0)
			close(exec->pipes[i - 1][0]);
		if (i < exec->nb_cmds - 1)
			close(exec->pipes[i][1]);
	}
}

void	initialize_pipes(t_exec *exec)
{
	int	i;

	exec->pipes = malloc(sizeof(int *) * exec->nb_pipes);
	// if (!exec->pipes)
	// {
	// 	free_tab(exec->cmds);
	// 	perror("Malloc failed");
	// 	exit(EXIT_FAILURE);
	// }
	i = -1;
	while (++i < exec->nb_pipes)
	{
		exec->pipes[i] = malloc(sizeof(int) * 2);
		// if (!exec->pipes[i])
		// {
		// 	free_tab(exec->cmds);
		// 	while (i >= 0)
		// 	{
		// 		free(exec->pipes[i]);
		// 		i--;
		// 	}
		// 	free(exec->pipes);
		// 	perror("Malloc failed");
		// 	exit(EXIT_FAILURE);
		// }
		if (pipe(exec->pipes[i]) == -1)
		{
			// free_tab(exec->cmds);
			// while (i >= 0)
			// {
			// 	free(exec->pipes[i]);
			// 	i--;
			// }
			// free(exec->pipes);
	//		perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

int	count_args(t_struct *lst)
{
	int			i;
	t_struct	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && tmp->type != CMD)
		tmp = tmp->next;
	while (tmp && (tmp->type == CMD || tmp->type == OPT || tmp->type == ARG))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
		//si cmd
		//on prend dans args
		//on avance si option
		//on prend dans args
		//on avance si arguments
		//on prend dans args
		//on avance jusqu'à autre chose

char	**take_full_cmd(t_struct *lst)
{
	char		**args;
	int			i;
	int			nb_args;
	t_struct	*tmp;

	tmp = lst;
	i = 0;
	nb_args = count_args(lst);
	args = malloc(sizeof(char *) * (nb_args + 1));
	while (tmp && i < nb_args)
	{
			args[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
			i++;
	}
	return (args);
}

int	what_exec(t_struct *lst)
{
	t_struct	*tmp;
	int			nb;

	nb = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}
