#include "../includes/minishell.h"

// What could make the search stop ?
// index finds a `\0`
// index finds a `'` while outside single braces
// index finds a `"`
// index finds a ` `
// index finds a `=`

int get_size_of_var(int j, int blind, char *prompt)
{
	(void)blind;
	int size;

	size = 0;
	while (prompt[j])
	{
		if (ft_isalnum(prompt[j]) != 1 && prompt[j] != '$')
			return (size);
		j++;
		size++;
	}
	return (j);
}

char *is_there_env_to_expend(char *prompt)
{
	int i;
	int j;
	int blind;
	char *ret;

	i = 0;
	blind = 0;
	while (prompt[i])
	{
		if (blind == 0 && prompt[i] == '\'')
			blind = (i++, 1);
		if (blind == 1 && prompt[i] == '\'')
			blind = (i++, 0);
		if (blind == 0 && prompt[i] == '$')
		{
			j = get_size_of_var(i, blind, prompt);
			printf("HI I AM GOING TO ALLOCATE %d OF MEMORY\n", j);
			ret = malloc(sizeof(char) * j + 1);
			j = i;
			while ((prompt[j] && ft_isalnum(prompt[j]) != 0) || prompt[j] == '$')
				ret[blind++] = prompt[j++];
			ret[blind] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

void expend_env_vars(char *prompt)
{
	char *to_expend;

	to_expend = NULL;
	while (1)
	{
		to_expend = is_there_env_to_expend(prompt);
		printf("to_expend: `%s`\n", to_expend);
		break;
	}
}