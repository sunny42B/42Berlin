/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:40:47 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 15:37:26 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exe_arr(t_shell *shell, t_exe *list)
{
	int	i;
	int	j;

	j = 0;
	while (j < shell->units)
	{
		i = 0;
		while (list[j].exec[i] != NULL)
		{
			free(list[j].exec[i]);
			i++;
		}
		free(list[j].exec);
		j++;
	}
	free(list);
}

void	free_executer(t_shell *shell)
{
	int	i;
	int	j;

	j = 0;
	while (j < shell->units)
	{
		i = 0;
		while (shell->final[j].exec[i] != NULL)
		{
			free(shell->final[j].exec[i]);
			i++;
		}
		free(shell->final[j].exec);
		j++;
	}
	free(shell->final);
}

int	print_exe_arr(t_shell *shell, t_exe *arr)
{
	int	i;
	int	j;

	j = 0;
	printf("in print_exe_arr \n");
	while (j < shell->units)
	{
		i = 0;
		printf("type %d\t", arr[j].type);
		while (arr[j].exec[i] != NULL)
		{
			printf("exec[%d]: %s\t", i, arr[j].exec[i]);
			i++;
		}
		printf("\n");
		j++;
	}
	return (0);
}
