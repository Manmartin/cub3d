/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freezers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:15:39 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/05 23:15:39 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_raw_scene(t_scene_data *scene)
{
	t_line	*l;
	t_line	*aux;

	l = *(scene->scene_list);
	while (l)
	{
		aux = l->next;
		free(l->line);
		free(l);
		l = aux;
	}
	free(scene->scene_list);
}

void	free_map(t_scene_data *scene)
{
	size_t	i;

	i = 0;
	while (scene->map && scene->map[i])
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
}

int	free_textures(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(scene->textures[i]);
		i++;
	}
	return (1);
}

int	free_cardinals(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(scene->cardinal[i]);
		i++;
	}
	return (1);
}

void	freezers(t_data *data)
{
	free_map(data->scene);
	free_textures(data->scene);
	free_raw_scene(data->scene);
	if (data->scene->valid_map)
		mlx_destroy_image(data->mlx, data->img.img);
	free(data->scene);
	free(data->game->player);
	free(data->game->dir);
	free(data->game->cam);
	free(data->game);
}
