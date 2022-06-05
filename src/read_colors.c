/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:07 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/06 00:13:19 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	parse_colors_2(char *line)
{
	int		sep_rgb[3];
	char	*aux;
	int		color;

	aux = line + 2;
	if (!aux || ft_strlen(aux) == 0 || *(aux) == ',')
		return (-1);
	sep_rgb[0] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 1 || *(++aux) == ',')
		return (-1);
	sep_rgb[1] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 2)
		return (-1);
	sep_rgb[2] = ft_atoi(++aux);
	color = ((sep_rgb[0] << 16) | (sep_rgb[1] << 8) | sep_rgb[2]);
	return (color);
}

int	parse_colors(t_scene_data *scene, t_line *l)
{
	if (ft_strncmp(l->line, "F ", 2) == 0)
	{
		scene->floor_color = parse_colors_2(l->line);
		if (scene->floor_color == -1)
			return (1);
	}
	else
		return (1);
	l = l->next;
	if (ft_strncmp(l->line, "C ", 2) == 0)
	{
		scene->ceilling_color = parse_colors_2(l->line);
		if (scene->ceilling_color == -1)
			return (1);
	}
	else
		return (1);
	l = l->next;
	return (0);
}
