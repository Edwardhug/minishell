#include "../../include/minishell.h"

int	find_size_quote(char *line, int *i, t_struct **list_word, t_exec *exec)
{
	int	size;
	int	copy;

	size = 1;
	copy = (*i) + 1;
	while (line[copy] && line[copy] != exec->quote)
	{
		copy++;
		size++;
	}
	if (line[copy] != exec->quote)
		return (fill_node(list_word, find_end_of_the_word(line, i), exec), 0);
	return (size);
}

char	*keep_quotes(char *line, int *i, t_struct **list_word, t_exec *exec)
{
	int		len;
	char	*word;
	int		j;

	len = find_size_quote(line, i, list_word, exec);
	if (len == 0)
		return (NULL);
	word = ft_calloc((len + 2), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j <= len)
	{
		word[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j;
	return (word);
}

char	*find_last_quote(char *line, int *i, t_struct **list_word, t_exec *exec)
{
	char	type_quote;
	int		len;
	char	*word;
	int		j;

	type_quote = line[(*i)];
	exec->quote = type_quote;
	if (type_quote == '\'' && line[(*i) + 1] == '$')
		return (find_end_var(line, i, list_word, exec));
	if (type_quote == '\'')
		return (keep_quotes(line, i, list_word, exec));
	len = find_size_quote(line, i, list_word, exec);
	if (len == 0)
		return (NULL);
	word = ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len - 1)
	{
		word[j] = line[(*i) + j + 1];
		j++;
	}
	(*i) = (*i) + j + 1;
	return (word);
}

void	fill_quote_node(t_struct **list_word, char *word, t_exec *exec)
{
	t_struct	*tmp;
	t_enum		type;

	if (!word)
		return ;
	(void)exec;
	tmp = *list_word;
	type = find_type_enum(tmp, word);
	add_node_back(list_word, new_node(word, type));
}
