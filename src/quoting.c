/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:56:33 by lzaengel          #+#    #+#             */
/*   Updated: 2024/05/31 20:12:50 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	find_next_quotes(char const *s, char c, int i)
{
	int	j;

	j = i + 1;
	while (s[j])
	{
		if (s[j] == c)
		{
			return (j - i);
		}
		j++;
	}
	return (0);
}

void	add_word(char const *s, int i, char *word)
{
	int		j[3];

	j[1] = 0;
	j[0] = 0;
	j[2] = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ' && !is_pipe(s[i]))
	{
		j[2] = 1;
		if (s[i] == 39 || s[i] == '"')
		{
			j[1] = i + find_next_quotes(s, s[i], i);
			while (i < j[1])
				word[j[0]++] = s[i++];
		}
		word[j[0]++] = s[i++];
	}
	if (is_pipe(s[i]) && j[2] == 0)
	{
		word[j[0]++] = s[i++];
		if (s[i] && s[i] == s[i - 1])
			word[j[0]++] = s[i++];
	}
	word[j[0]] = '\0';
}

int	nextword(char const *s, int i, int step)
{
	int		j;
	int		bow;

	j = 0;
	bow = 0;
	while (s[i] == ' ')
		i++;
	while (s[i + j] && s[i + j] != ' ' && !is_pipe(s[i + j]))
	{
		bow = 1;
		if (s[i + j] == 39 || s[i + j] == '"')
			j = j + find_next_quotes(s, s[i + j], i + j);
		j++;
	}
	if (is_pipe(s[i + j]) && bow == 0)
	{
		if (s[i + j + 1] && s[i + j] == s[i + j + 1])
			j++;
		j++;
	}
	if (step == 1)
		return (j);
	if (j > 0)
		return (i + j);
	return (0);
}

int	count_word(char const *s)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while ((nextword(s, i, 0)) > 0)
	{
		i = nextword(s, i, 0);
		wc++;
	}
	return (wc);
}

char	**prompt_splitter(char const *s)
{
	char	**tab;
	int		j[4];

	if (s == NULL)
		return (NULL);
	j[2] = count_word(s);
	j[0] = 0;
	j[1] = 0;
	j[3] = 0;
	tab = malloc(sizeof(char *) * (j[2] + 1));
	if (!tab)
	{
	}
	while (j[3] < j[2])
	{
		j[0] = nextword(s, j[1], 1);
		tab[j[3]] = malloc(sizeof(char) * j[0] + 1);
		if (!tab[j[3]])
		{
		}
		add_word(s, j[1], tab[j[3]]);
		j[1] = (j[3]++, nextword(s, j[1], 0));
	}
	tab[j[3]] = 0;
	return (tab);
}
