#include "../../../include/minishell.h"

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

static void	show_export(t_exec *exec)
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
			if (tmp->value[0] == '\"' && tmp->value[ft_strlen(tmp->value) - 1] == '\"')
				ft_printf("%s", tmp->value);
			else
				ft_printf("\"%s\"", tmp->value);
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void	export_existing_value(t_env *args_tmp, t_exec *exec)
{
	t_env	*tmp_exp;
	t_env	*tmp_env;

	tmp_exp = exec->export;
	tmp_env = exec->env;
	while (tmp_exp)
	{
		if (ft_strcmp(args_tmp->name, tmp_exp->name) == 0)
		{
			free(tmp_exp->value);
			tmp_exp->value = ft_strdup(args_tmp->value);
			if (!tmp_exp->value)
			{
				perror("tmp_exp->value dup error\n");
				free_env(args_tmp);
				free_exec_struct(exec);
				exit(EXIT_FAILURE);
			}
		}
		tmp_exp = tmp_exp->next;
	}
	while (tmp_env)
	{
		if (ft_strcmp(args_tmp->name, tmp_env->name) == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(args_tmp->value);
			if (!tmp_env->value)
			{
				free_env(args_tmp);
				free_exec_struct(exec);
				exit(EXIT_FAILURE);
			}
		}
		tmp_env = tmp_env->next;
	}
}

static t_env	*ft_lstnew_export(t_env *args_tmp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_env(args_tmp);
		exit(EXIT_FAILURE);
	}
	new->name = malloc(sizeof(char *) * (ft_strlen(args_tmp->name) + 1));
	if (!new->name)
	{
		free_env(args_tmp);
		exit(EXIT_FAILURE);
	}
	new->name = ft_strdup(args_tmp->name);
	if (!new->name)
	{
		free_env(args_tmp);
		exit(EXIT_FAILURE);
	}
	if (args_tmp->value == NULL || args_tmp->value[0] == '\0')
	{
		new->value = malloc(sizeof(char *) * 1);
		if (!new->value)
		{
			free_env(args_tmp);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new->value = malloc(sizeof(char *) * (ft_strlen(args_tmp->value) + 1));
		if (!new->value)
		{
			free_env(args_tmp);
			exit(EXIT_FAILURE);
		}
	}
	if (args_tmp->value)
	{
		new->value = ft_strdup(args_tmp->value);
		if (!new->value)
		{
			free_env(args_tmp);
			exit(EXIT_FAILURE);
		}
	}
	else
		new->value[0] = '\0';
	new->next = NULL;
	return (new);
}

static void	create_var(t_env *args_tmp, t_exec *exec)
{
	t_env	*new_exp;
	t_env	*new_env;

	if (args_tmp->value == NULL || args_tmp->value[0] == '\0') //pas de valeur donnée donc on met juste dans export
	{
		new_exp = ft_lstnew_export(args_tmp);
		new_exp->next = exec->export;
		exec->export = new_exp;
	}
	else //a une valeur donc on met dans export et env
	{
		new_exp = ft_lstnew_export(args_tmp);
		new_exp->next = exec->export;
		exec->export = new_exp;
		new_env = ft_lstnew_export(args_tmp);
		new_env->next = exec->env;
		exec->env = new_env;
	}
}

//on a le droit qu'à alphanumérique et underscore. Ne peut pas commencer par un chiffre.
static	int	is_valid_name(char *cmd_name, t_env *args_tmp)
{
	int		i;
	t_env	*tmp;

	tmp = args_tmp;
	while (tmp)
	{
		i = 0;
		if (tmp->name[i] >= '0' && tmp->name[i] <= '9')
		{
			ft_error_message_arg(cmd_name, tmp->name, ": not a valid identifier\n");
			return (1);
		}
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

	lst_args = env_double_char_into_lst(cmd + 1);	//on met les args dans une liste pour comparer plus facilement.
	if (is_valid_name(cmd[0], lst_args))
	{
		g_error_value = -1;
		return (1);
	}
//	free_tab(cmd);
	while (lst_args)
	{
		tmp = exec->export;
		args_tmp = lst_args;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, args_tmp->name) == 0)
			{
				if (args_tmp->value == NULL || args_tmp->value[0] == '\0') //variable trouvée mais pas de valeur = on fait rien
					break ;
				else	//variable trouvée et nouvelle valeur à mettre
					export_existing_value(args_tmp, exec);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
		{
			create_var(args_tmp, exec); //la variable n'a pas été trouvée donc on la crée
		}
		lst_args = lst_args->next;
	}
	free_env(lst_args);
	return (0);
}

static int	quote_here(char *arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			nb++;
		i++;
	}
	return (nb);
}

static char	**quotation_check(char **cmd, t_exec *exec, int nb_args)
{
	char	**clean_cmd;
	int		i;
	int		j;
	int		k;

	clean_cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!clean_cmd)
	{
		free_tab(cmd);
		free_exec_struct(exec);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (cmd[i])
	{
		j = 0;
		k = 0;
		if (quote_here(cmd[i]))
			clean_cmd[i] = malloc(sizeof(char) * ft_strlen(cmd[i]) - 1);
		else
			clean_cmd[i] = malloc(sizeof(char) * ft_strlen(cmd[i]) + 1);
		if (!clean_cmd[i])
		{
			free_tab(cmd);
			free_exec_struct(exec);
			while (clean_cmd[--i])
				free(clean_cmd[i]);
			free(clean_cmd);
			exit(EXIT_FAILURE);
		}
		while (clean_cmd[i][j] && cmd[i][k])
		{

			if (cmd[i][k] != '\"')
			{
				clean_cmd[i][j] = cmd[i][k];
				j++;
				k++;
			}
			else
				k++;
		}
		i++;
	}
	clean_cmd[i] = NULL;
	return (clean_cmd);
}

int	ft_export(char **cmd, t_exec *exec)
{
	int		nb_args;
	char	**clean_cmd;

	nb_args = 0;
	while (cmd[nb_args])
		nb_args++;
	if (nb_args == 1) //export seul = on affiche la liste export
		show_export(exec);
	else
	{
		clean_cmd = quotation_check(cmd, exec, nb_args);
//		for (int i = 0; clean_cmd[i]; i++)
//			ft_printf("clean_cmd: %s\n", clean_cmd[i]);
		what_to_do(clean_cmd, exec);
		free_tab(clean_cmd);
	}
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
