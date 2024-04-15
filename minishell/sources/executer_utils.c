/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:04:34 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 14:52:29 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cd(t_shell *shell, int i)
{
	char	*str;

	str = shell->final[i].exec[1];
	if (ft_strcmp(shell->final[i].exec[1], "~") == 0 \
		|| !shell->final[i].exec[1])
		chdir(getenv("HOME"));
	else if (ft_strcmp(shell->final[i].exec[1], "-") == 0)
		chdir(getenv("OLDPWD"));
	else if (ft_strcmp(shell->final[i].exec[1], "..") == 0)
		chdir("..");
	else if (chdir(shell->final[i].exec[1]) != 0)
		ft_printf("cd: no such file or directory: %s\n", str);
}

void	part_of_echo(t_shell *shell, int unit, int *n_pos, int *n_flag)
{
	int		break_flag;
	size_t	j;

	break_flag = 0;
	if (!ft_strncmp(shell->final[unit].exec[(*n_pos)], "-n", 2))
	{
		while (!ft_strncmp(shell->final[unit].exec[(*n_pos)], "-n", 2))
		{
			if (ft_strlen(shell->final[unit].exec[(*n_pos)]) > 2)
			{
				j = 1;
				while (j < ft_strlen(shell->final[unit].exec[(*n_pos)]))
				{
					if (shell->final[unit].exec[(*n_pos)][j] != 'n')
						break_flag = 1;
					j++;
				}
			}
			if (break_flag)
				break ;
			(*n_flag) = 1;
			(*n_pos)++;
		}
	}
}

void	run_echo(t_shell *shell, int unit)
{
	int	i;
	int	n_flag;
	int	n_pos;
	int	len;

	i = 0;
	n_flag = 0;
	n_pos = 1;
	len = 1;
	while (shell->final[unit].exec[len++] != NULL)
		;
	len = len - 2;
	part_of_echo(shell, unit, &n_pos, &n_flag);
	i = --n_pos;
	while (shell->final[unit].exec[++i] != NULL)
	{
		ft_putstr_fd(shell->final[unit].exec[i], 1);
		if (i < len)
			ft_putchar_fd(' ', 1);
	}
	if (!n_flag)
		write(1, "\n", 1);
}

int	run_export(t_shell *shell, int unit)
{
	int	j;

	if (shell->final[unit].exec[1] == NULL)
		return (export_no_arg(shell), 0);
	else
	{
		j = 0;
		while (shell->final[unit].exec[++j] != NULL)
		{
			if (ft_strchr(shell->final[unit].exec[j], '='))
			{
				if (export_valid_var(shell->final[unit].exec[j]))
					return (ft_printf("bash: export: `%s': not a valid \
					identifier\n", shell->final[unit].exec[j]), 1);
				else if (check_export(shell, unit, j) == 1)
					return (2);
				else if (check_export(shell, unit, j) == 2)
					ft_realloc_add_string(shell, shell->final[unit].exec[j]);
				else
					break ;
			}
		}
	}
	return (0);
}

void	run_unset(t_shell *shell, int unit)
{
	int	k;
	int	m;

	k = 1;
	while (shell->final[unit].exec[k] != NULL)
	{
		m = 0;
		while (shell->env[m] != NULL)
		{
			if (ft_strncmp(shell->env[m], shell->final[unit].exec[k], \
				ft_strlen(shell->final[unit].exec[k])) == 0)
				ft_realloc_del_string(shell, shell->final[unit].exec[k]);
			m++;
		}
		k++;
	}
	return ;
}
