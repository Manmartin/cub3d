/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:15 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/07 12:44:12 by albgarci         ###   ########.fr       */
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
	if (check_input_schema(scene))
	{
		free_basics(data, scene);
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (1);
	}
	if (get_scene_size(scene, &scene->width, &scene->height))
	{
		free_basics(data, scene);
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (1);
	}
	if (parse_scene(data, scene))
		return (1);
	if (data->game->found_player == 0)
	{
		ft_putstr_fd("Error\nNo player found\n", 2);
		return (1);
	}
	return (0);
}

/*
int	parse_texture_paths(t_scene_data *scene, t_line *l)
{
	size_t	i;
	char	*aux;

	scene->cardinal[0] = ft_strdup("NO ");
	scene->cardinal[1] = ft_strdup("SO ");
	scene->cardinal[2] = ft_strdup("WE ");
	scene->cardinal[3] = ft_strdup("EA ");
	i = 0;
	while (i < 4)
	{
		aux = l->line;
		if (ft_strncmp(aux, scene->cardinal[i], 3) == 0)
		{
			aux += 3;
			scene->textures[i] = ft_substr(aux, 0, ft_strchr(aux, '\n') - aux);
		}
		else
			return (free_cardinals(scene));
		l = l->next;
		i++;
	}
	l = l->next;
	free_cardinals(scene);
	return (0);
}
*/

int	parse_scene_previous_checks(t_data *data, t_scene_data *scene)
{
	if (parse_texture_paths(scene, *(scene->scene_list)) == 1)
	{
		free_basics(data, scene);
		ft_putstr_fd("Error\nBad texture paths\n", 2);
		return (1);
	}
	if (check_texture_names(scene))
	{
		ft_putstr_fd("Error\nBad texture name. "
			"Make sure they have a name a have .xpm extension.\n", 2);
		free_basics(data, scene);
		return (1);
	}
	if (parse_colors(scene, scene->colors_start))
	{
		ft_putstr_fd("Error\nBad colors.\n", 2);
		free_basics(data, scene);
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
		ft_putstr_fd("Error\nUnexpected character\n", 2);
		ft_putchar_fd(c, 2);
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

int	parse_scene(t_data *data, t_scene_data *scene)
{
	int		i;
	t_line	*l;

	i = 0;
	l = scene->map_start;
	if (parse_scene_previous_checks(data, scene))
		return (1);
	scene->map = malloc(sizeof(char *) * (scene->height + 1));
	while (l)
	{
		if (parse_scene_loop(data, scene, l->line, i))
			return (1);
		l = l->next;
		i++;
	}
	scene->map[i] = 0;
	return (0);
}
