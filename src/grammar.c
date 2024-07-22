#include "../includes/minishell.h"

int	check_quotes(void)
{
	char	*temp;
	int		i;
	int		s;
	int		d;

	i = 0;
	s = 0;
	d = 0;
	temp = ft_strdup(_ms(0)->prompt);
	while (temp[i++])
	{
		if (temp[i] == '\'' && d % 2 == 0)
			s++;
		if (temp[i] == '\"' && s % 2 == 0)
			d++;
	}
	if (s % 2 != 0 || d % 2 != 0)
		return (ft_putstr_fd("minishell: parse error: Warning, string won't be processed, invalid number of quotes\n", 2), -1);
	return (1);
}

int	pipe_syntax_check(t_quote *next)
{
	if (!next)
		return (1); // Syntax error near token '\n'
	if (ft_strcmp(next->token, "cmd") != 0)
		return (2); // Syntax error near next->token
	if (next->id == 1)
		return (3);
	return (0);
}

int	redir_syntax_check(t_quote *next)
{
	printf("Checking...\n");
	if (!next)
		return (1); // Syntax error near token '\n'
	if (ft_strcmp(next->token, "fnm") != 0)
		return (2); // Syntax error near next->token
	printf("All good :)\n");
	return (0);
}

int	check_token_grammar(void)
{
	t_list	*temp;
	t_quote	*curr;
	t_quote	*next;
	int		i;

	i = 0;
	temp = _ms(0)->tokenized_prompt;
	curr = NULL;
	next = NULL;
	while (temp != NULL && i == 0)
	{
		curr = (t_quote *)temp->content;
		if ((t_quote *)temp->next)
			next = (t_quote *)temp->next->content;
		else
			next = NULL;
		if (ft_strcmp(curr->token, "SIMPLE_|") == 0)
			i = pipe_syntax_check(next);
		if (ft_strcmp(curr->token, "SIMPLE_>") == 0 || ft_strcmp(curr->token,
				"SIMPLE_<") == 0 || ft_strcmp(curr->token, "DOUBLE_>") == 0
			|| ft_strcmp(curr->token, "DOUBLE_<") == 0)
			i = redir_syntax_check(next);
		temp = temp->next;
	}
	return (i);
}
