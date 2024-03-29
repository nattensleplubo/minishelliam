#include "../includes/minishell.h"

// What could make the search stop ?
// index finds a `\0`
// index finds a `'` while outside single braces
// index finds a `"`
// index finds a ` `
// index finds a `=`

int get_size_of_var(int j, int blind)
{
	(void)blind;
	int size;

	size = 0;
	while (_ms(0)->prompt[j])
	{
		if (ft_isalnum(_ms(0)->prompt[j]) != 1 && _ms(0)->prompt[j] != '$')
			return (size);
		j++;
		size++;
	}
	return (size);
}

void	skip_single_quote(int *i)
{
	*i = *i + 1;
	while (_ms(0)->prompt[*i] != '\'')
		*i = *i + 1;
	*i = *i + 1;
}

int	should_be_skipped(int i)
{
	int before;
	int after;

	before = i;
	after = i;
	while (_ms(0)->prompt[after] && _ms(0)->prompt[after] != '\"')
		after++;
	while (before >= 0 && _ms(0)->prompt[before] != '\"')
		before--;
	if (_ms(0)->prompt[before] == '\"' && _ms(0)->prompt[after] == '\"')
		return (1);
	return (0);
}

char *is_there_env_to_expend(int *index)
{
	int i;
	int j;
	int blind;
	char *ret;

	i = 0;
	blind = 0;
	while (_ms(0)->prompt[i])
	{
		if (_ms(0)->prompt[i] == '\'' && should_be_skipped(i) != 1)
			skip_single_quote(&i);
		if (_ms(0)->prompt[i] == '$')
		{
			*index = i;
			j = get_size_of_var(i, blind);
			ret = malloc(sizeof(char) * j + 1);
			j = i;
			while ((_ms(0)->prompt[j] && ft_isalnum(_ms(0)->prompt[j]) != 0) || _ms(0)->prompt[j] == '$')
				ret[blind++] = _ms(0)->prompt[j++];
			ret[blind] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*delete_var(char *to_expend, int index)
{
	char *new;
	int i;
	int j;
	int to_skip;

	i = 0;
	j = 0;
	to_skip = ft_strlen(to_expend);
	new = malloc(sizeof(char) * (ft_strlen(_ms(0)->prompt) - to_skip));
	while (_ms(0)->prompt[i])
	{
		if (i < index || i >= index + to_skip)
			new[j++] = _ms(0)->prompt[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void expend_env_vars()
{
	char *to_expend;
	int index;

	to_expend = NULL;
	index = -1;
	while (1)
	{	
		to_expend = is_there_env_to_expend(&index);
		if (!to_expend)
			break;
		printf("to_expend: `%s` at %d\n", to_expend, index);
		_ms(0)->prompt = delete_var(to_expend, index);
		// prompt = insert_value(prompt, to_expend, index);
	}
}