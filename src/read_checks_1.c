/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_checks_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:09 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/28 22:15:05 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_names(t_scene_data *scene)
{
	int		i;
	char	*aux;

	i = 0;
	while (i < 4)
	{
		if (scene->textures[i] == 0 || ft_strlen(scene->textures[i]) <= 4)
			return (1);
		aux = scene->textures[i] + ft_strlen(scene->textures[i]) - 4;
		if (ft_strncmp(".xpm", aux, 4) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_scene_size(t_scene_data *scene, long *scene_width, long *scene_height)
{
	t_line	*l;

//	l = *scene->scene_list;
	l = scene->map_start;
	*scene_height = 0;
	*scene_width = 0;
	while (l)
	{
		if (ft_strlen(l->line) == 0)
			return (1);
		if ((int) ft_strlen(l->line) > *scene_width)
			*scene_width = ft_strlen(l->line);
		if (*scene_width == 1 && l->line[0] == '\n')
			*scene_width -= 1;
		l = l->next;
		(*scene_height) += 1;
	}
	if (*scene_height < 3 || *scene_width < 3)
		return (1);
	printf("width: %li, height: %li\n", *scene_width, *scene_height);
	return (0);
}

int	check_input_schema_first(t_scene_data *scene)
{
	int		i;
	t_line	*l;

	i = 0;
	l = *(scene->scene_list);
	while (i < 4)
	{
		if (l->next == 0)
			return (1);
		i++;
		l = l->next;
	}
	if (l && ft_strlen(l->line) > 1)
		return (1);
	l = l->next;
	scene->colors_start = l;
	return (0);
}
/*
int	check_input_schema(t_scene_data *scene)
{
	int		i;
	t_line	*l;

	i = 0;
	if (check_input_schema_first(scene))
		return (1);
	l = scene->colors_start;
	while (i < 2)
	{
		if (l->next == 0)
			return (1);
		l = l->next;
		i++;
	}
	if (l && ft_strlen(l->line) > 1)
		return (1);
	l = l->next;
	if (l)
		scene->map_start = l;
	else
		return (1);
	return (0);
}
*/
