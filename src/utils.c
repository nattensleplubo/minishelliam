/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:57:08 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/23 23:39:51 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_number_of_args(int i)
{
	int		ret_size;
	int		j;
	t_list	*temp;

	j = 0;
	ret_size = 0;
	temp = _ms(0)->tokenized_prompt;
	while (j <= i)
	{
		if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) == 0)
			j++;
		temp = temp->next;
	}
	while (temp && ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) != 0)
	{
		if (ft_strncmp(((t_quote *)temp->content)->token, "arg", 3) == 0)
			ret_size++;
		temp = temp->next;
	}
	return (ret_size);
}

int	size_without_set(int i, int set)
{
	int	j;
	int	size;

	j = 0;
	size = 0;
	while (_ms(0)->splitted_prompt[i][j])
	{
		if (_ms(0)->splitted_prompt[i][j] != set)
			size++;
		j++;
	}
	return (size);
}

void	ft_lstprint(t_list *lst)
{
	t_list	*temp;

	printf("\033[0;33mTOKENIZED PROMPT :\n");
	if (lst == NULL)
		return ;
	temp = lst;
	printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
		((t_quote *)temp->content)->str);
	while (temp->next)
	{
		temp = temp->next;
		printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
			((t_quote *)temp->content)->str);
	}
	printf("----------------------------------------------\033[0m\n");
}

int	is_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
