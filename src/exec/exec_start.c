/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/09/20 14:27:32 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	access_cmd(t_exec *exec, int i)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strnstr(exec->cmd[0], "/", ft_strlen(exec->cmd[0])) != NULL)
	{
		exec->true_path = ft_strdup(exec->cmd[0]);
		if (!(exec->true_path))
			perror("strdup");
	}
	else
	{
		tmp = ft_strjoin(exec->path[i], "/");
		if (!tmp)
			perror("malloc");
		exec->true_path = ft_strjoin(tmp, exec->cmd[0]);
		if (!(exec->true_path))
			perror("malloc");
		free(tmp);
	}
	if (access(exec->true_path, R_OK) != -1)
		execute_command(exec);
	//free tout ça
}

void	find_correct_path(t_exec *exec)
{
	int	i;
	
	i = 0;
	if (!exec->path) //c'est si on supprime le path je crois je comprend plus mon code de pipex
	{
		access_cmd(exec, i);
	}
	while (exec->path[i]) //on cherche le bon path en les testant un à un
	{
		access_cmd(exec, i);
		i++;
	}
	//command_not_found
}

int	is_builtin(t_exec *exec, t_struct *temp_word)
{
	if (ft_strnstr(exec->cmd[0], "cd", 2) != NULL)
	{
		printf("on trouve cd dans les commandes\n");
		return (ft_cd(exec, temp_word), 1);
	}
	return (0);
}


int	exec_cmd(t_exec *exec, t_struct *list_word, t_struct *temp_list)
{
	(void)list_word;
	//pipe
	//fork
	exec->cmd = get_cmd(exec, temp_list);
	if (!exec->cmd)
		return (perror("malloc"), 1);
	if (is_builtin(exec, temp_list) == 1)
	{
		//builtin
		return(0);
	}
	else
	{
		//commande normale
		find_correct_path(exec);
	}
	return (0);
/*
	On fait un tableau de fork pour stocker les pids.
	Si on est dans le processus enfant, on regarde si builtins ou commande normale.
	Si builtins on redirige.
	Si commande normale on cherche le path puis access puis execve.

	mais pour moi il faut fork avant la boucle.
*/
}

int	open_fd_in(t_struct *temp_list)									// fonction qui change de stdin pour mettre fd_in a la place
{
	int	fd_in;

	temp_list = temp_list->next;
	fd_in = open(temp_list->str, O_RDONLY);
	if (fd_in < 0)
		perror(temp_list->str);
	else
		dup2(fd_in, STDIN_FILENO);
	if (fd_in != -1)
		close (fd_in);
	return (fd_in);
}

int	get_fd_in(t_struct *list_word, t_struct *temp_list) 			// fonction pour savoir auel sera le fdin de la commande qui arrive
{
	int fd_in;

	if (t_struct_strlen(list_word) == t_struct_strlen(temp_list))	// check si c'est la premiere commande
	{
		if (list_word->type == REDIRECTION)							// verifie si c'est une redirection
		{
			if (ft_strncmp(list_word->str, "<<", 2) == 0)
				fd_in = open_fd_in(temp_list);						// l'entree c'est le heredoc mais on verra ca plus tard, (lgabet a un heredoc)
			else
				fd_in = open_fd_in(temp_list->next);				// l'entree c'est le fichier qui suit le ( < )
		}
		else
			fd_in = dup(STDIN_FILENO);								// l'entree c'est le terminal
	}
	else
		fd_in = dup(STDIN_FILENO);									// l'infile est le stdout deja existant
	return (fd_in);
}

int	is_end(t_struct *temp_list)
{
	while (temp_list)
	{
		if (temp_list->type == PIPE)
			return (0);
		temp_list = temp_list->next;
	}
	return (1);
}

void exec_start(char **path, char **env, t_struct *list_word)
{
	t_struct	*temp_list;
	t_exec		exec;

	exec.env = env;
	exec.path = path;
	temp_list = list_word;
	while (temp_list)										// les forks à faire dans la boucle
	{
		exec.fd_in = get_fd_in(list_word, temp_list);
		if (is_end(temp_list))								// check si il y a d'autres cmd ou si c'est la derniere ( si il y a un pipe quoi)
		{
//			last_exec(&exec, list_word, temp_list);	
			exec_cmd(&exec, list_word, temp_list);		// si c'est la derniere commande on fait un dernier execv
			return ;
		}
		else
		{
			exec_cmd(&exec, list_word, temp_list);
		}
		while (temp_list->type != PIPE)
			temp_list = temp_list->next;
		temp_list = temp_list->next;
	}
}
