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
		((t_quote *)temp->content)->str
			= ft_calloc(sizeof(char), ft_strlen(_ms(0)->splitted_prompt[i]));
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

char	***make_commands_tab(void)
{
	char	***ret;
	t_list	*temp;
	int		ints[5]; // 0: cmd, 1: i, 2: tab_size, 3 fill_commands, 4 check commands


	temp = _ms(0)->tokenized_prompt;
	ints[1] = 0;
	ints[4] = -1;
	ints[0] = get_number_of_commands();
	ret = (char ***)ft_calloc(sizeof(char **), (ints[0] + 1));
	ret[ints[0]] = NULL;
	while (temp && ints[4] < ints[0])
	{
		if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) == 0)
		{
			ints[4]++;
			ints[3] = 1;
			ints[2] = get_number_of_args(ints[1]);
			ret[ints[1]] = malloc(sizeof(char *) * (ints[2] + 2));
			ret[ints[1]][ints[2] + 1] = NULL;
			ret[ints[1]][0]
				= ft_calloc(sizeof(char), ft_strlen
					(((t_quote *)temp->content)->str));
			ft_strlcpy(ret[ints[1]][0], ((t_quote *)temp->content)->str,
				ft_strlen(((t_quote *)temp->content)->str) + 1);
			ints[1]++;
		}
		if (ft_strncmp(((t_quote *)temp->content)->token, "arg", 3) == 0)
		{
			ret[ints[4]][ints[3]]
				= ft_calloc(sizeof(char), ft_strlen(((t_quote *)temp->content)->str));
			ft_strlcpy(ret[ints[4]][ints[3]], ((t_quote *)temp->content)->str,
				ft_strlen(((t_quote *)temp->content)->str) + 1);
			ints[3]++;
		}
		temp = temp->next;
	}
	return (ret);
}

void	exec(void)
{
	fill_list();
	// ft_lstprint(_ms(0)->tokenized_prompt);
	_ms(0)->commands = make_commands_tab();
}
