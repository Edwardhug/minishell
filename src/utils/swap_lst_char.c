#include "../../include/minishell.h"

char	**env_lst_into_double_char(t_env *env, t_exec *exec)
{
	int		i;
	char	**char_env;
	char	*tmp2;
	t_env	*tmp;

	i = 0;
	tmp = env;
	char_env = malloc(sizeof(char **) * (t_env_strlen(tmp) + 1));
	if (!char_env)
	{
		free_exec_struct(exec);
		perror("malloc lst into double char 1");
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		tmp2 = ft_strjoin(tmp->name, "=");
		if (!tmp2)
		{
			while (i >= 0)
			{
				free(char_env[i]);
				i--;
			}
			free(char_env);
			free_exec_struct(exec);
			perror("malloc error\n");
			exit(EXIT_FAILURE);
		}
		char_env[i] = ft_strjoin(tmp2, tmp->value);
		if (!char_env[i])
		{
			free_tab(char_env);
			free_exec_struct(exec);
			perror("malloc error\n");
			exit(EXIT_FAILURE);
		}
		free(tmp2);
		tmp = tmp->next;
		i++;
	}
	char_env[i] = NULL;
	return (char_env);
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
