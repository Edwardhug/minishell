/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:37:12 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/19 14:28:36 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
de préférence un double tableau en argument avec tous les args.

void	ft_echo(t_struct *lst)
{
	On fait une boucle qui parcourt toute la liste.
	On passe le premier argument qui est echo.
	On regarde si le second argument est -n, et on utilise un bool pour le garder en mémoire.
	On passe ensuite à la chaîne d'après.
	On imprime chaque argument un à un avec ft_printf.
	À la fin, si il y avait un -n on ne fait pas de retour à la ligne, autrement on en fait un.
}

pas oublier:
"bonjour""bonjour" renvoie: bonjourbonjour
"bonjour" "bonjour" renvoie: bonjour bonjour
*/