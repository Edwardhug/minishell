#include "../../include/minishell.h"

char	**env_lst_into_double_char(t_env *env, t_exec *exec)
{
	t_env_lst	str;

	str.i = 0;
	str.tmp = env;
	str.char_env = malloc(sizeof(char **) * (t_env_strlen(str.tmp) + 1));
	if (!str.char_env)
	{
		free_exec_struct(exec);
		perror("malloc lst into double char 1");
		exit(EXIT_FAILURE);
	}
	while (str.tmp)
	{
		str.tmp2 = ft_strjoin(str.tmp->name, "=");
		if (!str.tmp2)
		{
			while (str.i >= 0)
			{
				free(str.char_env[str.i]);
				str.i--;
			}
			free(str.char_env);
			free_exec_struct(exec);
			perror("malloc error\n");
			exit(EXIT_FAILURE);
		}
		str.char_env[str.i] = ft_strjoin(str.tmp2, str.tmp->value);
		if (!str.char_env[str.i])
		{
			free_tab(str.char_env);
			free_exec_struct(exec);
			perror("malloc error\n");
			exit(EXIT_FAILURE);
		}
		free(str.tmp2);
		str.tmp = str.tmp->next;
		str.i++;
	}
	str.char_env[str.i] = NULL;
	return (str.char_env);
}

t_env	*ft_lstnew_env(char *str, int nb)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc lstnew_env 1"), NULL);
	new->name = malloc(sizeof(char) * (nb + 1));
	if (!new->name)
		return (perror("malloc lstnew_env 2"), free(new), NULL);
	change_name(&new, str, &i, nb);
	if (str[nb] != '\0')
	{
		new->value = malloc(sizeof(char) * (ft_strlen(str) - nb));
		if (!new->value)
			return (free(new), free(new->name), NULL);
		ft_strcpy(new->value, &str[nb + 1]);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

static int	search_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	change_tail(t_env **tail, t_env **new_env, t_env **lst_env)
{
	if (!(*lst_env))
	{
		(*lst_env) = (*new_env);
		(*tail) = (*lst_env);
	}
	else
	{
		(*tail)->next = (*new_env);
		(*tail) = (*new_env);
	}
}

t_env	*env_double_char_into_lst(char **c_env, t_exec *exec)
{
	int		i;
	t_env	*lst_env;
	t_env	*new_env;
	t_env	*tail;

	i = 0;
	lst_env = NULL;
	tail = NULL;
	while (c_env[i])
	{
		new_env = ft_lstnew_env(c_env[i], search_equal_sign(c_env[i]));
		if (!new_env)
		{
			perror("lst error");
			free_tab(c_env);
			free_exec_struct(exec);
			exit(EXIT_FAILURE);
		}
		change_tail(&tail, &new_env, &lst_env);
		i++;
	}
	return (lst_env);
}
