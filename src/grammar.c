#include "../includes/minishell.h"

int check_quotes()
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
		return (ft_putstr_fd("minishell: Warning, string won't be processed, invalid number of quotes\n", 2), -1);
	return (1);
}