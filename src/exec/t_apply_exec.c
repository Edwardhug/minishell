#include "../../include/minishell.h"

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

char	*t_get_path_cmd(char **all_path, char **splited, struct stat info)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (splited[0][0] == '/')
	{
		path_cmd = ft_strdup(splited[0]);
		if (access(path_cmd, F_OK | X_OK) == -1)
			return (print_error(splited, all_path, 0), free(path_cmd),exit(127), NULL);
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
	get_right_return_value(splited, info);
	return (NULL);
}

char	*t_get_cmd(char **env, char **splited_cmd)
{
	int		i;
	char	*path;
	char	**all_path;
	struct stat info;		// pour savoir si on essaie d'applique a un directory ou pas

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
	// ft_printf("cmd 1 = %s\n", splited_cmd[0]);
	if (ft_strncmp(splited_cmd[0], "./", 2) == 0)
		return (ft_strdup(splited_cmd[0]));				// peut etre pas besoin du strdup mais je pense que si
	all_path = ft_split(path, ':');
	if (!all_path)
		return (NULL);
	stat(splited_cmd[0], &info);	// pour savoir si on essaie d'applique a un directory ou pas
	return (t_get_path_cmd(all_path, splited_cmd, info));
}

void	t_apply_exec(t_struct *temp_list, t_exec *exec)
{
	char		*path_cmd;
	char		**splited_cmd;

	splited_cmd = t_get_clean_cmd(temp_list);
	if (!splited_cmd)
		return ;
	path_cmd = t_get_cmd(env_lst_into_double_char(exec->env), splited_cmd);
	// ft_printf("pass = %s\n", path_cmd);
	if (!path_cmd)
		exit(127);
	execve(path_cmd, splited_cmd, env_lst_into_double_char(exec->env));
	perror("");
	free_tab(splited_cmd);
	free(path_cmd);
	// ft_printf("erno = %d\n", errno);
	if (errno == 13)
		exit (126);
	exit(127);
}
