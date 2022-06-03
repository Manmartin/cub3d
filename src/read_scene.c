#include "cub3d.h"

int	read_scene(t_data *data,t_scene_data *scene)
{
	if (copy_map(scene))
		return (1);
//	(void) data;
	get_scene_size(scene, &scene->width, &scene->height);
	if (parse_scene(data, scene))
		return (1);
//	print_map(scene);
	printf("width %li, height %li", scene->width, scene->height);
	return (0);
}

t_line	*get_line_as_list_element(char *aux_line)
{
	t_line *l;

	if (!aux_line)
		return (0);
	l = malloc(sizeof(t_line));
	l->next = 0;
	l->line = aux_line;
	return (l);
}

int	copy_map(t_scene_data *scene)
{
	int		fd;
	t_line 	*l;
	char	*aux_line;

	l = 0;
	fd = open(scene->scene_path, O_RDONLY);
	if (fd < 1)
	{
		perror("error opening scene file");
		return (1);
	}
	scene->scene_list = malloc(sizeof(t_line *));
	aux_line = get_next_line(fd);
	if (!aux_line)
	{
		ft_putstr_fd("Empty map\n", 2);
		return (1);
	}
	l = get_line_as_list_element(aux_line);
	*(scene->scene_list) = l;
	ft_putstr_fd(aux_line, 2);
	while (aux_line)
	{
		aux_line = get_next_line(fd);
		ft_putstr_fd(aux_line, 2);
		l->next = get_line_as_list_element(aux_line);
		l = l->next;
	}
	close(fd);
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
	printf("aux%s\n", aux);
	if (!aux || ft_strlen(aux) <= 1 || *(++aux) == ',')
		return (-1);
	sep_rgb[1] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	printf("aux11: %s\n", aux);
	if (!aux || ft_strlen(aux) <= 2)
		return (-1);
	printf("eoooo %zu\n", ft_strlen(aux));
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
	printf("color ok\n");
//	printf("%u, %u\n", scene->floor_color, scene->ceilling_color);
	l = l->next;
	return (0);
}

int		parse_texture_paths(t_scene_data *scene, t_line *l)
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

int		parse_scene(t_data *data, t_scene_data *scene)
{
	size_t	i;
	size_t	j;
	t_line	*l;

	i = 0;
	j = 0;
	l = scene->map_start;
	if (parse_texture_paths(scene, *(scene->scene_list)) == 1)
	{
		ft_putstr_fd("Error parsing texture paths\n", 2);
		return (1);
	}
	if (parse_colors(scene, scene->colors_start))
	{
		ft_putstr_fd("Error parsing colors, invalid map\n", 2);
		return (1);
	}
	scene->map = malloc(sizeof(char *) * (scene->height + 1));
	while (l)
	{
		scene->map[i] = malloc(sizeof(char) * scene->width + 1);
		while (j < ft_strlen(l->line) - 1)
		{
			scene->map[i][j] = l->line[j];
			if (l->line[j] == 'N')
			{
				data->game->player->x = j;
				data->game->player->y = i;
				printf("[%f %f]\n", data->game->player->x, data->game->player->y);
			}
			j++;
		}
		while (j < scene->width)
		{
			scene->map[i][j] = ' ';
			j++;
		}
		scene->map[i][j] = 0;
		j = 0;
		l = l->next;
		i++;
	}
	scene->map[i] = 0;
	return (0);
}

void	get_scene_size(t_scene_data *scene, size_t *scene_width, size_t *scene_height)
{
	int		i;
	t_line	*l;

	i = 0;
	*scene_height = 0;
	*scene_width = 0;
	l = *(scene->scene_list);
	while (i < 8)
	{
		if (i == 5)
			scene->colors_start = l;
		l = l->next;
		i++;
	}
	if (l)
		scene->map_start = l;
	while (l)
	{
		if (ft_strlen(l->line) > *scene_width)
			*scene_width = ft_strlen(l->line);
		if (*scene_width > 0 && l->line[*scene_width - 1] == '\n')
			*scene_width -= 1;
		l = l->next;
		(*scene_height) += 1;
	}
}
