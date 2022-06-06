/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freezers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:15:42 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/06 20:22:12 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_basics(t_data *data, t_scene_data *scene)
{
//	free_textures(scene);
	free_raw_scene(scene);
	free(data->scene);
	free(data->game->player);
	free(data->game);
}

void	free_map_partially(t_scene_data *scene, int limit)
{
	int	i;

	i = 0;
	while (i < limit && scene->map && scene->map[i])
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
}
