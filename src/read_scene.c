/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:15 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/29 22:36:05 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_scene(t_data *data, t_scene_data *scene)
{
	if (copy_map(scene))
	{
		free(data->scene);
		free(data->game->player);
		free(data->game);
		return (1);
	}
	if (parse_scene(data, scene))
		return (1);
	if (data->game->found_player == 0)
	{
		ft_putstr_fd("Error\nNo player found\n", 2);
		free_map(data->scene);
		free_basics(data, data->scene);
		return (1);
	}
	return (0);
}

int	parse_scene_operations(t_data *data, int i, int j, char c)
{
	if (ft_strchr("NSEW", c))
	{
		if (data->game->found_player == 0)
			data->game->found_player = 1;
		else
		{
			free_map_partially(data->scene, i + 1);
			free_basics(data, data->scene);
			ft_putstr_fd("Error\n2 players found\n", 2);
			return (1);
		}
		data->game->player->x = j;
		data->game->player->y = i;
		data->game->initial_orientation = c;
	}
	else if (ft_strchr(" 10", c) == 0)
	{
		free_map_partially(data->scene, i + 1);
		free_basics(data, data->scene);
		ft_putstr_fd("Error\nWrong map!!\n", 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	parse_scene_loop(t_data *data, t_scene_data *scene, char *line, int i)
{
	int	j;

	j = 0;
	scene->map[i] = malloc(sizeof(char) * scene->width + 1);
	while (j < (int) ft_strlen(line) - 1)
	{
		scene->map[i][j] = line[j];
		if (parse_scene_operations(data, i, j, line[j]))
			return (1);
		j++;
	}
	while (j < scene->width)
	{
		scene->map[i][j] = ' ';
		j++;
	}
	scene->map[i][j] = 0;
	return (0);
}

char	**base_elements(void)
{
	char	**elements;

	elements = malloc(sizeof(char *) * 7);
	elements[0] = ft_strdup("NO ");
	elements[1] = ft_strdup("SO ");
	elements[2] = ft_strdup("WE ");
	elements[3] = ft_strdup("EA ");
	elements[4] = ft_strdup("F ");
	elements[5] = ft_strdup("C ");
	elements[6] = 0;
	return (elements);
}

int	check_all_elements(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strlen(scene->elements[i]) != 2
			|| ft_strncmp(scene->elements[i], "OK", 3))
			break ;
		i++;
	}
	if (i == 6)
	{
		scene->all_elements = 1;
		return (0);
	}
	return (1);
}
