/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:15:35 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/05 23:15:36 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mark_path(long x, long y, char **map, t_scene_data *scene)
{
	if (x == 0 || y == 0 || x == scene->width || y == scene->height)
		scene->valid_map = 0;
	else
		map[y][x] = 'x';
}

int	check_valid_map(long x, long y, char **map, t_scene_data *scene)
{
	if (x < 0 || y < 0)
		return (0);
	if ((x == scene->width - 1 || x == 0) && map[y][x] == ' ')
		scene->valid_map = 0;
	else if ((y == scene->height - 1 || y == 0) && map[y][x] == ' ')
		scene->valid_map = 0;
	else if (ft_strchr("NSEW", map[y][x]) || map[y][x] == '0')
		mark_path(x, y, map, scene);
	else if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	else
		scene->valid_map = 0;
	if (scene->valid_map == 0)
		return (-1);
	check_valid_map(x, y + 1, map, scene);
	check_valid_map(x + 1, y, map, scene);
	check_valid_map(x, y - 1, map, scene);
	check_valid_map(x - 1, y, map, scene);
	return (0);
}
