/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:54:01 by ngobert           #+#    #+#             */
/*   Updated: 2021/11/24 10:04:03 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_c(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

char	*ft_splitter(int *i, char const *str, int size)
{
	int		j;
	char	*dest;

	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	j = 0;
	while (j < size)
	{
		dest[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	dest[size] = '\0';
	return (dest);
}

int	num_word(char const *str, char charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (is_c(str[i], charset) == 0)
		{
			counter++;
			while (str[i] && is_c(str[i], charset) == 0)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char charset)
{
	char	**dest;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	dest = malloc(sizeof(char *) * (num_word(s, charset) + 1));
	if (!dest)
		return (NULL);
	dest[num_word(s, charset)] = NULL;
	while (s[i])
	{
		if (is_c(s[i], charset) == 0)
		{
			j = 0;
			while (s[i + j] && is_c(s[i + j], charset) == 0)
				j++;
			dest[k] = ft_splitter(&i, s, j);
			k++;
		}
		else
			i++;
	}
	return (dest);
}
