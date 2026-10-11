/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>          +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 12:00:00 by jrenault            #+#    #+#           */
/*   Updated: 2026/10/11 12:00:00 by jrenault           ###   ########.f      */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*get_display_path(t_exec *exec)
{
	char	*cwd;
	char	*home;
	char	*short_path;
	size_t	len;

	cwd = getcwd(NULL, 0);
	if (!cwd && get_var(exec, "PWD"))
		cwd = ft_strdup(get_var(exec, "PWD"));
	if (!cwd)
		return (NULL);
	home = get_var(exec, "HOME");
	if (!home || !home[0])
		return (cwd);
	len = ft_strlen(home);
	if (ft_strncmp(cwd, home, len) != 0 || (cwd[len] && cwd[len] != '/'))
		return (cwd);
	short_path = ft_strjoin("~", cwd + len);
	free(cwd);
	return (short_path);
}

char	*build_prompt(t_exec *exec)
{
	char	*path;
	char	*prompt;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (NULL);
	path = get_display_path(exec);
	if (!path)
		return (NULL);
	prompt = ft_strjoin(PROMPT_NAME, path);
	free(path);
	if (g_error_value / 256 == 0)
		prompt = join_and_free(prompt, PROMPT_OK);
	else
		prompt = join_and_free(prompt, PROMPT_KO);
	return (prompt);
}
