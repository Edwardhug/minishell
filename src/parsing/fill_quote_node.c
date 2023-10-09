#include "../../include/minishell.h"

int	find_size_quote(char *line, int *i, char quote, t_struct **list_word)
{
	int size;
	int copy;

	size = 1;
	copy = (*i) + 1;
	while (line[copy] && line[copy] != quote)
	{
		copy++;
		size++;
	}
	if (line[copy] != quote)
		return (fill_node(list_word, find_end_of_the_word(line, i)), 0);
	return (size);
}

char	*find_last_quote(char *line, int *i, t_struct **list_word)
{
	char	type_quote;
	int		len;
	char	*word;
	int		j;

	type_quote = line[(*i)];
	len = find_size_quote(line, i, type_quote, list_word);
	if (len == 0)
		return (NULL);
	word = calloc((len + 1), sizeof(char));
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

void fill_quote_node(t_struct **list_word, char *word)
{
	t_struct	*tmp;
	t_enum		type;

	if (!word)
		return ;
	tmp = *list_word;
	type = find_type_enum(tmp, word);		//currently working on this
	add_node_back(list_word, new_node(word, type));
}