/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:01:29 by ngobert           #+#    #+#             */
/*   Updated: 2021/11/25 10:03:55 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*dest;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		dest = ft_lstnew((*f)(lst->content));
		if (!(dest))
		{
			while (first)
			{
				dest = first->next;
				(*del)(first->content);
				free(first);
				first = dest;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, dest);
		lst = lst->next;
	}
	return (dest);
}
