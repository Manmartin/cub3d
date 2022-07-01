/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:32:01 by albgarci          #+#    #+#             */
/*   Updated: 2022/07/01 17:21:06 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bad_colors_error(t_data *data, t_scene_data *scene)
{
	ft_putstr_fd("Error\nBad colors.\n", 2);
	free_double_char(scene->elements);
	free_basics(data, scene);
	return (1);
}

int	parse_previous_elements_1(t_data *data, t_scene_data *scene,
		t_line **l, int *j)
{
	while (*j < 6)
	{
		if (ft_strlen((*l)->line) == 1 && *(*l)->line == '\n')
			break ;
		else if (ft_strncmp(scene->elements[*j], (*l)->line,
				ft_strlen(scene->elements[*j])) == 0)
		{
			free(scene->elements[*j]);
			scene->elements[*j] = ft_strdup("OK");
			if (*j < 4)
				scene->textures[*j] = ft_strtrim((*l)->line + 3, " \n");
			else if (parse_colors(scene, *l))
				return (bad_colors_error(data, scene));
			break ;
		}
		(*j)++;
	}
	return (0);
}

int	parse_previous_elements(t_data *data, t_scene_data *scene, t_line **l)
{
	int	j;

	j = 0;
	scene->all_elements = 0;
	scene->elements = base_elements();
	while (*l && scene->all_elements == 0)
	{
		j = 0;
		check_all_elements(scene);
		if (parse_previous_elements_1(data, scene, l, &j))
			return (1);
		if (j == 6 && scene->all_elements == 0)
		{
			ft_putstr_fd("Error\nWrong map.\n", 2);
			free_double_char(scene->elements);
			free_basics(data, scene);
			return (1);
		}
		if (scene->all_elements == 1)
			break ;
		*l = (*l)->next;
	}
	free_double_char(scene->elements);
	return (0);
}

int	parse_map(t_data *data, t_scene_data *scene, t_line **l)
{
	int	i;

	i = 0;
	scene->map = malloc(sizeof(char *) * (scene->height + 1));
	while (*l)
	{
		if (parse_scene_loop(data, scene, (*l)->line, i))
			return (1);
		i++;
		*l = (*l)->next;
	}
	scene->map[i] = 0;
	return (0);
}

int	parse_scene(t_data *data, t_scene_data *scene)
{
	t_line	*l;

	l = *(scene->scene_list);
	if (parse_previous_elements(data, scene, &l))
		return (1);
	while (l && ft_strlen(l->line) == 1 && *l->line == '\n')
		l = l->next;
	scene->map_start = l;
	if (get_scene_size(scene, &scene->width, &scene->height))
	{
		free_basics(data, scene);
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (1);
	}
	if (check_texture_names(scene))
	{
		free_basics(data, scene);
		return (1);
	}
	return (parse_map(data, scene, &l));
}
