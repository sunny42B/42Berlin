/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:55:57 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/19 13:36:17 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_map(char **map, int *i)
{
	while (*i != 0)
		free(map[(*i)--]);
	free(map);
	map = NULL;
	return (1);
}

int	get_map_arr(t_cub *cub, t_list *head)
{
	int		i;
	t_list	*tmp;
	size_t	len;

	i = 0;
	tmp = head;
	while (i < cub->config->map_h && tmp != NULL)
	{
		len = ft_strlen(tmp->content) + 1;
		cub->config->map[i] = (char *) malloc(sizeof(char) * len);
		if (!cub->config->map[i])
			return (printf("error malloc map\n"), \
				free_map(cub->config->map, &i), 1);
		ft_strlcpy(cub->config->map[i], tmp->content, len);
		i++;
		tmp = tmp->next;
	}
	cub->config->map[i] = NULL;
	return (0);
}

int	get_map(t_cub *cub, t_list *head)
{
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	tmp = head;
	len = ft_strlen(tmp->content);
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->content) > len)
			len = ft_strlen(tmp->content);
		tmp = tmp->next;
		i++;
	}
	cub->config->map_h = i;
	cub->config->map_w = (int)len;
	cub->config->map = (char **) malloc(sizeof(char *) * (i + 1));
	if (!cub->config->map)
		return (printf("error malloc map\n"), 1);
	if (get_map_arr(cub, head))
		return (1);
	return (0);
}

int	check_config(t_cub *cub, t_list *head)
{
	int	flag;

	flag = 0;
	if (!cub->config->no)
		flag = 1;
	if (!cub->config->so)
		flag = 1;
	if (!cub->config->we)
		flag = 1;
	if (!cub->config->ea)
		flag = 1;
	if (!head)
		flag = 1;
	if (cub->config->f == -2 || cub->config->c == -2)
		flag = 1;
	if (flag)
		return (1);
	return (0);
}

int	parse_map(t_cub *cub, char **split)
{
	t_list	*head;
	int		flag;

	flag = 0;
	head = NULL;
	if (ft_config_init(cub))
		return (1);
	ft_fill_config(cub, split, &head, &flag);
	if (flag == 1)
		return (ft_free_list(&head), free_the_shit(cub), 1);
	if (check_config(cub, head))
		return (printf("error, some info is missing\n"), \
			ft_free_list(&head), free_the_shit(cub), 1);
	if (get_map(cub, head))
		return (ft_free_list(&head), free_the_shit(cub), 1);
	ft_free_list(&head);
	return (0);
}
