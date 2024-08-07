/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:54:48 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/30 19:47:18 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_of_varname(char *varname)
{
	int		i;
	char	*value;
	int		j;
	int		k;

	value = NULL;
	i = get_index_of_varname(varname);
	if (i == -1)
		return (NULL);
	j = ft_strlen(varname) + 1;
	k = 0;
	while (_ms(0)->env[i][j])
		j = (k++, j + 1);
	value = ft_calloc(sizeof(char), k + 1);
	if (!value)
		ft_exit(NULL, NULL);
	j = ft_strlen(varname) + 1;
	k = 0;
	while (_ms(0)->env[i][j])
	{
		value[k] = _ms(0)->env[i][j];
		j = (k++, j + 1);
	}
	value[k] = '\0';
	return (value);
}

int	get_index_of_varname(char *varname)
{
	int		i;
	int		j;
	char	*current;

	i = 0;
	current = NULL;
	while (_ms(0)->env[i])
	{
		j = 0;
		while (_ms(0)->env[i][j] != '=' && _ms(0)->env[i][j] != '\0')
			j++;
		current = ft_calloc(sizeof(char), j + 1);
		if (!current)
			ft_exit(NULL, NULL);
		ft_strlcpy(current, _ms(0)->env[i], j + 1);
		if (ft_strcmp(current, varname) == 0)
			return (free(current), i);
		else
			i = (free(current), i + 1);
	}
	return (-1);
}

void	init_env(char **env)
{
	int	i;

	i = tab_size(env);
	_ms(0)->env = ft_calloc(sizeof(char *), i + 1);
	if (!_ms(0)->env)
		exit(0);
	i = 0;
	while (env[i])
	{
		_ms(0)->env[i] = ft_strdup(env[i]);
		i++;
	}
	_ms(0)->env[i] = NULL;
}
