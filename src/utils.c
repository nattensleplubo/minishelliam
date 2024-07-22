/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:57:08 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/22 16:17:16 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
