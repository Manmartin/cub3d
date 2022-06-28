/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:27 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/28 23:00:09 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%s\n", scene->textures[i]);
		i++;
	}
	i = 0;
	while (i < scene->height)
	{
		printf("%s\n", scene->map[i]);
		i++;
	}
}
