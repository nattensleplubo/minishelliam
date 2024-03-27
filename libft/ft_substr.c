/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:20:44 by ngobert           #+#    #+#             */
/*   Updated: 2021/11/26 13:39:03 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	size_t				j;
	char				*dest;

	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < start)
		i++;
	while (j < len && s[i])
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
