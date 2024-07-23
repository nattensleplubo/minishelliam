/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:10:30 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/23 15:10:31 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	print_tab(char **tab)
{
	int	size;
	int	i;

	i = 0;
	size = tab_size(tab);
	while (i < size)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
