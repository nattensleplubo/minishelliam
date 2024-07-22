/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:18:58 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/22 15:51:36 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	free_taboftab(char ***tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free_tab(tab[i++]);
		free(tab);
	}
}

void	free_content(void *content)
{
	t_quote	*quote;

	quote = (t_quote *)content;
	free(quote->token);
	free(quote->str);
	free(quote);
}
