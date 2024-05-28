/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:22:31 by lzaengel          #+#    #+#             */
/*   Updated: 2024/05/28 18:50:18 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	post_pipe(char *s, t_list **lst)
{
	lst = &(*lst)->next;
	if (*lst == NULL)
	{}
	((t_quote *)(*lst)->content)->token = malloc(sizeof(char) * 4);
	if (!((t_quote *)(*lst)->content)->token)
	{}
	printf("bruh\n");
	if (s[0] == '|')
		ft_strlcpy(((t_quote *)(*lst)->content)->token, "cmd", 4);
	else if (s[0] == '<' || s[0] == '>')
		ft_strlcpy(((t_quote *)(*lst)->content)->token, "fnm", 4);
}

int	is_redirection_or_pipe(t_list **lst, int i, int cmd)
{
	char	*s;	

	s = _ms(0)->splitted_prompt[i];
	if (s[0] == '>' || s[0] == '|' || s[0] == '<')
	{
		free(((t_quote *)(*lst)->content)->token);
		((t_quote *)(*lst)->content)->token = malloc(sizeof(char) * 9);
		if (!((t_quote *)(*lst)->content)->token)
		{}	//protect
		if (s[1] == s[0])
			ft_strlcpy(((t_quote *)(*lst)->content)->token, "DOUBLE__", 9);
		else
			ft_strlcpy(((t_quote *)(*lst)->content)->token, "SIMPLE__", 9);
		((t_quote *)(*lst)->content)->token[7] = s[0];
		((t_quote *)(*lst)->content)->token[8] = '\0';
	}
	if (is_pipe(_ms(0)->splitted_prompt[i][0])
		&& !is_pipe(_ms(0)->splitted_prompt[i + 1][0]))
		post_pipe(s, lst);
	if(s[0] == '|' && is_pipe(_ms(0)->splitted_prompt[i + 1][0]))
		return (0);
	return (cmd);
}

void	add_token(t_list **lst,int size)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (i[0] < size)
	{
		if (!((t_quote *)(*lst)->content)->token)
		{
			((t_quote *)(*lst)->content)->token = malloc(sizeof(char) * 4);
			if (!((t_quote *)(*lst)->content)->token)
			{}
			if (i[1] == 0 && !is_pipe(_ms(0)->splitted_prompt[i[0]][0]))
				((t_quote *)(*lst)->content)->token = (i[1]++, "cmd\0");
			else if (is_pipe(_ms(0)->splitted_prompt[i[0]][0]))
				i[1] = is_redirection_or_pipe(lst, i[0], i[1]);
			else
				((t_quote *)(*lst)->content)->token = "arg\0";
		}
		lst = (i[0]++, &(*lst)->next);
	}
}

t_quote *create_struct(char *arg, int i)
{
	t_quote *content;

	(void)arg;
	content = malloc(sizeof(t_quote));
	if(!content)
	{
	}
	content->token = NULL;
	content->id = i;
	return (content);
}
void free_content(void *content)
{
    t_quote *quote = (t_quote *)content;
    //free(quote->token);
    free(quote);
}

void ft_token(void)
{
	int	size;
	int	i;
	t_list *node;	

	i = 0;
  	size = tab_size(_ms(0)->splitted_prompt);
	if(_ms(0)->tokenized_prompt)
	{
		ft_lstclear(&_ms(0)->tokenized_prompt, free_content);
	}
	while (i < size)
	{
		node =  ft_lstnew(create_struct(_ms(0)->splitted_prompt[i], i));
		if(!node)
		{
		}
		ft_lstadd_back(&_ms(0)->tokenized_prompt, node);
		i++;
	}
	add_token(&_ms(0)->tokenized_prompt, size);
}