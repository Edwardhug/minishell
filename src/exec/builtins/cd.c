/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jrenault <jrenault@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/18 15:04:15 by jrenault		  #+#	#+#			 */
/*   Updated: 2023/09/18 14:33:33 by jrenault		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_get_cmd(char **env, char **splited_cmd)
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
		return (ft_free_tab(splited_cmd), NULL);
	path = path + 5;
	if (ft_strncmp(splited_cmd[0], "./", 2) == 0)
		path = "";
	all_path = ft_split(path, ':');
	if (!all_path)
		return (NULL);
	return (ft_get_path_cmd(all_path, splited_cmd));
}

char	*ft_get_path_cmd(char **all_path, char **splited)
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
		return (ft_free_tab(all_path), path_cmd);
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

int	ft_cd(t_exec *exec)
{
	if (chdir(exec->true_path) == -1)
		perror("chdir");
	return (0);
}

//chdir se démerde pour la plupart des cas, mais pas tout.

/*
"cd -"
En revanche, pour "cd -", qui consiste à retourner vers le
chemin précédent où on est allé avec cd, il faut garder en
mémoire ce dernier.
Pour ça on utilise getcwd() avant chdir pour garder en mémoire.
exemple de cd -:
Documents>
Documents> cd 42_projects
42_projects>
42_projects> cd -
~/Documents/42_projects
Documents>
Documents> cd -
~/Documents
42_projects>
et si je fais cd - à l'infini ça reviendra forcément aux deux
mêmes vu que ça garde en mémoire le dernier path que cd a
utilisé.
Donc pour ce cas, je stocke toujours dans un char* le dernier
path donné, et quand l'utilisateur fait cd -, je l'affiche puis
je le fais revenir à ce path.
*/

/*
"cd ~" ou "cd"
Dans ce cas de figure, cd amène au home directory $(HOME).
Attention, cd "~" par contre doit amener à un chemin appelé "~"
*/

/*
"cd -L" et "cd -P"
*/

/*
"cd --"
*/

/*
"cd nom_de_répértoire_non_valide"
*/

/*
Messages d'erreurs de cd:
-commande nulle:
cd: no such file or directory: "nom de la commande tapée"
-plus de 2 arguments:
cd: too many arguments
-deux arguments:
cd: string not in pwd: "nom du premier argument"
à tester avec deux arguments valides du coup mais jsp
*/