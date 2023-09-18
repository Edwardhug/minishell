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

#include "test.h"

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
		return (perror("chdir"), 1);
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