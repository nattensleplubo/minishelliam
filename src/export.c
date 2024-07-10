/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:11:03 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/27 19:56:25 by ngobert          ###   ########.fr       */
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

int	ft_export(char **arg)
{
	int		i[4];
	char	*env;

	i[0] = 1;
	i[3] = 0;
	while (arg[i[0]])
	{
		i[1] = 0;
		while (arg[i[0]][i[1]] && (i[1] == 0 || arg[i[0]][i[1]] != '='))
		{
			if (ft_isalnum(arg[i[0]][i[1]]) == 0
				|| arg[i[0]][0] == '=' || isdigit(arg[i[0]][0]))
			{
				i[3] = 1;
				ft_putstr_fd(" not a valid identifier\n", 2);
				break ;
			}
			i[1]++;
		}
		if (i[3] != 1)
		{
			env = calloc(sizeof(char), i[1] + 1);
			if (!env)
			{
			}
			ft_strlcpy(env, arg[i[0]], i[1] + 1);
			i[2] = get_index_of_varname(env);
			if (i[2] == -1 && arg[i[0]][i[1]] == '=')
				addtotab(&_ms(0)->env, arg[i[0]]);
			else if (i[2] >= 0 && arg[i[0]][i[1]] == '=')
				changevalue(&_ms(0)->env[i[2]], arg[i[0]]);
			free(env);
		}
		i[0]++;
	}
	return (i[3]);
}
