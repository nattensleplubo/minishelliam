#include "../includes/minishell.h"
// teub = CUL
// echo bonjour '$teub' "$teub" $teub | echo cul > a
// [echo]->[bonjour]->[$teub]->[CUL]->[CUL]->[echo]->[cul]->[a] => QUOTING
// [CMD] ->[ARGUMNT]->[ARG]--->[ARG]->[ARG]->[PIPE]->[COMMAND]->[ARG]->[REDIR]->[FILE] => TOKENIZATION

int	wcounter(char const *s, char c)
{
	int	wc;
	int	i;
	int	sep;

	wc = 0;
	i = 0;
	sep = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
		sep = (i++, 1);
	while (s[i] != '\0')
	{
		if (s[i++] == c)
		{
			if (sep == 1)
				sep = (wc++, 0);
		}
		else
			sep = 1;
	}
	if (s[i - 1] != c && sep == 1)
		wc++;
	return (wc);
}

char	**ft_free(int wl, char **tab)
{
	while (wl >= 0)
	{
		free(tab[wl]);
		wl--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split2(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	wl;

	i = 0;
	j = 0;
	wl = 0;
	while (s[i] != 0 && s[i] == c)
		i++;
	while (wl < wcounter(s, c))
	{
		while (s[i] != c && s[i] != '\0')
		{
			j++;
			i++;
		}
		tab[wl] = ft_substr(s, i - j, j);
		if (!tab[wl])
			return (ft_free(wl, tab));
		while (s[i] == c && s[i] != '\0')
			i++;
		j = (wl++, 0);
	}
	tab[wl] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (wcounter(s, c) + 1));
	if (!tab)
		return (NULL);
	return (ft_split2(tab, s, c));
}
