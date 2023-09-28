#include "minishell.h"

int	t_size_cmd(t_struct *temp_list)			// compte la taille de ma commande complete
{
	int i;

	i = 0;
	while (temp_list && temp_list->type != REDIRECTION
		&& temp_list->type != PIPE)
	{
		i++;
		temp_list = temp_list->next;
	}
	return (i);
}

char	**t_get_clean_cmd(t_struct *temp_list)
{
	char	**str;
	int		i;

	i = 0;
	if (temp_list->type == REDIRECTION) // on avance dans la liste chainee en cas de redirection 2 fois pour passer la redirection et le fichier
	{
		temp_list = temp_list->next;
		temp_list = temp_list->next;
	}
	str = malloc(sizeof(char *) * (t_size_cmd(temp_list) + 1));
	if (!str)
		return (NULL);
	while (temp_list && temp_list->type != REDIRECTION	
		&& temp_list->type != PIPE)
	{
		str[i] = temp_list->str;				// remplit le tab** avec la commande et les argument
		i++;
		temp_list = temp_list->next;
	}
	str[i] = NULL;
	return (str);
}

char	*t_get_path_cmd(char **all_path, char **splited)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (splited[0][0] == '/')
	{
		path_cmd = ft_strdup(splited[0]);
		if (access(path_cmd, F_OK | X_OK) == -1)
			return (print_error(splited, all_path, 0), free(path_cmd), NULL);
		return (free_tab(all_path), path_cmd);
	}
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		path_cmd = ft_strjoin(tmp, splited[0]);
		if (access(path_cmd, F_OK | X_OK) != -1)
			return (free(tmp), path_cmd);
		free(path_cmd);
		free(tmp);
		i++;
	}
	print_error(splited, all_path, 1);
	return (NULL);
}

char	*t_get_cmd(char **env, char **splited_cmd)
{
	int		i;
	char	*path;
	char	**all_path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	if (!path)
		return (free_tab(splited_cmd), NULL);
	path = path + 5;
	if (ft_strncmp(splited_cmd[0], "./", 2) == 0)
		path = "";
	all_path = ft_split(path, ':');
	if (!all_path)
		return (NULL);
	return (t_get_path_cmd(all_path, splited_cmd));
}

void	t_apply_exec(t_struct *temp_list, t_exec *exec)
{
	char	*path_cmd;
	char	**splited_cmd;

	print_return_value(temp_list);
	splited_cmd = t_get_clean_cmd(temp_list);
	if (!splited_cmd)
		return ;
	path_cmd = t_get_cmd(exec->char_env, splited_cmd);
	if (!path_cmd)
		exit(EXIT_FAILURE);
	execve(path_cmd, splited_cmd, exec->char_env);
	ft_putstr_fd("permission denied: ", 2);
	ft_putstr_fd(path_cmd, 2);
	ft_putstr_fd("\n", 2);
	free_tab(splited_cmd);
	free(path_cmd);
	exit(EXIT_FAILURE);
}