/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:53:34 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/30 22:55:14 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_list(void)
{
	int		i;
	int		size;
	t_list	*temp;

	temp = _ms(0)->tokenized_prompt;
	size = tab_size(_ms(0)->splitted_prompt);
	i = 0;
	while (i < size)
	{
		((t_quote *)temp->content)->str = ft_calloc(sizeof(char),
				(ft_strlen(_ms(0)->splitted_prompt[i])) + 1);
		if (!((t_quote *)temp->content)->str)
			ft_exit(NULL, NULL);
		ft_strlcpy(((t_quote *)temp->content)->str, _ms(0)->splitted_prompt[i],
			ft_strlen(_ms(0)->splitted_prompt[i]) + 1);
		i++;
		temp = temp->next;
	}
}

int	get_number_of_commands(void)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = _ms(0)->tokenized_prompt;
	while (temp)
	{
		if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) == 0)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	alloc_commands_tab(int ints[5], t_list *temp, char ***ret)
{
	if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) == 0)
	{
		ints[4]++;
		ints[3] = 1;
		ints[2] = get_number_of_args(ints[1]);
		ret[ints[1]] = ft_cal_te(sizeof(char *), (ints[2] + 2), ret, NULL);
		ret[ints[1]][ints[2] + 1] = NULL;
		ret[ints[1]][0] = ft_cal_te(sizeof(char),
				(ft_strlen(((t_quote *)temp->content)->str) + 1), ret, NULL);
		ft_strlcpy(ret[ints[1]][0], ((t_quote *)temp->content)->str,
			ft_strlen(((t_quote *)temp->content)->str) + 1);
		ints[1]++;
	}
	if (ft_strncmp(((t_quote *)temp->content)->token, "arg", 3) == 0)
	{
		ret[ints[4]][ints[3]] = ft_cal_te(sizeof(char),
				(ft_strlen(((t_quote *)temp->content)->str) + 1), ret, NULL);
		ft_strlcpy(ret[ints[4]][ints[3]], ((t_quote *)temp->content)->str,
			ft_strlen(((t_quote *)temp->content)->str) + 1);
		ints[3]++;
	}
}

char	***make_commands_tab(void)
{
	char	***ret;
	t_list	*temp;
	int		ints[5];

	temp = _ms(0)->tokenized_prompt;
	ints[1] = 0;
	ints[4] = -1;
	ints[0] = get_number_of_commands();
	ret = (char ***)ft_calloc(sizeof(char **), (ints[0] + 1));
	if (!ret)
		ft_exit(NULL, NULL);
	ret[ints[0]] = NULL;
	while (temp && ints[4] < ints[0])
	{
		alloc_commands_tab(ints, temp, ret);
		temp = temp->next;
	}
	return (ret);
}

void	exec(void)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (_ms(0)->commands)
	{
		while (_ms(0)->commands[i])
		{
			while (_ms(0)->commands[i][j])
			{
				free(_ms(0)->commands[i][j++]);
			}
			j = 0;
			free(_ms(0)->commands[i++]);
		}
		free(_ms(0)->commands);
	}
	fill_list();
	_ms(0)->commands = make_commands_tab();
}
