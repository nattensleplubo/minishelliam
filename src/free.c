/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:18:58 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/31 00:09:36 by lzaengel         ###   ########.fr       */
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

void	*ft_cal_te(size_t count, size_t size, char ***tab, char *str)
{
	void	*dest;

	dest = malloc(count * size);
	if (!dest)
	{
		if (tab)
			free_taboftab(tab);
		if (str)
			free(str);
		ft_exit(NULL, NULL);
	}
	ft_bzero(dest, count * size);
	return (dest);
}

void	ft_dup(int fd1, int fd2, int pfd[2], int tofree)
{
	if (dup2(fd1, fd2) == -1)
	{
		if (tofree == 1)
			close(fd1);
		if (tofree == 2)
			close(fd2);
		if (tofree == 3)
		{
			close(fd1);
			close(fd2);
		}
		if (pfd != NULL)
		{
			close(pfd[0]);
			close(pfd[1]);
		}
		ft_pexit(-100);
	}
}
