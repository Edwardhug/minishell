/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:01:40 by lezard            #+#    #+#             */
/*   Updated: 2023/09/21 11:28:58 by lgabet           ###   ########.fr       */
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
	return (nb + 1);
}