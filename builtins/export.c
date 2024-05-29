#include "../includes/minishell.h"


void	changeValue(char **OldString, char *NewString)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(NewString);
	free(*OldString);
	*OldString = malloc(sizeof(char) * size + 1);
	while (NewString[i])
	{
		(*OldString)[i] = NewString[i];
		i++;
	}
	(*OldString)[i] = '\0';
}

void	addToTab(char ***tab, const char *newString)
{
	int		size;
	int		i;
	char	**newArray;

	i = 0;
	size = 0;
	while ((*tab)[size] != NULL)
		size++;
	newArray = malloc((size + 2) * sizeof(char *));
	if (newArray == NULL)
	{}
	while ((*tab)[i])
	{
		newArray[i] = (*tab)[i];
		i++;
	}
    newArray[size] = malloc((strlen(newString) + 1) * sizeof(char));
    if (newArray[size] == NULL)
	{}
    strcpy(newArray[size], newString);
    newArray[size + 1] = NULL;
    free(*tab);
    *tab = newArray;
}

void	ft_export(char **arg)
{
	int		i[2];
	char	*env;
	int		indexenv;

	i[0] = 1;
	while (arg[i[0]])
	{
		i[1] = 0;
		while (arg[i[0]][i[1]] != '=' && arg[i[0]][i[1]])
			i[1]++;
		env = calloc(sizeof(char), i[1] + 1);
		if (!env)
		{}
		ft_strlcpy(env, arg[i[0]], i[1] + 1);
		indexenv = get_index_of_varname(env);
		if (arg[i[0]][i[1]] == '=')
		{
			if (indexenv == -1)
				addToTab(&_ms(0)->env, arg[i[0]]);
			else if (indexenv >= 0)
				changeValue(&_ms(0)->env[indexenv], arg[i[0]]);
		}
		i[0]++;
		free(env);
	}
}

