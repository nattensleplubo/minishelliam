/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:11:03 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/29 14:21:29 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	changeValue(char **oldstring, char *newstring)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(newstring);
	free(*oldstring);
	*oldstring = malloc(sizeof(char) * size + 1);
	while (newstring[i])
	{
		(*oldstring)[i] = newstring[i];
		i++;
	}
	(*oldstring)[i] = '\0';
}

void	addToTab(char ***tab, const char *newstring)
{
	int		size;
	int		i;
	char	**newarray;

	i = 0;
	size = 0;
		size++;
	newarray = malloc((size + 2) * sizeof(char *));
	if (newarray == NULL)
	{}
	while ((*tab)[i])
	{
		newarray[i] = (*tab)[i];
		i++;
	}
	newarray[size] = malloc((strlen(newstring) + 1) * sizeof(char));
	if (newarray[size] == NULL)
	{}
	strcpy(newarray[size], newstring);
	newarray[size + 1] = NULL;
	free(*tab);
	*tab = newarray;
}

void	ft_export(char **arg)
{
	int		i[3];
	char	*env;
trepo;pppwqpz
	i[0] = 1;
	while (arg[i[0]])
	{
		if (arg[i[0]][0] == '=' || isdigit(arg[i[0]][0]))
		{
			printf("export : '%s': not a valid identifier\n", arg[i[0]]);
			return ;
		}
		i[1] = 0;
		while (arg[i[0]][i[1]] != '=' && arg[i[0]][i[1]])
			i[1]++;
		env = calloc(sizeof(char), i[1] + 1);
		if (!env)
		{}
		ft_strlcpy(env, arg[i[0]], i[1] + 1);
		i[2] = get_index_of_varname(env);
		if (i[2] == -1 && arg[i[0]][i[1]] == '=')
			addToTab(&_ms(0)->env, arg[i[0]]);
		else if (i[2] >= 0 && arg[i[0]][i[1]] == '=')
			changeValue(&_ms(0)->env[i[2]], arg[i[0]]);
		i[0]++;
		free(env);
	}
}
