/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:07 by albgarci          #+#    #+#             */
/*   Updated: 2022/07/01 17:12:06 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	zero_to_255_check(char *line)
{
	int	num;

	num = ft_atoi(line);
	if (num > 255)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int	color_rgb_verification(char *line)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (ft_strchr(line, ',') == 0)
		sub = ft_strdup(line);
	else
		sub = ft_substr(line, 0, ft_strchr(line, ',') - line);
	if (ft_strlen(sub) == 0 || *sub == '-' || ft_strlen(sub) > 4)
	{
		free(sub);
		return (1);
	}
	while (sub[i] && sub[i] != ',' && sub[i] != '\n')
	{
		if (ft_isdigit(sub[i]) == 0)
		{
			free(sub);
			return (1);
		}
		i++;
	}
	return (zero_to_255_check(sub));
}

int	parse_colors_2(char *line)
{
	int		sep_rgb[3];
	char	*aux;
	int		color;

	aux = line + 2;
	if (!aux || ft_strlen(aux) == 0 || *(aux) == ',')
		return (-1);
	while (aux && *aux == ' ')
		aux++;
	if (color_rgb_verification(aux))
		return (-1);
	sep_rgb[0] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 1 || *(++aux) == ',')
		return (-1);
	if (color_rgb_verification(aux))
		return (-1);
	sep_rgb[1] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 2 || color_rgb_verification(++aux))
		return (-1);
	sep_rgb[2] = ft_atoi(aux);
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
	else if (ft_strncmp(l->line, "C ", 2) == 0)
	{
		scene->ceilling_color = parse_colors_2(l->line);
		if (scene->ceilling_color == -1)
			return (1);
	}
	else
		return (1);
	return (0);
}
