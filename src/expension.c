/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:19:31 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/23 16:40:23 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_there_env_to_expand(int *index)
{
	int		i;
	int		j;

	i = 0;
	while (_ms(0)->prompt[i])
	{
		if (_ms(0)->prompt[i] == '\'' && should_be_skipped(i) != 1)
			skip_single_quote(&i);
		if (_ms(0)->prompt[i] == '$')
		{
			j = get_size_of_var(i, j);
			if (j > 1)
			{
				*index = i;
				return (calloc_var(j, i));
			}
		}
		i++;
	}
	return (NULL);
}

char	*is_there_ret_to_expand(int *index)
{
	int		i;
	char	*ret;

	i = 0;
	while (_ms(0)->prompt[i])
	{
		if (_ms(0)->prompt[i] == '\'' && should_be_skipped(i) != 1)
			skip_single_quote(&i);
		if (_ms(0)->prompt[i] == '$')
		{
			*index = i;
			if (_ms(0)->prompt[i + 1] == '?')
			{
				ret = "$?";
				return (ret);
			}
		}
		i++;
	}
	return (NULL);
}

char	*delete_var(char *to_expend, int index)
{
	char	*new;
	int		i;
	int		j;
	int		to_skip;

	i = 0;
	j = 0;
	to_skip = ft_strlen(to_expend);
	new = calloc(sizeof(char), (ft_strlen(_ms(0)->prompt) - to_skip + 1));
	while (_ms(0)->prompt[i])
	{
		if (i < index || i >= index + to_skip)
			new[j++] = _ms(0)->prompt[i];
		i++;
	}
	new[j] = '\0';
	free(_ms(0)->prompt);
	return (new);
}

char	*insert_value(char *to_expand, int index)
{
	char	*new;
	char	*vl;
	int		i;
	int		j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	if (to_expand && to_expand[1] == '?')
		vl = ft_itoa(_ms(0)->errnum);
	else
		vl = get_value_of_varname(to_expand + 1);
	if (!vl)
		vl = ft_strdup("");
	new = calloc(sizeof(char), (ft_strlen(_ms(0)->prompt) + ft_strlen(vl) + 2));
	while (x < ft_strlen(_ms(0)->prompt) + ft_strlen(vl))
	{
		if (i == index)
			while (vl[j])
				new[x++] = vl[j++];
		new[x++] = _ms(0)->prompt[i++];
	}
	new[x] = '\0';
	return (free(_ms(0)->prompt), free(vl), new);
}

void	expend_env_vars(void)
{
	char	*to_expand;
	int		index;

	to_expand = NULL;
	index = -1;
	while (1)
	{
		to_expand = is_there_ret_to_expand(&index);
		if (!to_expand)
			break ;
		_ms(0)->prompt = delete_var(to_expand, index);
		_ms(0)->prompt = insert_value(to_expand, index);
	}
	index = -1;
	while (1)
	{
		to_expand = is_there_env_to_expand(&index);
		if (!to_expand)
			break ;
		_ms(0)->prompt = delete_var(to_expand, index);
		_ms(0)->prompt = insert_value(to_expand, index);
		free(to_expand);
	}
}
