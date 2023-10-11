#include "../../include/minishell.h"

int	verif(char *line, int *i)
{
	int q_count;
	int	j;
	int c;

	q_count = 0;
	j = 0;
	c = *i;
	while (line[c] && q_count != 2)
	{
		if (line[c] == '\"' && line[c + 1] == '.' && line[c + 2] == '/')
		{
			q_count = 1;
		}
		else if (line[c] == '\"' && q_count == 1)
			q_count = 2;
		if (q_count == 0)
			j++;
		c++;
	}
	if (q_count == 2)
		return (j);
	return (0);
}

int	check_quote_file(char *line, int *i, char **word)
{
	int	size;
	int j;
	char	*cp;

	cp = *word;
	size = verif(line, i);
	if (size == 0)
		return (0);
	cp = calloc((size + 1), sizeof(char));
	if (!cp)
		return (0);
	j = 0;
	while(j < size)
	{
		(cp)[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j;
	*word = cp;
	return (1);
}
