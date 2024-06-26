/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:56:33 by lzaengel          #+#    #+#             */
/*   Updated: 2024/05/17 16:36:26 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_next_quote(char const *s, char c, int i)
{
	int	j;

	j = i;
	i++;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (j);
}

int	is_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	wcounter(char const *s)
{
	int	wc;
	int	i;
	int	sep;

	wc = 0;
	i = 0;
	sep = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != ' ')
		sep = (i++, 1);
	while (s[i] != '\0')
	{
		if (s[i] == 39 || s[i] == '"')
			i = find_next_quote(s, s[i], i);
		if (is_pipe(s[i]) && !(s[i - 1] == ' ' && s[i + 1] == ' '))
		{
			if (s[i - 1] != ' ' && !is_pipe(s[i - 1]))
				wc++;
			wc++;
			if (s[i + 1] == s[i])
				i++;
			while (s[i + 1] == ' ')
				i++;
			sep = 0;
		}
		if (s[i++] == ' ')
		{
			if (sep == 1)
				sep = (wc++, 0);
		}
		else
			sep = 1;
	}
	if (s[i - 1] != ' ' && sep == 1)
		wc++;
	return (wc);
}

char	**ft_free(int wl, char **tab)
{
	while (wl >= 0)
	{
		free(tab[wl]);
		wl--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split2(char **tab, char const *s)
{
	int	i;
	int	j;
	int	wl;

	i = 0;
	j = 0;
	wl = 0;
	while (s[i] != 0 && s[i] == ' ')
		i++;
	while (wl < wcounter(s))
	{
		while (s[i] != ' ' && s[i] != '\0')
		{
			if (s[i] == 39 || s[i] == '"')
			{
				j = j + (find_next_quote(s, s[i], i) - i);
				i = find_next_quote(s, s[i], i);
			}
			if (is_pipe(s[i]) && !( s[i + 1] == ' ' && (i == 0 || s[i - 1] == ' ')))
			{
				if ((s[i - 1] != ' ' && !is_pipe(s[i - 1])))
					tab[wl++] = ft_substr(s, i - j, j);
				j = 0;
				if (s[i + 1] == s[i])
				{
					i++;
					j++;
				}
				tab[wl++] = ft_substr(s, i - j, j + 1);
				j = 0;
				while (s[i + 1] == ' ' && s[i] != '\0')
					i++;
			}
			else
				j++;
			i++;
		}
		tab[wl] = ft_substr(s, i - j, j);
		if (!tab[wl])
			return (ft_free(wl, tab));
		while (s[i] == ' ' && s[i] != '\0')
			i++;
		j = (wl++, 0);
	}
	tab[wl] = 0;
	return (tab);
}

char	**prompt_splitter(char const *s)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (wcounter(s) + 1));
	//printf("%d\n", wcounter(s));
	if (!tab)
		return (NULL);
	return (ft_split2(tab, s));
}
