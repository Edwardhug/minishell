#include "minishell.h"

char	**env_lst_into_double_char(t_env *env)
{
	int		i;
	char	**char_env;
	t_env	*tmp;
	int		size_node;

	i = 0;
	tmp = env;
	size_node = ft_strlen(env->name) + ft_strlen(env->value) + 1;
	char_env = malloc(sizeof(char **) * (t_env_strlen(tmp) + 1));
	if (!char_env)
		return (perror("malloc"), NULL);
	while (tmp)
	{
		char_env[i] = malloc(sizeof(char *) * (size_node + 1));
		if (!char_env[i])
			return (perror("malloc"), free_tab(char_env), NULL);
		char_env[i] = ft_strjoin(tmp->name, "=");
		char_env[i] = ft_strjoin(char_env[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	char_env[i] = NULL;
	return (char_env);
}

static t_env	*ft_lstnew_env(char *str, int nb)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc"), NULL);
	new->name = malloc(sizeof(char *) * (nb + 1));
	if (!new->name)
		return (perror("malloc"), free(new), NULL);
	new->name = ft_strncpy(new->name, str, nb);
	new->value = malloc(sizeof(char *) * (ft_strlen(str) - nb + 1));
	if (!new->value)
		return (perror("malloc"), free(new), free(new->name), NULL);
	new->value = ft_strcpy(new->value, &str[nb + 1]);
	new->next = NULL;
	return (new);
}

static int	search_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
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
			return (perror("lst env error I think..."), lst_env);
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
