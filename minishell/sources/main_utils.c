/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:10:21 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/31 15:05:03 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_com(t_shell *shell)
{
	close(shell->fd_in);
	close(shell->fd_out);
	free(shell->com);
	free(shell->prompt);
}

void	clean_up(t_shell *shell)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = shell->mypaths;
	if (!tmp)
	{
		printf("segfault in clean_up\n");
		return ;
	}
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(shell->mypaths);
	free(shell);
}
