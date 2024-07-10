/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:27 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/29 12:53:04 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_changeenv(char *o_cwd)
{
	char	*nwd[4];
	char	*n_owd;

	nwd[0] = NULL;
	nwd[1] = ft_strjoin("OLDPWD=\0", o_cwd);
	n_owd = getcwd(NULL, 0);
	if (!n_owd)
	{
	}
	nwd[2] = ft_strjoin("PWD=\0", n_owd);
	nwd[3] = NULL;
	if (!nwd[1] || !nwd[2])
	{
	}
	ft_export(nwd);
	free(nwd[1]);
	free(nwd[2]);
	free(n_owd);
}

int	ft_cd(char	**dirtogo)
{
	char	*cwd;

	if (dirtogo[0] && dirtogo[1] != NULL)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
	}
	if (dirtogo[0] == NULL)
		chdir("/home/");
	else
	{
		if (chdir(dirtogo[0]) == -1)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			free(cwd);
			return (1);
		}
	}
	ft_changeenv(cwd);
	free(cwd);
	return (0);
}
