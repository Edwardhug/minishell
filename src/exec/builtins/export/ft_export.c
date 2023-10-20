/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:40:58 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 13:41:06 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static void	ft_swap(t_env *node1, t_env *node2)
{
	char	*tmp_name;
	char	*tmp_value;

	if (node1 == NULL || node1->next == NULL)
		return ;
	if (node2 == NULL || node2->next == NULL)
		return ;
	tmp_name = node1->name;
    tmp_value = node1->value;
    node1->name = node2->name;
    node1->value = node2->value;
    node2->name = tmp_name;
    node2->value = tmp_value;
}

static void	sort_list(t_exec *exec)
{
	int		swapped;
	t_env	*head;
	t_env	*last_ptr;

	last_ptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		head = exec->export;
		while (head && head->next && head->next != last_ptr)
		{
			if (ft_strcmp(head->name, head->next->name) > 0)
			{
				ft_swap(head, head->next);
				swapped = 1;
			}
			head = head->next;
		}
		last_ptr = head;
	}
}

void	show_export(t_exec *exec)
{
	t_env	*tmp;

	sort_list(exec);
	tmp = exec->export;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s", tmp->name);
		if (tmp->value != NULL)
		{
			ft_printf("=");
			ft_printf("\"%s\"", tmp->value);
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}

static t_env	*ft_lstnew_export(t_env *args_tmp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc lstnew_export1"), NULL);
	new->name = ft_strdup(args_tmp->name);
	if (!new->name)
		return(perror("lstnew_export dup 1"), NULL);
	if (args_tmp->value == NULL || args_tmp->value[0] == '\0')
	{
		new->value = malloc(sizeof(char *) * 1);
		new->value[0] = '\0';
	}
	else
	{
		new->value = ft_strdup(args_tmp->value);
		if (!new->value)
			return (perror("lstnew_export dup 2"), NULL);
	}
	new->next = NULL;
	return (new);
}

void	export_existing_value(t_env *args_tmp, t_exec *exec, t_env *head)
{
	t_env	*tmp_exp;
	t_env	*tmp_env;
	int		not_in_env;

	tmp_exp = exec->export;
	tmp_env = exec->env;
	not_in_env = 0;
	while (tmp_exp)
	{
		if (ft_strcmp(args_tmp->name, tmp_exp->name) == 0)
		{
			while (tmp_env)
			{
				if (ft_strcmp(args_tmp->name, tmp_env->name) == 0)
				{
					if (tmp_env->value) //à virer je pense lors du normage 
						free(tmp_env->value);
					tmp_env->value = ft_strdup(args_tmp->value);
					if (!tmp_env->value)
					{
						perror("tmp_env->value malloc\n");
						free_exec_struct(exec);
						if (head)
							free_env(head);
						exit(EXIT_FAILURE);
					}
					not_in_env = 1;
				}
				tmp_env = tmp_env->next;
			}
			if (tmp_exp->value)
				free(tmp_exp->value);
			tmp_exp->value = ft_strdup(args_tmp->value);
			if (!tmp_exp->value)
			{
				perror("tmp_exp->value dup error\n");
				free_exec_struct(exec);
				if (head)
					free_env(head);
				exit(EXIT_FAILURE);
			}
		}
		tmp_exp = tmp_exp->next;
	}
	if (not_in_env == 0)
	{
		tmp_env = ft_lstnew_export(args_tmp);
		if (!tmp_env)
		{
			if (head)
				free_env(head);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		tmp_env->next = exec->env;
		exec->env = tmp_env;
	}
}


static void	create_var(t_env *args_tmp, t_exec *exec, t_env *head)
{
	t_env	*new_exp;
	t_env	*new_env;

	if (args_tmp->value == NULL || args_tmp->value[0] == '\0')
	{
		new_exp = ft_lstnew_export(args_tmp);
		if (!new_exp)
		{
			free_env(head);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		if (new_exp->value)
			free(new_exp->value);
		new_exp->value = NULL;
		new_exp->next = exec->export;
		exec->export = new_exp;
	}
	else
	{
		new_exp = ft_lstnew_export(args_tmp);
		if (!new_exp)
		{
			free_env(head);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		new_exp->next = exec->export;
		exec->export = new_exp;
		new_env = ft_lstnew_export(args_tmp);
		if (!new_env)
		{
			free_env(head);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		new_env->next = exec->env;
		exec->env = new_env;
	}
}

static	int	is_valid_name(char *cmd_name, t_env *args_tmp)
{
	int		i;
	t_env	*tmp;

	tmp = args_tmp;
	while (tmp)
	{
		if (tmp->name[0] >= '0' && tmp->name[0] <= '9')
		{
			ft_error_message_arg(cmd_name, tmp->name, ": not a valid identifier\n");
			return (1);
		}
		i = 0;
		while (tmp->name[i])
		{
			if (!(tmp->name[i] >= 'a' && tmp->name[i] <= 'z')
					&& !(tmp->name[i] >= 'A' && tmp->name[i] <= 'Z')
					&& !(tmp->name[i] >= '0' && tmp->name[i] <= '9')
					&& (tmp->name[i] != '_'))
			{
				ft_error_message_arg(cmd_name, tmp->name, ": not a valid identifier\n");
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	what_to_do(char **cmd, t_exec *exec)
{
	t_env	*tmp;
	t_env	*lst_args;
	t_env	*args_tmp;
	t_env	*head;

	lst_args = env_double_char_into_lst(cmd + 1, exec);
	head = lst_args;
	if (is_valid_name(cmd[0], lst_args))
	{
		g_error_value = -1;
		return (1);
	}
	while (lst_args)
	{
		tmp = exec->export;
		args_tmp = lst_args;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, args_tmp->name) == 0)
			{
				if (args_tmp->value == NULL || args_tmp->value[0] == '\0')
				{
					break ;
				}
				else
				{
					export_existing_value(args_tmp, exec, head);
				}
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
		{
			create_var(args_tmp, exec, head);
		}
		lst_args = lst_args->next;
	}
	free_env(head);
	return (0);
}

static size_t	size_without_quotes(char *arg)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while(arg[i])
	{
		if (arg[i] == '\"')
			nb--;
		nb++;
		i++;
	}
	return (nb);
}

static char	**delete_quotation_mark(char **cmd, t_exec *exec, int nb_args)
{
	char	**clean_cmd;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	clean_cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!clean_cmd)
	{
		free_tab(cmd);
		free_exec_struct(exec);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (cmd[i])
	{
		clean_cmd[i] = malloc(sizeof(char) * (size_without_quotes(cmd[i]) + 1));
		if (!clean_cmd[i])
		{
			perror("malloc");
			while (--i >= 0)
				free(clean_cmd[i]);
			free(clean_cmd);
			free_tab(cmd);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		j = 0;
		k = 0;
		while (cmd[i][k])
		{
			if (cmd[i][k] != '\"' && cmd[i][k] != '\'')
			{
				clean_cmd[i][j] = cmd[i][k];
				j++;
			}
			k++;
		}
		clean_cmd[i][j] = '\0';
		i++;
	}
	clean_cmd[i] = NULL;
	return (clean_cmd);
}

int	ft_export(char **cmd, t_exec *exec)
{
	int	nb_args;
	char	**clean_cmd;

	nb_args = 0;
	while (cmd[nb_args])
		nb_args++;
	clean_cmd = delete_quotation_mark(cmd, exec, nb_args);
	if (nb_args == 1)
		show_export(exec);
	else
		what_to_do(clean_cmd, exec);
	free_tab(clean_cmd);
	if (exec->nb_cmds > 1)
	{
		free_exec_fork(exec);
		exit(0);
	}
	return (0);
}
