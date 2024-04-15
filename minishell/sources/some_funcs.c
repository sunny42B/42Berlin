/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:57:05 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 16:32:17 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_arg(t_shell *shell)
{
	char	**sort;
	int		i;
	int		j;
	char	**env;

	i = -1;
	j = -1;
	env = shell->env;
	while (env[++i] != NULL)
		;
	sort = malloc(sizeof(char *) * (i + 1));
	while (env[++j] != NULL)
		sort[j] = ft_strdup(env[j]);
	sort[j] = NULL;
	sort_arr(sort, i);
	i = -1;
	while (sort[++i] != NULL)
		printf("declare -x %s\n", sort[i]);
	ft_free(sort);
}

int	check_export(t_shell *shell, int unit, int j)
{
	int		m;
	char	*check;

	m = -1;
	while (shell->env[++m] != NULL)
	{
		check = remove_after_eq(shell->final[unit].exec[j]);
		if (ft_strncmp(shell->env[m], check, ft_strlen(check)) == 0)
		{
			free(shell->env[m]);
			shell->env[m] = ft_strdup(shell->final[unit].exec[j]);
			if (!shell->env[m])
				return (free(check), printf("Error strdup in export\n"), 1);
			return (free(check), 0);
		}
	}
	return (2);
}

void	ft_realloc_add_string(t_shell *shell, char *new)
{
	int		i;
	int		j;
	char	**env;
	char	**new_env;

	i = 0;
	j = -1;
	env = shell->env;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	while (env[++j] != NULL)
	{
		new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
			return ;
	}
	new_env[j] = ft_strdup(new);
	new_env[++j] = NULL;
	ft_free(env);
	shell->env = new_env;
	get_new_env(shell);
}

void	ft_realloc_del_string(t_shell *shell, char *out)
{
	int		i;
	int		j;
	char	**new_env;
	char	**env;

	env = shell->env;
	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	j = -1;
	while (env[++j] != NULL)
	{
		if ((ft_strncmp(env[j], out, ft_strlen(out)) == 0)
			&& (ft_strlen(env[j]) == ft_strlen(out)
				+ ft_strlen(ft_strchr(env[j], '='))))
			continue ;
		else
			new_env[++i] = ft_strdup(env[j]);
	}
	new_env[++i] = NULL;
	ft_free(env);
	shell->env = new_env;
	get_new_env(shell);
}

int	export_valid_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((ft_isdigit(str[0]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}
