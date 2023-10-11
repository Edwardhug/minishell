#include "../../include/minishell.h"

char	**env_lst_into_double_char(t_env *env)
{
	int		i;
	char	**char_env;
	char	*tmp2;
	t_env	*tmp;
	int		size_node;

	i = 0;
	tmp = env;
	char_env = malloc(sizeof(char **) * (t_env_strlen(tmp) + 1));
	if (!char_env)
	{
		perror("malloc lst into double char 1");
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		size_node = ft_strlen(tmp->name) + ft_strlen(env->value) + 2;
		char_env[i] = malloc(sizeof(char *) * (size_node + 1));
		if (!char_env[i])
		{
			perror("malloc lst into double char 2");
			free_tab(char_env);
			free_env(env);
			exit(EXIT_FAILURE);

		}
		tmp2 = ft_strjoin(tmp->name, "=");
		if (!tmp2)
		{
			perror("malloc lst into double char 2");
			free_tab(char_env);
			free_env(env);
			exit(EXIT_FAILURE);
		}
		char_env[i] = ft_strjoin(tmp2, tmp->value);
		if (!char_env[i])
		{
			perror("malloc lst into double char 2");
			free(tmp2);
			free_tab(char_env);
			free_env(env);
			exit(EXIT_FAILURE);
		}
		free(tmp2);
		tmp = tmp->next;
		i++;
	}
	char_env[i] = NULL;
	return (char_env);
}

static t_env	*ft_lstnew_env(char *str, int nb)
{
	t_env	*new;
	int		i;
	int		only_equal;

	i = 0;
	only_equal = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc lstnew_env 1"), NULL);
	if (nb)
	{
		new->name = malloc(sizeof(char) * (nb + 1));
		if (!new->name)
			return (perror("malloc lstnew_env 2"), free(new), NULL);
	}
	else
	{
		while (str[i] == '=')
			i++;
		new->name = malloc(sizeof(char) * i + 1);
		if (!new->name)
		{
			free(str);
			free(new);
			return (perror("malloc name ="), NULL);
		}
		i = 0;
		while (str[i] == '=')
		{
			new->name[i] = '=';
			i++;
		}
		new->name[i] = '\0';
		new->value = malloc(sizeof (char) * 1);
		new->value[0] = '\0';
		only_equal = 1;
	}
	if (!only_equal)
	{
		ft_strncpy(new->name, str, nb);
		new->name[nb] = '\0';
		if (str[nb])
		{
			new->value = malloc(sizeof(char) * (ft_strlen(str) - nb));
			if (!new->value)
				return (perror("malloc lstnew_env 3"), free(new), free(new->name), NULL);
			ft_strcpy(new->value, &str[nb + 1]);
		}
		else
		{
			new->value = malloc(sizeof (char) * 1);
			new->value[0] = '\0';
		}
	}
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

t_env	*env_double_char_into_lst(char **c_env)
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
			free_tab(c_env);
			perror("env_double_char_int_lst lstnew_env failed");
			exit(EXIT_FAILURE);
		}
		if (!lst_env)
		{
			lst_env = new_env;
			tail = lst_env;
		}
		else
		{
			tail->next = new_env;
			tail = new_env;
		}
		i++;
	}
	return (lst_env);
}
