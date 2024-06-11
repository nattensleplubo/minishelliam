/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:27 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/10 16:09:04 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char	*dirtogo)
{
	if(dirtogo == NULL)
		chdir("/home/");
	else
	{
		if (chdir(dirtogo) == -1)
			printf("%s : no such file or directory\n", dirtogo);
	}
}