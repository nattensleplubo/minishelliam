/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:11:03 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/21 19:31:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	changevalue(char **oldstring, char *newstring)
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

void	addtotab(char ***tab, const char *newstring)
{
	int		size;
	int		i;
	char	**newarray;

	i = 0;
	size = 0;
	while ((*tab)[size] != NULL)
		size++;
	newarray = malloc((size + 2) * sizeof(char *));
	if (newarray == NULL)
	{
	}
	while ((*tab)[i])
	{
		newarray[i] = (*tab)[i];
		i++;
	}
	newarray[size] = malloc((strlen(newstring) + 1) * sizeof(char));
	if (newarray[size] == NULL)
	{
	}
	strcpy(newarray[size], newstring);
	newarray[size + 1] = NULL;
	free(*tab);
	*tab = newarray;
}

void	ft_export2(char **arg, int i, int j, int k)
{
	char	*env;

	env = calloc(sizeof(char), i + 1);
	if (!env)
	{
	}
	ft_strlcpy(env, arg[j], i + 1);
	k = get_index_of_varname(env);
	if (k == -1 && arg[j][i] == '=')
		addtotab(&_ms(0)->env, arg[j]);
	else if (k >= 0 && arg[j][i] == '=')
		changevalue(&_ms(0)->env[k], arg[j]);
	free(env);
}

int	ft_export(char **arg)
{
	int	i[4];

	i[0] = 1;
	i[3] = 0;
	i[2] = 0;
	while (arg[i[0]])
	{
		i[1] = 0;
		while (arg[i[0]][i[1]] && (i[1] == 0 || arg[i[0]][i[1]] != '='))
		{
			if (ft_isalnum(arg[i[0]][i[1]]) == 0 || arg[i[0]][0] == '='
				|| isdigit(arg[i[0]][0]))
			{
				i[3] = 1;
				ft_putstr_fd(" not a valid identifier\n", 2);
				break ;
			}
			i[1]++;
		}
		if (i[3] != 1)
			ft_export2(arg, i[1], i[0], i[2]);
		i[0]++;
	}
	return (i[3]);
}
