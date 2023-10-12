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
		return (perror("malloc lst into double char 1"), NULL);
	while (tmp)
	{
		size_node = ft_strlen(tmp->name) + ft_strlen(env->value) + 2;
		char_env[i] = malloc(sizeof(char *) * (size_node + 1));
		if (!char_env[i])
			return (perror("malloc lst into double char 2"), free_tab(char_env), NULL);
		tmp2 = ft_strjoin(tmp->name, "=");
		char_env[i] = ft_strjoin(tmp2, tmp->value);
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

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc lstnew_env 1"), NULL);
	new->name = malloc(sizeof(char) * (nb + 1));
	if (!new->name)
		return (perror("malloc lstnew_env 2"), free(new), NULL);
	if (str[0] == '=')
	{
		while (str[i] == '=')
		{
			new->name[i] = '=';
			i++;
		}
		new->name[i] = '\0';
	}
	else
	{
		ft_strncpy(new->name, str, nb);
		new->name[nb] = '\0';
	}
	new->value = malloc(sizeof(char) * (ft_strlen(str) - nb));
	if (!new->value)
		return (perror("malloc lstnew_env 3"), free(new), free(new->name), NULL);
	ft_strcpy(new->value, &str[nb + 1]);
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
			return (perror("env_double_char_int_lst malloc error"), lst_env);
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
