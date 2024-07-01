/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:02:40 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/29 12:06:46 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	deletefromtab(char ***tab, int index)
{
	int		size;
	int		i;
	int		j;
	char	**newarray;

	i = 0;
	j = 0;
	size = 0;
	while ((*tab)[size] != NULL)
		size++;
	newarray = malloc((size) * sizeof(char *));
	if (newarray == NULL)
	{}
	while ((*tab)[j])
	{
		if (j != index)
			newarray[i++] = (*tab)[j];
		j++;
	}
	newarray[size - 1] = NULL;
	free((*tab)[index]);
	free(*tab);
	*tab = newarray;
}

int	ft_unset(char **arg)
{
	int	i;
	int	index;

	i = 1;
	while (arg[i])
	{
		index = get_index_of_varname(arg[i]);
		if (index >= 0)
			deletefromtab(&_ms(0)->env, index);
		i++;
	}
	return (0);
}