/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:35:01 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/28 14:38:02 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_size_of_var(int j, int blind)
{
	int	size;

	(void)blind;
	size = 0;
	while (_ms(0)->prompt[j])
	{
		if (ft_isalnum(_ms(0)->prompt[j]) != 1 && _ms(0)->prompt[j] != '$')
			return (size);
		j++;
		size++;
	}
	return (size);
}

void	skip_single_quote(int *i)
{
	*i = *i + 1;
	while (_ms(0)->prompt[*i] && _ms(0)->prompt[*i] != '\'')
		*i = *i + 1;
}

char	*calloc_var(int j, int i)
{
	char	*ret;
	int		blind;

	blind = 0;
	ret = calloc(sizeof(char), j + 1);
	if (!ret)
	{
	}
	j = i;
	while ((_ms(0)->prompt[j] && ft_isalnum(_ms(0)->prompt[j]) != 0)
		|| _ms(0)->prompt[j] == '$')
		ret[blind++] = _ms(0)->prompt[j++];
	ret[blind] = '\0';
	return (ret);
}

int	should_be_skipped(int i)
{
	int	before;
	int	after;
	int	inside[2];

	before = i;
	after = i;
	inside[0] = 0;
	inside[1] = 0;
	while (inside[0] < i)
	{
		if (_ms(0)->prompt[inside[0]] == '\"' && inside[1] == 0)
			inside[1] = 1;
		else if (_ms(0)->prompt[inside[0]] == '\"' && inside[1] == 1)
			inside[1] = 0;
		inside[0]++;
	}
	while (_ms(0)->prompt[after] && _ms(0)->prompt[after] != '\"')
		after++;
	while (before > 0 && _ms(0)->prompt[before] != '\"')
		before--;
	if (_ms(0)->prompt[after])
		if (_ms(0)->prompt[before] == '\"' && _ms(0)->prompt[after] == '\"'
			&& inside[1] == 1)
			return (1);
	return (0);
}
