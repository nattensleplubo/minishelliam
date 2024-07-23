/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:54:39 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/23 16:54:40 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_set(int i, int set)
{
	int		j;
	int		k;
	int		size;
	char	*newstring;
	char	*oldstring;

	j = 0;
	k = 0;
	size = 0;
	while (_ms(0)->splitted_prompt[i][j])
	{
		if (_ms(0)->splitted_prompt[i][j] != set)
			size++;
		j++;
	}
	newstring = malloc(sizeof(char) * size + 1);
	j = 0;
	while (_ms(0)->splitted_prompt[i][j])
	{
		if (_ms(0)->splitted_prompt[i][j] != set)
		{
			newstring[k] = _ms(0)->splitted_prompt[i][j];
			j++;
			k++;
		}
		else
		{
			j++;
		}
	}
	newstring[k] = '\0';
	oldstring = _ms(0)->splitted_prompt[i];
	_ms(0)->splitted_prompt[i] = newstring;
	free(oldstring);
}

int	findset(int i)
{
	int	set;
	int	j;

	j = 0;
	set = 41;
	while (_ms(0)->splitted_prompt[i][j])
	{
		if (_ms(0)->splitted_prompt[i][j] == set)
		{
			set++;
			j = 0;
		}
		j++;
	}
	return (set);
}

int	find_next_quote_2(char const *s, char c, int i)
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

void	delete_quotes_word(int i)
{
	int	j;
	int	set;
	int	next;

	j = 0;
	set = findset(i);
	while (_ms(0)->splitted_prompt[i][j])
	{
		if (_ms(0)->splitted_prompt[i][j] == '"'
			|| _ms(0)->splitted_prompt[i][j] == 39)
		{
			if (find_next_quote_2(_ms(0)->splitted_prompt[i],
					_ms(0)->splitted_prompt[i][j], j) != j)
			{
				next = find_next_quote_2(_ms(0)->splitted_prompt[i],
						_ms(0)->splitted_prompt[i][j], j);
				_ms(0)->splitted_prompt[i][next] = set;
				_ms(0)->splitted_prompt[i][j] = set;
				j = next;
			}
		}
		j++;
	}
	delete_set(i, set);
}

void	delete_quotes(void)
{
	int	size;
	int	i;

	i = 0;
	size = tab_size(_ms(0)->splitted_prompt);
	while (i < size)
	{
		delete_quotes_word(i);
		i++;
	}
}
