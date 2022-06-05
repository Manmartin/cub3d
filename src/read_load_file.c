/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:12 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/05 23:16:13 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	copy_map_loop(t_scene_data *scene, int fd)
{
	t_line	*l;
	char	*aux_line;

	aux_line = get_next_line(fd);
	if (!aux_line)
	{
		ft_putstr_fd("Empty map\n", 2);
		return (1);
	}
	scene->scene_list = malloc(sizeof(t_line *));
	l = get_line_as_list_element(aux_line);
	*(scene->scene_list) = l;
	while (aux_line)
	{
		aux_line = get_next_line(fd);
		l->next = get_line_as_list_element(aux_line);
		l = l->next;
	}
	return (0);
}

int	copy_map(t_scene_data *scene)
{
	int		fd;

	fd = open(scene->scene_path, O_RDONLY);
	if (fd < 1)
	{
		perror("error opening scene file");
		return (1);
	}
	if (copy_map_loop(scene, fd))
		return (1);
	close(fd);
	return (0);
}
