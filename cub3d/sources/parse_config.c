/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:47:28 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/19 13:40:13 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_path(char **conf, char *identifier, char *split_i)
{
	char	*save;
	char	*check;

	save = NULL;
	if (!*conf)
	{
		check = ft_strnstr(split_i, "./", ft_strlen(split_i));
		if (check == NULL)
			return (printf("error, invalid path\n"), 1);
		save = ft_strtrim(check, " ");
		if (!save)
			return (printf("error, malloc strtrim\n"), 1);
		*conf = save;
		return (0);
	}
	else
		return (printf("error, %s already set\n", identifier), 1);
}

int	check_and_get_color(char **ff, char identifier)
{
	int	x;

	x = 0;
	while (ff[x] != NULL)
		x++;
	if (x != 3)
		return (printf("error, format for %c is not correct!\n", \
			identifier), ft_free(ff), 1);
	if (ft_atoi(ff[0]) < 0 || ft_atoi(ff[1]) < 0 || ft_atoi(ff[2]) < 0 || \
		ft_atoi(ff[0]) > 255 || ft_atoi(ff[1]) > 255 || ft_atoi(ff[2]) > 255)
		return (printf("error, color-values not correct\n"), ft_free(ff), 1);
	return (0);
}

int	set_color(int *conf, char identifier, char *split_i)
{
	char	*cut;
	char	**ff;
	char	*check;

	if (*conf == -2)
	{
		check = ft_strchr(split_i, identifier) + 1;
		if (!ft_strchr(check, ','))
			return (printf("error, %c empty\n", identifier), 1);
		cut = ft_strtrim(check, " ");
		if (!cut)
			return (printf("error trim\n"), 1);
		ff = ft_split(cut, ',');
		free(cut);
		if (!ff)
			return (printf("error split malloc\n"), 1);
		if (check_and_get_color(ff, identifier))
			return (1);
		*conf = ft_pixel(ft_atoi(ff[0]), ft_atoi(ff[1]), ft_atoi(ff[2]), 0xff);
		ft_free(ff);
		return (0);
	}
	else
		return (printf("error, %c already set\n", identifier), 1);
}

int	set_map(char **split, int *i, t_list **head)
{
	int	flag;

	flag = 0;
	while (split[*i] != NULL)
	{
		if ((ft_strchr(split[*i], '0') || ft_strchr(split[*i], '1')) \
			&& !ft_strchr(split[*i], 'F') && !ft_strchr(split[*i], 'C'))
		{
			if (!flag)
				ft_lstadd_back(head, ft_lstnew(ft_strdup(split[*i])));
			else
				return (printf("error, map should not have empty lines\n"), 1);
		}
		else
			flag = 1;
		(*i)++;
	}
	--(*i);
	return (0);
}

int	ft_fill_config(t_cub *cub, char **split, t_list **head, int *flag)
{
	int		i;

	i = -1;
	while (split[++i] != NULL && *flag == 0)
	{
		if (ft_strnstr(split[i], "NO", ft_strlen(split[i])))
			*flag = set_path(&cub->config->no, "NO", split[i]);
		if (ft_strnstr(split[i], "SO", ft_strlen(split[i])))
			*flag = set_path(&cub->config->so, "SO", split[i]);
		if (ft_strnstr(split[i], "WE", ft_strlen(split[i])))
			*flag = set_path(&cub->config->we, "WE", split[i]);
		if (ft_strnstr(split[i], "EA", ft_strlen(split[i])))
			*flag = set_path(&cub->config->ea, "EA", split[i]);
		if (ft_strnstr(split[i], "F", ft_strlen(split[i])))
			*flag = set_color(&cub->config->f, 'F', split[i]);
		if (ft_strnstr(split[i], "C", ft_strlen(split[i])))
			*flag = set_color(&cub->config->c, 'C', split[i]);
		if ((ft_strchr(split[i], '0') || ft_strchr(split[i], '1')) \
			&& !ft_strchr(split[i], 'F') && !ft_strchr(split[i], 'C')
			&& !ft_strchr(split[i], 'E') && !ft_strchr(split[i], 'O'))
			*flag = set_map(split, &i, head);
	}
	return (0);
}
