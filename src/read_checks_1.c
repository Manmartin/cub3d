/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_checks_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:09 by albgarci          #+#    #+#             */
/*   Updated: 2022/07/01 16:19:00 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	throw_texture_error(int type)
{
	if (type == 1)
	{
		ft_putstr_fd("Error\nBad texture name. "
			"Make sure they have a name a have .xpm extension.\n", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("Error\n"
			"Error opening texture files.\n", 2);
	}
	return (1);
}

int	check_texture_names(t_scene_data *scene)
{
	int		i;
	char	*aux;
	int		fd;

	i = 0;
	while (i < 4)
	{
		if (scene->textures[i] == 0 || ft_strlen(scene->textures[i]) <= 4)
			return (throw_texture_error(1));
		aux = scene->textures[i] + ft_strlen(scene->textures[i]) - 4;
		if (ft_strncmp(".xpm", aux, 4) != 0)
			return (throw_texture_error(1));
		fd = open(scene->textures[i], O_RDONLY);
		if (fd == -1)
			return (throw_texture_error(2));
		close(fd);
		i++;
	}
	return (0);
}

int	get_scene_size(t_scene_data *scene, long *scene_width, long *scene_height)
{
	t_line	*l;

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
	return (0);
}
